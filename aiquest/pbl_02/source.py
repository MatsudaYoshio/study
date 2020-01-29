import pandas as pd
from sklearn.preprocessing import LabelEncoder
import lightgbm as lgbm

def main():
    # 訓練データとテストデータを読み込む
    train_data = pd.read_csv('./train.csv', index_col='id')
    test_data = pd.read_csv('./test.csv', index_col='id')

    train_data = train_data.drop_duplicates() # 重複データの削除

    # 訓練データとテストデータにフラグをつけた後に一つのデータに合わせる
    train_data['flg'] = 1
    test_data['flg'] = 0
    all_data = pd.concat([train_data, test_data], axis=0, sort=False)

    # "term"を3か5の数字にする
    all_data.loc[:, 'term'] = all_data['term'].str.split(' ').str.get(0)
    all_data.loc[:, 'term'] = pd.to_numeric(all_data['term'])

    all_data.loc[:, 'employment_length'] = all_data['employment_length'].str.split(' ').str.get(0)
    all_data.loc[:, 'employment_length'] = pd.to_numeric(all_data['employment_length']) # "employment_length"を数値にする

    all_data.loc[all_data['purpose'] == 'educational', 'purpose'] = 'other' # "purpose"の"educational"を"other"に含める
   
    # ラベルエンコードする
    le = LabelEncoder()
    all_data.loc[:, 'purpose'] = le.fit_transform(all_data['purpose'].values)
    all_data.loc[:, 'application_type'] = le.fit_transform(all_data['application_type'].values)
    all_data.loc[:, 'grade'] = le.fit_transform(all_data['grade'].values)

    # "loan_status"で"ChargedOff"を1、それ以外を0にする
    all_data.loc[all_data['loan_status'] != 'ChargedOff', 'loan_status'] = 0
    all_data.loc[all_data['loan_status'] == 'ChargedOff', 'loan_status'] = 1

    # 訓練データとテストデータに戻す
    train_data = all_data.query('flg == 1')
    test_data = all_data.query('flg == 0')

    train_data = train_data.drop(['flg'], axis=1)
    test_data = test_data.drop(['flg', 'loan_status'], axis=1)

    train_data_X, train_data_y = train_data.drop('loan_status', axis=1), train_data['loan_status']

    # lightGBMで学習して予測する
    clf = lgbm.LGBMClassifier(
            random_state=0,
            verbosity=1,
            bagging_seed=0,
            boost_from_average='true',
            boost='gbdt',
            metric='auc',
            scale_pos_weight=6.126082824966007,
            bagging_freq=6,
            min_data_in_leaf=12,
            max_depth=20,
            learning_rate=0.02446105502742414,
            num_leaves=154,
            num_threads=20,
            min_sum_hessian_in_leaf=10,
            lambda_l1=1.1831513783644946e-05,
            lambda_l2=0.00027986289682016015,
            feature_fraction=0.6583930205490401,
            bagging_fraction=0.8901118065688907,
            min_child_samples=38
    )
    clf.fit(train_data_X, train_data_y)
    pred = clf.predict(test_data)

    # 提出ファイルに出力する
    submit = pd.read_csv('./sample_submit.csv', header=None)
    submit[1] = pred
    submit.to_csv('./submit.csv', index=False, header=False)

if __name__ == '__main__':
    main()