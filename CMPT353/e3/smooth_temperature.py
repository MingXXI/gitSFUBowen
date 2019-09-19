from statsmodels.nonparametric.smoothers_lowess import lowess
from pandas.plotting import register_matplotlib_converters 
register_matplotlib_converters()
from pykalman import KalmanFilter
import matplotlib.pyplot as plt
import statsmodels.api as sm
import scipy.stats as stats
import pandas as pd
import numpy as np
import sys

def to_timestamp(d):
    return d.timestamp()



filename = sys.argv[1]
cpu_data = pd.read_csv(filename, sep=',', header=0, parse_dates= ['timestamp'])
cpu_data['processed_timestamp'] = cpu_data['timestamp'].apply(to_timestamp)

loess_smoothed = lowess(cpu_data['temperature'], cpu_data['timestamp'], frac = 0.01)
plt.figure(figsize=(12, 4))
plt.plot(cpu_data['processed_timestamp'], cpu_data['temperature'], 'b.', alpha=0.5)
plt.plot(cpu_data['processed_timestamp'], loess_smoothed[:, 1], 'r-')

kalman_data = cpu_data[['temperature', 'cpu_percent', 'sys_load_1']]

initial_state = kalman_data.iloc[0]
observation_covariance = np.diag([1.25, 1.25, 1.25]) ** 2 # TODO: shouldn't be zero
transition_covariance = np.diag([0.2, 0.2, 0.2]) ** 2 # TODO: shouldn't be zero
transition = [[1, -1, 0.7], [0, 0.6, 0.03], [0, 1.3, 0.8]] # TODO: shouldn't (all) be zero

kf = KalmanFilter(initial_state_mean = initial_state, initial_state_covariance = observation_covariance, observation_covariance = observation_covariance, transition_covariance = transition_covariance, transition_matrices = transition)
kalman_smoothed, _ = kf.smooth(kalman_data)
plt.plot(cpu_data['processed_timestamp'], kalman_smoothed[:, 0], 'g-', alpha=0.5)
plt.legend(['CPU Data', 'LOESS Smoothing', 'Kalman Smoothing'])
# plt.show() # maybe easier for testing
plt.savefig('cpu.svg')