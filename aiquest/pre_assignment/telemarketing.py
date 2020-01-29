import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pydotplus
import io
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import roc_auc_score
from sklearn.metrics import roc_curve
from sklearn.metrics import accuracy_score
from sklearn.metrics import precision_score
from sklearn.metrics import recall_score
from sklearn.metrics import f1_score
from sklearn.tree import DecisionTreeClassifier as DT
from sklearn.tree import export_graphviz
from sklearn.ensemble import RandomForestClassifier
from PIL import Image

'''
print(df.info()) # データのカラム情報の表示
print(df.shape) # データの（行，列）を表示
print(df.head()) # データの先頭5行を表示
print(df.loc[[1, 2], ['age', 'balance', 'loan']]) # 複数の行，列を選んで表示

print(df.describe()) # 数値型データの基本統計量を表示
print(df.describe(include=['O'])) # オブジェクト型データの基本統計量を表示
print(df['poutcome'].value_counts()) # カラムpoutcomeの要素の種類と出現数を表示
print(pd.crosstab(df['poutcome'], df['y'], margins=True)) # クロス集計
    
#相関関係
corr_matrix = df.corr()
print(corr_matrix) # 量的データの相関係数の表示
sns.heatmap(corr_matrix) # ヒートマップで相関関係を可視化
plt.title('correlation')
plt.show()

# ヒストグラム
duration_0 = df[df['y']==0]['duration']
duration_1 = df[df['y']==1]['duration']
sns.distplot(duration_0, label='y=0')
sns.distplot(duration_1, label='y=1')
plt.title('duration histgram')
plt.xlabel('duration')
plt.ylabel('frequency')
plt.xlim(0,1000)
plt.legend()
plt.show()

# 順序特徴量のマッピング
mapping = {'primary': 1, 'secondary': 2, 'tertiary': 3}
df['education'] = df['education'].map(mapping)
# 元に戻す
inverse_mapping = {v: k for k, v in mapping_dict.items()}
df['education'] = df['education'].map(inverse_mapping)

# Label Encoding
le = LabelEncoder()
df['loan'] = le.fit_transform(df['loan'].values)
df['loan'] = le.inverse_transform(df['loan']) # 元に戻す

# One Hot Encoding
df = pd.get_dummies(df) # One Hot Encoding
df = pd.get_dummies(df, drop_first=True) # One Hot Encoding（多重共線性回避のために特徴量の一列を削除）
'''

def my_preprocessing(dataframe):
    return pd.get_dummies(dataframe, drop_first=True)

def show_feature_importance(train_X, tree_model):
    print(pd.Series(tree_model.feature_importances_, index=train_X.columns))

    features_num = train_X.shape[1]
    plt.barh(range(features_num), tree_model.feature_importances_, align='center')
    plt.yticks(np.arange(features_num), train_X.columns)
    plt.xlabel('Feature imporatance')
    plt.ylabel('Feature')
    plt.show()

def show_tree_graph(train_X, tree_model):
    export_graphviz(tree_model, out_file='tree_dot', feature_names=train_X.columns, class_names=['0', '1'], filled=True, rounded=True)
    g = pydotplus.graph_from_dot_file(path='tree_dot')
    gg = g.create_png()
    img = io.BytesIO(gg)
    img2 = Image.open(img)

    plt.figure(figsize=(img2.width/100, img2.height/100), dpi=100)
    plt.imshow(img2)
    plt.axis('off')
    plt.show()

def evaluate_model(test_X, test_y, model):
    pred = model.predict(test_X)

    print('accuracy score:', accuracy_score(test_y, pred))
    print('precision score:', precision_score(test_y, pred))
    print('recall score:', recall_score(test_y, pred))
    print('f score:', f1_score(test_y, pred))

    pred = model.predict_proba(test_X)[:, 1]
    auc = roc_auc_score(test_y, pred)
    print('ROC AUC score:', auc)

    # ROC曲線の描画
    fpr, tpr, thresholds = roc_curve(test_y, pred)
    plt.plot(fpr, tpr, label='ROC(AUC={:.2})'.format(auc))
    plt.plot([0, 1], [0, 1], color='black', ls='dashed')
    plt.title('ROC')
    plt.xlabel('FOR')
    plt.ylabel('TPR')
    plt.xlim(0, 1)
    plt.ylim(0, 1)
    plt.legend()
    plt.show()

def main():
    df = pd.read_csv('data.csv', index_col='id')
    df = my_preprocessing(df)

    data_X, data_y = df.drop('y', axis=1), df['y']
    
    train_X, test_X, train_y, test_y = train_test_split(data_X, data_y, test_size=0.25, random_state=0)

    tree = DT(random_state=0)
    parameters = {'max_depth':np.arange(2,11)}
    gcv = GridSearchCV(tree, parameters, cv=5, scoring='roc_auc', return_train_score=True, n_jobs=-1)
    gcv.fit(data_X, data_y)
    print(gcv.best_params_)
    best_tree = gcv.best_estimator_

    forest = RandomForestClassifier(random_state=0)
    parameters = {'max_depth':np.arange(2,11)}
    gcv = GridSearchCV(forest, parameters, cv=5, scoring='roc_auc', return_train_score=True, n_jobs=-1)
    gcv.fit(data_X, data_y)
    print(gcv.best_params_)
    best_forest = gcv.best_estimator_

    test_data = pd.read_csv('test.csv', index_col='id')
    test_data my_preprocessing(test_data)

    pred = best_forest.predict_proba(test_data)[:, 1]

    submit = pd.read_csv('../input/sample_submission.csv', header=None)
    submit[1] = pred
    submit.to_csv('submit.csv', index=False, header=False)

if __name__ == '__main__':
    main()