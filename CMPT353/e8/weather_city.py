import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score
from sklearn.preprocessing import FunctionTransformer
from sklearn.pipeline import make_pipeline
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.preprocessing import MinMaxScaler, StandardScaler


data = pd.read_csv(sys.argv[1])
data_unlabelled = pd.read_csv(sys.argv[2])
del data_unlabelled['city']
del data_unlabelled['year']

city_data = data['city']
del data['city']
del data['year']
X = data.copy()
X_test, X_train, y_test, y_train = train_test_split(X, city_data)

# C = 2
# C = 3
C = 4
# C = 5
# C = 6
# C = 20
N = 25

# NB = make_pipeline(
#     StandardScaler(),
#     GaussianNB()
# )
# NB.fit(X_train, y_train)
# print(NB.score(X_test, y_test))


# KNN_model = make_pipeline(
#     StandardScaler(),
#     KNeighborsClassifier(n_neighbors=N)
# )
# KNN_model.fit(X_train, y_train)
# print(KNN_model.score(X_test, y_test))
# print(N)


SVC_model = make_pipeline(
    StandardScaler(),
    SVC(C = C)
)
SVC_model.fit(X_train, y_train)
print('Current model using: SVC \nthe score is:', SVC_model.score(X_test, y_test))

predictions = SVC_model.predict(data_unlabelled)
pd.Series(predictions).to_csv(sys.argv[3], index=False, header=False)

check = pd.DataFrame({'truth': y_test, 'prediction': SVC_model.predict(X_test)})
print(check[check['truth'] != check['prediction']])

#print(predictions)
# print(check)
