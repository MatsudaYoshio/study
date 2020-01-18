import math
import pickle
import pandas as pd
import numpy as np
import lightgbm as lgbm
from datetime import datetime as dt
from datetime import timedelta

# 天気情報の補間、最も近い時間帯のものでうめる
def nearest_weather(x, weather_data, place):
    x = x.replace('-', '/')
    d = dt.strptime(x, '%Y/%m/%d %H:%M')
    h = d.hour

    th = 0
    if place == 'kanazawa':
        if h == 0 or h == 1:
            th = 3
        elif h == 23:
            th = 21
        elif h%3 == 2:
            th = h+1
        else:
            th = h//3*3
    elif place == 'toyama':
        th = (h//6+1)*6-3

    d += timedelta(hours=th-h)

    return weather_data.loc[[d.strftime('%Y/%#m/%#d %#H:00')], ['天気']].values[0][0]

# 気象情報の補間、前後の時間帯の情報から線形補完
def interpolate_weather(x, weather_data, dimension):
    x = x.replace('-', '/')
    d = dt.strptime(x, '%Y/%m/%d %H:%M')
    m = d.minute

    if m == 0:
       return weather_data.loc[[d.strftime('%Y/%#m/%#d %#H:%M')], [dimension]].values[0][0]
    else:
       sd = d - timedelta(minutes=m)
       ed = d + timedelta(minutes=60-m)

       sv = weather_data.loc[[sd.strftime('%Y/%#m/%#d %#H:%M')], [dimension]].values[0][0]
       ev = weather_data.loc[[ed.strftime('%Y/%#m/%#d %#H:%M')], [dimension]].values[0][0]

       return sv + m*(ev-sv)/60

# 月日、中央標準時、東経、北緯、日照時間から日射量を推定する
def solar_irradiance(month, day, standard_time, east_longitude, north_latitude, sunshine_duration):
    # J: 元日からの通算日数+0.5
    month_sum = [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334]
    J = month_sum[month-1]+day+0.5
    
    omega = 2*math.pi/365 # うるう年は2*math.pi/366

    # 太陽緯度（太陽光線と地球の赤道面との角度、±23°27'の範囲で変化）、計算方法は2通り
    delta = math.radians(0.33281-22.984*math.cos(omega*J)-0.34990*math.cos(2*omega*J)-0.13980*math.cos(3*omega*J)+3.7872*math.sin(omega*J)+0.03250*math.sin(2*omega*J)+0.07187*math.sin(3*omega*J))
    #delta = math.radians(0.006918-0.399912*math.cos(omega*J)-0.006758*math.cos(2*omega*J)-0.002697*math.cos(3*omega*J)+0.070257*math.sin(omega*J)+0.000907*math.sin(2*omega*J)+0.001480*math.sin(3*omega*J))

    # 均時差（天球上を一定な速さで動くと考えた平均太陽と、実際の太陽との移動の差、17分未満）
    e = 0.0072*math.cos(omega*J)-0.0528*math.cos(2*omega*J)-0.0012*math.cos(3*omega*J)-0.1229*math.sin(omega*J)-0.1565*math.sin(2*omega*J)-0.0041*math.sin(3*omega*J)

    Ts = standard_time # 時刻（中央標準時）
    theta = east_longitude # 東経
    phi = math.radians(north_latitude) # 北緯
    T = Ts + (theta-135)/15+e
    t = math.radians(15*T-180) # 時角

    # 高度（仰角）
    alpha = math.asin(math.sin(phi)*math.sin(delta)+math.cos(phi)*math.cos(delta)*math.cos(t))

    ## 方位角（北 = 0, 東 = 90, 南 = 180, 西 = 270°）
    #sin_beta = math.cos(delta)*math.sin(t)/math.cos(alpha)
    #cos_beta = (math.sin(alpha)*math.sin(phi)-math.sin(delta))/math.cos(alpha)/math.cos(delta)
    #beta = math.atan2(sin_beta, cos_beta)+math.pi

    t = math.degrees(math.acos(-math.tan(delta)*math.tan(phi)))

    # 日の出時刻
    T1 = (-t+180)/15
    t1 = T1-(theta-135)/15-e

    # 日の入り時刻
    T2 = (t+180)/15
    t2 = T2-(theta-135)/15-e

    ## 南中時刻（太陽が真南に来る時刻）、計算方法は2通り
    #tm = (t1+t2)/2
    ##tm = 12-(theta-135)/15-e

    # 可照時間
    S0 = t2-t1
    
    r = 1.000110+0.034221*math.cos(omega*J)+0.001280*math.sin(omega*J)+0.000719*math.cos(2*omega*J)+0.000077*math.sin(2*omega*J)
    
    # 大気外水平面日射量（MJ/m2/日）、地球の大気圏外で受け取る太陽からの輻射エネルギー：1.367kW/m2（太陽定数）の水平面成分
    Q0 = 1.367*r*math.sin(alpha)

    # 全天日射量（MJ/m2/日）
    Qt = (0.198+0.537*(sunshine_duration/S0))*Q0

    a = 0.244
    b = 0.511
    c = 0.118

    if Qt < 0:
        return 0.0

    if sunshine_duration/S0 == 0:
        return 24*Qt*c
    else:
        return 24*Qt*(a+b*(sunshine_duration/S0))

def predict_solar_irradiance(data, east_longitude, north_latitude):
    return solar_irradiance(int(data['month']), data['day'], data['time']/60, east_longitude, north_latitude, data['sunshine_duration'])

def main():
    # 金沢着雪ゼロ列車情報
    kanazawa_no_snow_train = pd.read_csv('./kanazawa_nosnow.csv', header=None)
    kanazawa_no_snow_train = kanazawa_no_snow_train[0].values.tolist()

    # 停車駅の位置情報
    stop_station_location = pd.read_csv('./stop_station_location.csv', index_col=0, encoding='shift_jis')

    # 列車のダイアグラム情報
    diagram = pd.read_csv('./diagram.csv', index_col=0, encoding='shift_jis')

    # 気象情報
    weather = pd.read_csv('./weather.csv', index_col=0, encoding='cp932')
    
    # 雪密度の推定
    weather['snow_density'] = 53.6*np.exp(0.488*weather['気温(℃)'])+37.0

    # 降雪量の推定
    weather['kousetsu'] = 100/weather['snow_density']*weather['降水量(mm)']
    weather.loc[weather['気温(℃)'] > 1, 'kousetsu'] = 0

    # 飛雪フラックスの推定
    weather['snowdrift'] = 4.33*np.exp(-0.0184*weather['snow_density'])*1.3*(weather['風速(m/s)']**2-(0.2)**2)

    # 気象情報から日照時間を推定するモデルを読み込む
    sunshine_duration_model = pickle.load(open('./sunshine_duration_model.sav', 'rb'))


    train_data = pd.read_csv('./train.csv', encoding='shift_jis')
    train_data = train_data[train_data['停車駅名'] == '富山'] # 富山停車時の着雪量のデータのみ使用
    train_data = train_data[['年月日', '列車番号', '合計']]

    train_data.rename(columns={'合計': 'snowfall'}, inplace=True)

    # 金沢着雪ゼロ列車フラグを追加
    train_data['no_snow'] = train_data['列車番号'].isin(kanazawa_no_snow_train)
    train_data['no_snow'] = train_data['no_snow'].map(lambda x: 1 if x else 0)

    # 月日を数値にする、1~3、12月のデータのみ使用
    train_data['month'] = train_data['年月日'].str.split('-').str.get(1)
    train_data.loc[:, 'month'] = pd.to_numeric(train_data['month'])
    train_data['day'] = train_data['年月日'].str.split('-').str.get(2)
    train_data.loc[:, 'day'] = pd.to_numeric(train_data['day'])
    train_data = train_data[(train_data['month'] == 1) | (train_data['month'] == 2) | (train_data['month'] == 3) | (train_data['month'] == 12)]

    # ダイアグラムから、金沢駅、富山駅における時刻を追加
    train_data['kanazawa_time'] = diagram.loc['金沢', train_data['列車番号']].values
    train_data['toyama_time'] = diagram.loc['富山', train_data['列車番号']].values

    kanazawa_weather = weather[weather['地点'] == '金沢']
    toyama_weather = weather[weather['地点'] == '富山']

    src_dimensions = ['気温(℃)', '降水量(mm)', '風速(m/s)', '降雪(cm)', 'snowdrift']
    dst_dimensions = ['temperature', 'precipitation', 'wind_speed', 'kousetsu', 'snowdrift']
    kanazawa_time = train_data['年月日'] + ' ' + train_data['kanazawa_time']
    toyama_time = train_data['年月日'] + ' ' + train_data['toyama_time']

    # 金沢駅における時刻に合わせて気象情報を補間
    for i in range(len(src_dimensions)):
        train_data['kanazawa_'+dst_dimensions[i]] = kanazawa_time.apply(interpolate_weather, weather_data=kanazawa_weather, dimension=src_dimensions[i])
    train_data['kanazawa_weather'] = kanazawa_time.apply(nearest_weather, weather_data=kanazawa_weather, place='kanazawa')

    # 富山駅における時刻に合わせて気象情報を補間
    for i in range(len(src_dimensions)):
        train_data['toyama_'+dst_dimensions[i]] = toyama_time.apply(interpolate_weather, weather_data=toyama_weather, dimension=src_dimensions[i])
    train_data['toyama_weather'] = toyama_time.apply(nearest_weather, weather_data=toyama_weather, place='toyama')

    train_data['kanazawa_sunshine_duration'] = kanazawa_time.apply(interpolate_weather, weather_data=kanazawa_weather, dimension='日照時間(時間)')
    train_data['toyama_sunshine_duration'] = toyama_time.apply(interpolate_weather, weather_data=toyama_weather, dimension='日照時間(時間)')

    # 時刻を数値する
    train_data['kanazawa_time'] = pd.to_numeric(train_data['kanazawa_time'].str.split(':').str.get(0))*60+pd.to_numeric(train_data['kanazawa_time'].str.split(':').str.get(1))
    train_data['toyama_time'] = pd.to_numeric(train_data['toyama_time'].str.split(':').str.get(0))*60+pd.to_numeric(train_data['toyama_time'].str.split(':').str.get(1))

    train_data.drop(['年月日', '列車番号'], axis=1, inplace=True)

    # 金沢駅における日射量を推定
    kanazawa_solar_irradiance_train_data = train_data[['month', 'day', 'kanazawa_time', 'kanazawa_sunshine_duration']]
    kanazawa_solar_irradiance_train_data = kanazawa_solar_irradiance_train_data.rename(columns={'kanazawa_time':'time', 'kanazawa_sunshine_duration':'sunshine_duration'})
    train_data['kanazawa_solar_irradiance'] = kanazawa_solar_irradiance_train_data[['month', 'day', 'time', 'sunshine_duration']].apply(predict_solar_irradiance, axis=1, east_longitude=stop_station_location.at['金沢', '経度'], north_latitude=stop_station_location.at['金沢', '緯度'])

    # 富山駅における日射量を推定
    toyama_solar_irradiance_train_data = train_data[['month', 'day', 'toyama_time', 'toyama_sunshine_duration']]
    toyama_solar_irradiance_train_data = toyama_solar_irradiance_train_data.rename(columns={'toyama_time':'time', 'toyama_sunshine_duration':'sunshine_duration'})
    train_data['toyama_solar_irradiance'] = toyama_solar_irradiance_train_data[['month', 'day', 'time', 'sunshine_duration']].apply(predict_solar_irradiance, axis=1, east_longitude=stop_station_location.at['富山', '経度'], north_latitude=stop_station_location.at['富山', '緯度'])

    train_data['toyama_time'] = np.sin(2*math.pi*train_data['toyama_time']/1440) # sinにする

    train_data.drop(['kanazawa_time', 'kanazawa_sunshine_duration'], axis=1, inplace=True)

    # 重複データを削除
    train_data = train_data.drop_duplicates()

    train_data_X, train_data_y = train_data.drop('snowfall', axis=1), train_data['snowfall']


    test_data = pd.read_csv('./test.csv', encoding='shift_jis')

    # 金沢着雪ゼロ列車フラグを追加
    test_data['no_snow'] = test_data['列車番号'].isin(kanazawa_no_snow_train)
    test_data['no_snow'] = test_data['no_snow'].map(lambda x: 1 if x else 0)

    # 月日を数値にする
    test_data['month'] = test_data['年月日'].str.split('-').str.get(1)
    test_data.loc[:, 'month'] = pd.to_numeric(test_data['month'])
    test_data['day'] = test_data['年月日'].str.split('-').str.get(2)
    test_data.loc[:, 'day'] = pd.to_numeric(test_data['day'])

    # ダイアグラムから、金沢駅、富山駅における時刻を追加
    test_data['kanazawa_time'] = diagram.loc['金沢', test_data['列車番号']].values
    test_data['toyama_time'] = diagram.loc['富山', test_data['列車番号']].values

    src_dimensions = ['気温(℃)', '降水量(mm)', '風速(m/s)', '相対湿度(％)', 'kousetsu', 'snowdrift']
    dst_dimensions = ['temperature', 'precipitation', 'wind_speed', 'humidity', 'kousetsu', 'snowdrift']
    kanazawa_time = test_data['年月日'] + ' ' + test_data['kanazawa_time']
    toyama_time = test_data['年月日'] + ' ' + test_data['toyama_time']

    # 金沢駅における時刻に合わせて気象情報を補間
    for i in range(len(src_dimensions)):
        test_data['kanazawa_'+dst_dimensions[i]] = kanazawa_time.apply(interpolate_weather, weather_data=kanazawa_weather, dimension=src_dimensions[i])
    test_data['kanazawa_weather'] = kanazawa_time.apply(nearest_weather, weather_data=kanazawa_weather, place='kanazawa')

    # 富山駅における時刻に合わせて気象情報を補間
    for i in range(len(src_dimensions)):
        test_data['toyama_'+dst_dimensions[i]] = toyama_time.apply(interpolate_weather, weather_data=toyama_weather, dimension=src_dimensions[i])
    test_data['toyama_weather'] = toyama_time.apply(nearest_weather, weather_data=toyama_weather, place='toyama')

    # 時刻を数値にする
    test_data['kanazawa_time'] = pd.to_numeric(test_data['kanazawa_time'].str.split(':').str.get(0))*60+pd.to_numeric(test_data['kanazawa_time'].str.split(':').str.get(1))
    test_data['toyama_time'] = pd.to_numeric(test_data['toyama_time'].str.split(':').str.get(0))*60+pd.to_numeric(test_data['toyama_time'].str.split(':').str.get(1))

    # 日照時間を推定
    test_data['kanazawa_sunshine_duration'] = sunshine_duration_model.predict(test_data[['month', 'day', 'kanazawa_time', 'kanazawa_temperature', 'kanazawa_precipitation', 'kanazawa_wind_speed', 'kanazawa_humidity', 'kanazawa_weather']])
    test_data['toyama_sunshine_duration'] = sunshine_duration_model.predict(test_data[['month', 'day', 'toyama_time', 'toyama_temperature', 'toyama_precipitation', 'toyama_wind_speed', 'toyama_humidity', 'toyama_weather']])

    # 金沢駅における日射量を推定
    kanazawa_solar_irradiance_test_data = test_data[['month', 'day', 'kanazawa_time', 'kanazawa_sunshine_duration']]
    kanazawa_solar_irradiance_test_data = kanazawa_solar_irradiance_test_data.rename(columns={'kanazawa_time':'time', 'kanazawa_sunshine_duration':'sunshine_duration'})
    test_data['kanazawa_solar_irradiance'] = kanazawa_solar_irradiance_test_data[['month', 'day', 'time', 'sunshine_duration']].apply(predict_solar_irradiance, axis=1, east_longitude=stop_station_location.at['金沢', '経度'], north_latitude=stop_station_location.at['金沢', '緯度'])

    # 富山駅における日射量を推定
    toyama_solar_irradiance_test_data = test_data[['month', 'day', 'toyama_time', 'toyama_sunshine_duration']]
    toyama_solar_irradiance_test_data = toyama_solar_irradiance_test_data.rename(columns={'toyama_time':'time', 'toyama_sunshine_duration':'sunshine_duration'})
    test_data['toyama_solar_irradiance'] = toyama_solar_irradiance_test_data[['month', 'day', 'time', 'sunshine_duration']].apply(predict_solar_irradiance, axis=1, east_longitude=stop_station_location.at['富山', '経度'], north_latitude=stop_station_location.at['富山', '緯度'])

    test_data['toyama_time'] = np.sin(2*math.pi*test_data['toyama_time']/1440) # sinに変換

    test_data.drop(['年月日', '列車番号', 'kanazawa_time', 'kanazawa_humidity', 'toyama_humidity', 'kanazawa_sunshine_duration'], axis=1, inplace=True)
    test_data.drop(test_data.columns[[0]], axis=1, inplace=True)

    # LightGBMで訓練
    clf = lgbm.LGBMRegressor(
            random_state = 0,
            verbosity = 1,
            bagging_seed = 0,
            boost_from_average = 'true',
            boost = 'gbdt',
            metric = 'rmse',
            bagging_freq = 5,
            min_data_in_leaf = 43,
            max_depth = 14,
            learning_rate = 0.09915863732263663,
            num_leaves = 86,
            num_threads = 10,
            min_sum_hessian_in_leaf = 4,
            lambda_l1 = 7.669881139878923e-08,
            lambda_l2 = 4.989401635878798e-06,
            feature_fraction = 0.40333387959374234,
            bagging_fraction = 0.9543658284144003,
            min_child_samples = 62
    )
    clf.fit(train_data_X, train_data_y)

    pred = clf.predict(test_data)
    pred = [x if x > 0 else 0 for x in pred]

    # 提出ファイルに出力する
    submit = pd.read_csv('./sample_submit.csv', header=None)
    submit[1] = pred
    submit.to_csv('./submit.csv', index=False, header=False)

if __name__ == '__main__':
    main()