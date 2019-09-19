import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from skimage.color import lab2rgb
from sklearn.svm import SVR
from sklearn.neighbors import KNeighborsRegressor
from sklearn.neighbors import KNeighborsClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import FunctionTransformer
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split
from skimage.color import rgb2lab
from sklearn.svm import SVC

import sys


OUTPUT_TEMPLATE = (
    'Bayesian classifier: {bayes_rgb:.3g} {bayes_lab:.3g}\n'
    'kNN classifier:      {knn_rgb:.3g} {knn_lab:.3g}\n'
    'SVM classifier:      {svm_rgb:.3g} {svm_lab:.3g}\n'
)


# representative RGB colours for each label, for nice display
COLOUR_RGB = {
    'red': (255, 0, 0),
    'orange': (255, 114, 0),
    'yellow': (255, 255, 0),
    'green': (0, 230, 0),
    'blue': (0, 0, 255),
    'purple': (187, 0, 187),
    'brown': (117, 60, 0),
    'pink': (255, 187, 187),
    'black': (0, 0, 0),
    'grey': (150, 150, 150),
    'white': (255, 255, 255),
}
name_to_rgb = np.vectorize(COLOUR_RGB.get, otypes=[np.uint8, np.uint8, np.uint8])


def plot_predictions(model, lum=71, resolution=256):
    """
    Create a slice of LAB colour space with given luminance; predict with the model; plot the results.
    """
    wid = resolution
    hei = resolution
    n_ticks = 5

    # create a hei*wid grid of LAB colour values, with L=lum
    ag = np.linspace(-100, 100, wid)
    bg = np.linspace(-100, 100, hei)
    aa, bb = np.meshgrid(ag, bg)
    ll = lum * np.ones((hei, wid))
    lab_grid = np.stack([ll, aa, bb], axis=2)

    # convert to RGB for consistency with original input
    X_grid = lab2rgb(lab_grid)

    # predict and convert predictions to colours so we can see what's happening
    y_grid = model.predict(X_grid.reshape((wid*hei, 3)))
    pixels = np.stack(name_to_rgb(y_grid), axis=1) / 255
    pixels = pixels.reshape((hei, wid, 3))

    # plot input and predictions
    plt.figure(figsize=(10, 5))
    plt.suptitle('Predictions at L=%g' % (lum,))
    plt.subplot(1, 2, 1)
    plt.title('Inputs')
    plt.xticks(np.linspace(0, wid, n_ticks), np.linspace(-100, 100, n_ticks))
    plt.yticks(np.linspace(0, hei, n_ticks), np.linspace(-100, 100, n_ticks))
    plt.xlabel('A')
    plt.ylabel('B')
    plt.imshow(X_grid.reshape((hei, wid, 3)))

    plt.subplot(1, 2, 2)
    plt.title('Predicted Labels')
    plt.xticks(np.linspace(0, wid, n_ticks), np.linspace(-100, 100, n_ticks))
    plt.yticks(np.linspace(0, hei, n_ticks), np.linspace(-100, 100, n_ticks))
    plt.xlabel('A')
    plt.imshow(pixels)

def convert_RGB_to_LAB(X):

    X_LAB = X.copy()
    X_LAB = X_LAB.reshape(1,-1,3)
    X_LAB = rgb2lab(X_LAB)
    X_LAB = X_LAB.reshape(-1,3)

    return X_LAB

def main():
    data = pd.read_csv(sys.argv[1])
    X = data[['R', 'G', 'B']].values / 255
    y = data['Label'].values

    X_valid, X_test, y_valid, y_test = train_test_split(X, y)
    # TODO: create some models
    # NB_rgb
    bayes_rgb_model = GaussianNB()
    bayes_rgb_model.fit(X_valid, y_valid)

    # NB_lab
    bayes_lab_model = make_pipeline(
        FunctionTransformer(convert_RGB_to_LAB),
        GaussianNB()
        )
    bayes_lab_model.fit(X_valid, y_valid)

    # KNN_rgb
    knn_rgb_model = KNeighborsClassifier(n_neighbors=14)
    knn_rgb_model.fit(X_valid, y_valid)

    # KNN_lab
    knn_lab_model = make_pipeline(
        FunctionTransformer(convert_RGB_to_LAB),
        KNeighborsClassifier(n_neighbors=24)
        )
    knn_lab_model.fit(X_valid, y_valid)

    #svm_rgb
    svc_rgb_model = SVC(C = 30, gamma = 'auto')
    svc_rgb_model.fit(X_valid, y_valid)

    #svm_lab
    svc_lab_model = make_pipeline(
        FunctionTransformer(convert_RGB_to_LAB),
        SVC(kernel='linear', C = 20, gamma = 'auto')
        )
    svc_lab_model.fit(X_valid, y_valid)

    # train each model and output image of predictions
    models = [bayes_rgb_model, bayes_lab_model, knn_rgb_model, knn_lab_model, svc_rgb_model, svc_lab_model]
    for i, m in enumerate(models):  # yes, you can leave this loop in if you want.
        m.fit(X_valid, y_valid)
        plot_predictions(m)
        plt.savefig('predictions-%i.png' % (i,))

    print(OUTPUT_TEMPLATE.format(
        bayes_rgb=bayes_rgb_model.score(X_valid, y_valid),
        bayes_lab=bayes_lab_model.score(X_valid, y_valid),
        knn_rgb=knn_rgb_model.score(X_valid, y_valid),
        knn_lab=knn_lab_model.score(X_valid, y_valid),
        svm_rgb=svc_rgb_model.score(X_valid, y_valid),
        svm_lab=svc_lab_model.score(X_valid, y_valid),
    ))


if __name__ == '__main__':
    main()
