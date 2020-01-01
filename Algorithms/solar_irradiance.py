import math

'''
日照時間から全天日射量を推定
http://www.enjoy.ne.jp/~k-ichikawa/sunShineTime4.html
http://sigbox.web.fc2.com/calc/calc2.html
'''

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

    return Qt

def main():
    print(solar_irradiance(12, 1, 12, 137.213608, 36.70132153, 0))
        
if __name__ == '__main__':
    main()