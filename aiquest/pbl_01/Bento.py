import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import mean_squared_error
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import ElasticNet
from scipy.optimize import curve_fit
import warnings

def sales_num_graph():
    train_data = pd.read_csv('./train.csv')

    fig, ax = plt.subplots(dpi=300)
    plt.rcParams['font.family'] = 'arial'
    ax.tick_params(bottom=False)
    
    ax.plot(train_data['datetime'], train_data['y'])
    ax.set_xticklabels([])
    ax.set_ylabel('The number of sales', weight='bold', fontsize=18, family='arial')
    
    plt.savefig('number_of_sales.svg', bbox_inches='tight', pad_inches=0.05)

def kcal_graph():
    train_data = pd.read_csv('./train.csv', index_col='datetime')

    fig, ax = plt.subplots(dpi=300)
    plt.rcParams['font.family'] = 'arial'
    ax.grid(True, 'major', 'x', ls='--', lw=0.5, color='k', alpha=0.5)
    ax.grid(True, 'major', 'y', ls='--', lw=0.5, color='k', alpha=0.5)

    plt.scatter(train_data['kcal'], train_data['y'])

    ax.set_yticks([30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140])
    ax.set_ylabel('The number of sales', weight='bold', fontsize=18, family='arial')

    ax.set_xticks([320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460])
    ax.set_xlabel('Kcal', weight='bold', fontsize=18, family='arial')

    plt.savefig('kcal.svg', bbox_inches='tight', pad_inches=0.05)

def exciting_menu_graph():
    train_data = pd.read_csv('./train.csv', index_col='datetime')

    fig, ax = plt.subplots(dpi=300)
    plt.rcParams['font.family'] = 'arial'

    fun = train_data.loc[(train_data['remarks'].notnull()) & (train_data['remarks'] == 'お楽しみメニュー'), ['y']].values
    no_fun = train_data.loc[(train_data['remarks'].notnull()) & (train_data['remarks'] != 'お楽しみメニュー'), ['y']].values
    
    ax.boxplot([fun, no_fun])
    
    ax.set_ylabel('The number of sales', weight='bold', fontsize=18, family='arial')
    ax.set_xticklabels(['Exciting menu', 'Other special menus'], family='arial')

    plt.savefig('exciting_menu.svg', bbox_inches='tight', pad_inches=0.05)

def func(x, a, b, c):
    return a*np.exp(-b*x)+c

def main():
    warnings.filterwarnings('ignore')
    pd.get_option("display.max_columns")
    pd.set_option('display.max_columns', 50)

    # 時系列に訓練データを取ってきて、指数関数のフィッティングを行う
    train_data = pd.read_csv('./train.csv')
   
    xs = train_data.index.values
    ys = train_data['y'].values

    popt, pcov = curve_fit(func, xs, ys)

    a, b, c = popt
    y_reg = a*np.exp(-b*xs)+c
    

    train_data = pd.read_csv('./train.csv', index_col='datetime')
    test_data = pd.read_csv('./test.csv', index_col='datetime')

    train_data['flg'] = 1
    test_data['flg'] = 0

    train_data['y'] = train_data['y'] - y_reg

    all_data = pd.concat([train_data, test_data], axis=0, sort=False)

    all_data['kcal'] = all_data['kcal'].fillna(train_data['kcal'].mean())

    all_data['payday'] = all_data['payday'].fillna(0)

    all_data['event'] = all_data['event'].fillna('なし')

    all_data.loc[all_data['remarks'] != 'お楽しみメニュー', 'remarks'] = 'なし'

    all_data['week'] = all_data['week'].replace(all_data.groupby('week').y.median())

    all_data['weather'] = all_data['weather'].replace(all_data.groupby('weather').y.median())

    all_data.loc[all_data['precipitation'] == '--', 'precipitation'] = '-1'
    all_data['precipitation'] = pd.to_numeric(all_data['precipitation'])

    all_data = pd.get_dummies(all_data, drop_first=True)

    train_data = all_data.query('flg == 1')
    test_data = all_data.query('flg == 0')

    train_data.drop(['flg'], axis=1, inplace=True)
    test_data.drop(['flg', 'y'], axis=1, inplace=True)

    train_data_X, train_data_y = train_data.drop('y', axis=1), train_data['y']

    # ElasticNetモデル
    #elastic_net = ElasticNet(random_state=0, max_iter=100000)
    #parameters = {'alpha':[0.02,0.019,0.018,0.017,0.016,0.015,0.014,0.013,0.012,0.011,0.01,0.005], 'l1_ratio':[0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9]}
    #gcv = GridSearchCV(elastic_net, parameters, cv=5, scoring='neg_mean_squared_error', return_train_score=True, n_jobs=-1)
    #gcv.fit(train_data_X, train_data_y)
    #print(gcv.best_params_)

    elastic_net = ElasticNet(alpha=0.000000001, l1_ratio=0.5, random_state=0, max_iter=1000000)
    elastic_net.fit(train_data_X, train_data_y)
    pred = elastic_net.predict(train_data_X)
    print('RMSE', np.sqrt(mean_squared_error(train_data_y, pred)))
    p = pd.DataFrame({"actual":train_data_y, "pred":pred})
    p.plot()
    plt.show()

    # 重回帰モデル
    #linear = LinearRegression(n_jobs=-1)
    #linear.fit(train_data_X, train_data_y)
    #pred = linear.predict(train_data_X)
    #print('RMSE', np.sqrt(mean_squared_error(train_data_y, pred)))
    #p = pd.DataFrame({"actual":train_data_y, "pred":pred})
    #p.plot()
    #plt.show()

    #pred = linear.predict(test_data)
    pred = elastic_net.predict(test_data)

    x = np.arange(xs[-1]+1, xs[-1]+test_data.shape[0]+1)
    y_reg = a*np.exp(-b*x)+c
    pred += y_reg

    submit = pd.read_csv('./sample_submit.csv', header=None)
    submit[1] = pred
    submit.to_csv('./submit.csv', index=False, header=False)

if __name__ == '__main__':
    main()
