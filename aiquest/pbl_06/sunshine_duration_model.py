import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import seaborn as sns
from sklearn.model_selection import GridSearchCV
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
from sklearn.metrics import mean_squared_error
from sklearn.ensemble import RandomForestRegressor
from datetime import datetime as dt
from datetime import timedelta
import warnings
import optuna
import pickle

def nearest_weather(data, weather_data):
    d = dt.strptime(data['年月日時'], '%Y/%m/%d %H:%M')
    h = d.hour
    
    th = 0
    if data['地点'] == '金沢':
        if h == 0 or h == 1:
            th = 3
        elif h == 23:
            th = 21
        elif h%3 == 2:
            th = h+1
        else:
            th = h//3*3
    elif data['地点'] == '富山':
        th = (h//6+1)*6-3
    
    d += timedelta(hours=th-h)

    return weather_data[weather_data['地点'] == data['地点']].loc[[d.strftime('%Y/%#m/%#d %#H:00')], ['天気']].values[0][0]

def WMAE_score_func(y_true, y_pred):
    v = sum([1+abs(10000*y) for y in y_true])
    w = [(1+abs(10000*y))/v for y in y_true]

    return sum([w*abs(y-y_hat) for (w, y, y_hat) in zip(w, y_true, y_pred)])

weather = pd.read_csv('./weather.csv', index_col=0, encoding='cp932')

## 2015年1月,2月,3月,12月,2016年1月,2月,3月,12月,金沢,富山
#train_data = weather[(weather.index.str.contains('2015/1/')) 
#                     | (weather.index.str.contains('2015/2/')) 
#                     | (weather.index.str.contains('2015/3/')) 
#                     | (weather.index.str.contains('2015/12/')) 
#                     | (weather.index.str.contains('2016/1/')) 
#                     | (weather.index.str.contains('2016/2/')) 
#                     | (weather.index.str.contains('2016/3/')) 
#                     | (weather.index.str.contains('2016/12/'))]

#train_data = train_data[(train_data['地点']=='富山') | (train_data['地点']=='金沢')]

#train_data.reset_index(inplace=True)
#train_data = train_data[['年月日時', '地点', '気温(℃)', '降水量(mm)', '風速(m/s)', '相対湿度(％)', '天気', '日照時間(時間)']]

#train_data['天気'] = train_data.apply(nearest_weather, axis=1, weather_data=weather)

#train_data['month'] = pd.to_numeric(train_data['年月日時'].str.split(' ').str.get(0).str.split('/').str.get(1))
#train_data['day'] = pd.to_numeric(train_data['年月日時'].str.split(' ').str.get(0).str.split('/').str.get(2))

#train_data['年月日時'] = train_data['年月日時'].str.split(' ').str.get(1)

#train_data['time'] = pd.to_numeric(train_data['年月日時'].str.split(':').str.get(0))*60+pd.to_numeric(train_data['年月日時'].str.split(':').str.get(1))

#train_data = train_data[['month', 'day', 'time', '気温(℃)', '降水量(mm)', '風速(m/s)', '相対湿度(％)', '天気', '日照時間(時間)']]

#train_data.rename(columns={'気温(℃)':'temperature', '降水量(mm)':'precipitation', '風速(m/s)':'wind_speed', '相対湿度(％)':'humidity', '天気':'weather', '日照時間(時間)':'sunshine_duration'}, inplace=True)

#train_data = train_data.drop_duplicates()

#train_data.to_csv('sunshine_duration_train_data.csv')

train_data = pd.read_csv('./sunshine_duration_train_data.csv', index_col=0)

train_data_X, train_data_y = train_data.drop('sunshine_duration', axis=1), train_data['sunshine_duration']

#train_X, test_X, train_y, test_y = train_test_split(train_data_X, train_data_y, test_size=0.25, random_state=0)

def opt(trial):
    n_estimators = trial.suggest_int('n_estimators', 10, 200)
    max_depth = trial.suggest_int('max_depth', 3, 20)
    max_features = trial.suggest_int('max_features', 3, 8)
    min_samples_leaf = trial.suggest_int('min_samples_leaf', 2, 50)
    max_leaf_nodes = trial.suggest_int('max_leaf_nodes', 5, 200)

    clf = RandomForestRegressor(
        random_state = 0,
        n_estimators = n_estimators,
        max_depth = max_depth,
        max_features = max_features,
        min_samples_leaf = min_samples_leaf,
        max_leaf_nodes = max_leaf_nodes
    )
    clf.fit(train_X, train_y)
    pred = clf.predict(test_X)

    return WMAE_score_func(test_y.values.tolist(), pred)

    #return np.sqrt(mean_squared_error(test_y, pred))

#study = optuna.create_study(direction='minimize')
#study.optimize(opt, n_trials=100)

#print(" ")
#print(study.best_params)
#print(study.best_value)
#print(study.best_trial)










#clf = RandomForestRegressor(n_estimators=10, n_jobs=-1, random_state=0)
#parameters = {'max_depth':list(range(6,7,1)), 'max_features':list(range(1,9,1))}
##parameters = {'max_depth':[6, 7, 8], 'max_features':list(range(10,13,1)), 'min_samples_leaf':[6,7,8,9,10,20], 'max_leaf_nodes':[10,20,40,100]}
#gcv = GridSearchCV(clf, parameters, cv=5, scoring='neg_mean_squared_error', return_train_score=True, n_jobs=-1)
#gcv.fit(train_data_X, train_data_y)
#print(gcv.best_score_, gcv.best_params_)


test_data = weather[weather.index.str.contains('2017/1/')
                   | weather.index.str.contains('2017/2/')
                   | weather.index.str.contains('2017/3/')]

test_data = test_data[(test_data['地点']=='富山') | (test_data['地点']=='金沢')]

test_data.reset_index(inplace=True)

test_data['天気'] = test_data.apply(nearest_weather, axis=1, weather_data=weather)

test_data['month'] = pd.to_numeric(test_data['年月日時'].str.split(' ').str.get(0).str.split('/').str.get(1))
test_data['day'] = pd.to_numeric(test_data['年月日時'].str.split(' ').str.get(0).str.split('/').str.get(2))

test_data['年月日時'] = test_data['年月日時'].str.split(' ').str.get(1)

test_data['time'] = pd.to_numeric(test_data['年月日時'].str.split(':').str.get(0))*60+pd.to_numeric(test_data['年月日時'].str.split(':').str.get(1))

test_data_true = test_data[['日照時間(時間)']]

test_data = test_data[['month', 'day', 'time', '気温(℃)', '降水量(mm)', '風速(m/s)', '相対湿度(％)', '天気']]

test_data.rename(columns={'気温(℃)':'temperature', '降水量(mm)':'precipitation', '風速(m/s)':'wind_speed', '相対湿度(％)':'humidity', '天気':'weather'}, inplace=True)



#test_data.to_csv('sunshine_duration_test_data.csv')

#test_data = pd.read_csv('./sunshine_duration_test_data.csv')


#{'n_estimators': 143, 'max_depth': 18, 'max_features': 7, 'min_samples_leaf': 8, 'max_leaf_nodes': 50}
#{'n_estimators': 73, 'max_depth': 19, 'max_features': 8, 'min_samples_leaf': 3, 'max_leaf_nodes': 189}
#{'n_estimators': 162, 'max_depth': 13, 'max_features': 8, 'min_samples_leaf': 2, 'max_leaf_nodes': 165}
#{'n_estimators': 52, 'max_depth': 12, 'max_features': 8, 'min_samples_leaf': 2, 'max_leaf_nodes': 200}
#{'n_estimators': 18, 'max_depth': 15, 'max_features': 8, 'min_samples_leaf': 2, 'max_leaf_nodes': 133}

clf = RandomForestRegressor(n_estimators=143, max_depth=18, max_features=7, min_samples_leaf=8, max_leaf_nodes=50, n_jobs=-1, random_state=0)
#clf = RandomForestRegressor(n_estimators=73, max_depth=19, max_features=8, min_samples_leaf=3, max_leaf_nodes=189, n_jobs=-1, random_state=0)
#clf = RandomForestRegressor(n_estimators=162, max_depth=13, max_features=8, min_samples_leaf=2, max_leaf_nodes=165, n_jobs=-1, random_state=0)
#clf = RandomForestRegressor(n_estimators=18, max_depth=15, max_features=8, min_samples_leaf=2, max_leaf_nodes=133, n_jobs=-1, random_state=0)
clf.fit(train_data_X, train_data_y)

#pickle.dump(clf, open('sunshine_duration_model.sav', 'wb'))

#clf = pickle.load(open('sunshine_duration_model.sav', 'rb'))

pred = clf.predict(test_data)
print('RMSE', np.sqrt(mean_squared_error(test_data_true, pred)))
print(clf.score(test_data, test_data_true.values.tolist()))

fig, ax = plt.subplots(figsize=(16, 9), dpi=300)
plt.rcParams['font.family'] = 'arial'
rc('font', weight='bold')
ax.grid(True, 'major', 'y', ls='--', lw=.5, c='k', alpha=.3)
ax.tick_params(bottom=False)

ax.plot(pred[100:400], label='Predicted')
ax.plot(test_data_true.values.tolist()[100:400], label='True')

ax.xaxis.labelpad = 15
ax.set_xlabel('Time', weight='bold', fontsize=28, family='arial')
ax.set_xticks([])

ax.set_ylabel('Sunshine duration [h]', weight='bold', fontsize=28, family='arial')
ax.set_ylim([0.0, 1.0])
plt.yticks([0.0, 0.2, 0.4, 0.6, 0.8, 1.0], weight='bold', fontsize=24, family='arial')

plt.legend(loc='upper', fontsize=24, ncol=2)

plt.savefig('sunshine_duration_result.svg', bbox_inches='tight', pad_inches=0.05)

#RMSE 0.17700875364877486
#0.6737384773122393

#RMSE 0.16880923913719978
#0.7032649858238033

plt.show()