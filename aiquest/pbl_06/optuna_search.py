import math
import optuna
import pandas as pd
import numpy as np
import lightgbm as lgbm
from sklearn.model_selection import train_test_split

def WMAE_score_func(y_true, y_pred):
    v = sum([1+abs(10000*y) for y in y_true])
    w = [(1+abs(10000*y))/v for y in y_true]

    return sum([w*abs(y-y_hat) for (w, y, y_hat) in zip(w, y_true, y_pred)])

def main():
    train_data = pd.read_csv('./train_data.csv', index_col=0)

    train_data_X, train_data_y = train_data.drop('y', axis=1), train_data['y']

    train_X, test_X, train_y, test_y = train_test_split(train_data_X, train_data_y, test_size=0.25, random_state=0)

    def opt(trial):
        #scale_pos_weight = trial.suggest_uniform('scale_pos_weight',6.0,8.0)
        bagging_freq = trial.suggest_int('bagging_freq',1,10)
        min_data_in_leaf = trial.suggest_int('min_data_in_leaf',2,100)
        max_depth = trial.suggest_int('max_depth',4,20)
        learning_rate = trial.suggest_loguniform('learning_rate',0.001,0.1)
        num_leaves = trial.suggest_int('num_leaves',2,200)
        num_threads = trial.suggest_int('num_threads',1,20)
        min_sum_hessian_in_leaf = trial.suggest_int('min_sum_hessian_in_leaf',1,10)
        lambda_l1 = trial.suggest_loguniform('lambda_l1', 1e-8, 10.0)
        lambda_l2 = trial.suggest_loguniform('lambda_l2', 1e-8, 10.0)
        feature_fraction = trial.suggest_uniform('feature_fraction', 0.4, 1.0)
        bagging_fraction = trial.suggest_uniform('bagging_fraction', 0.4, 1.0)
        min_child_samples = trial.suggest_int('min_child_samples', 5, 100)

        lightgbm_tuna = lgbm.LGBMRegressor(
            random_state = 0,
            verbosity = 1,
            bagging_seed = 0,
            boost_from_average = 'true',
            boost = 'gbdt',
            metric = 'rmse',
            bagging_freq = bagging_freq,
            min_data_in_leaf = min_data_in_leaf,
            max_depth = max_depth,
            learning_rate = learning_rate,
            num_leaves = num_leaves,
            num_threads = num_threads,
            min_sum_hessian_in_leaf = min_sum_hessian_in_leaf,
            lambda_l1 = lambda_l1,
            lambda_l2 = lambda_l2,
            feature_fraction = feature_fraction,
            bagging_fraction = bagging_fraction,
            min_child_samples = min_child_samples
        )
        lightgbm_tuna.fit(train_X, train_y)
        pred = lightgbm_tuna.predict(test_X)
        return WMAE_score_func(test_y.values.tolist(), pred)

    study = optuna.create_study(direction='minimize')
    study.optimize(opt, n_trials=100)

    print(" ")
    print(study.best_params)
    print(study.best_value)
    print(study.best_trial)

if __name__ == '__main__':
    main()