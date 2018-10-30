import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import Ridge

def main():
    X = np.loadtxt("./data/party_data.csv", delimiter=',', skiprows=1)
    y = np.loadtxt("./data/target_money.txt")
   
    X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=48)

    ridge = Ridge(alpha=0.0001).fit(X_train, y_train)

    print("Training set score: {:.2f}".format(ridge.score(X_train, y_train)))
    print("Test set score: {:.2f}".format(ridge.score(X_test, y_test)))
    
    print(ridge.predict(np.array([[5,5,3,29000]])))

if __name__ == '__main__':
    main()