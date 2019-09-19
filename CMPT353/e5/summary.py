import matplotlib.pyplot as plt
from scipy import stats
import pandas as pd
import numpy as np


data1 = pd.read_csv('data-1.csv')
data2 = pd.read_csv('data-2.csv')
data3 = pd.read_csv('data-3.csv')
data4 = pd.read_csv('data-4.csv')
data5 = pd.read_csv('data-5.csv')
data6 = pd.read_csv('data-6.csv')

print('data1 mean of x:', data1['x'].mean(), 'y:', data1['y'].mean())
print('data1 SD of x:', data1['x'].std(), 'y:', data1['y'].std())
print('data1 min of x:', data1['x'].min(), 'y:', data1['y'].min())
print('data1 max of x:', data1['x'].max(), 'y:', data1['y'].max())

print('data2 mean of x:', data2['x'].mean(), 'y:', data2['y'].mean())
print('data2 SD of x:',   data2['x'].std(),  'y:', data2['y'].std())
print('data2 min of x:',  data2['x'].min(),  'y:', data2['y'].min())
print('data2 max of x:',  data2['x'].max(),  'y:', data2['y'].max())

print('data3 mean of x:', data3['x'].mean(), 'y:', data3['y'].mean())
print('data3 SD of x:',   data3['x'].std(),  'y:', data3['y'].std())
print('data3 min of x:',  data3['x'].min(),  'y:', data3['y'].min())
print('data3 max of x:',  data3['x'].max(),  'y:', data3['y'].max())

print('data4 mean of x:', data4['x'].mean(), 'y:', data4['y'].mean())
print('data4 SD of x:',   data4['x'].std(),  'y:', data4['y'].std())
print('data4 min of x:',  data4['x'].min(),  'y:', data4['y'].min())
print('data4 max of x:',  data4['x'].max(),  'y:', data4['y'].max())

print('data5 mean of x:', data5['x'].mean(), 'y:', data5['y'].mean())
print('data5 SD of x:',   data5['x'].std(),  'y:', data5['y'].std())
print('data5 min of x:',  data5['x'].min(),  'y:', data5['y'].min())
print('data5 max of x:',  data5['x'].max(),  'y:', data5['y'].max())

print('data6 mean of x:', data6['x'].mean(), 'y:', data6['y'].mean())
print('data6 SD of x:',   data6['x'].std(),  'y:', data6['y'].std())
print('data6 min of x:',  data6['x'].min(),  'y:', data6['y'].min())
print('data6 max of x:',  data6['x'].max(),  'y:', data6['y'].max())


print('The correlation of data1:',stats.linregress(data1['x'], data1['y']).rvalue)
print('The correlation of data2:',stats.linregress(data2['x'], data2['y']).rvalue)
print('The correlation of data3:',stats.linregress(data3['x'], data3['y']).rvalue)
print('The correlation of data4:',stats.linregress(data4['x'], data4['y']).rvalue)
print('The correlation of data5:',stats.linregress(data5['x'], data5['y']).rvalue)
print('The correlation of data6:',stats.linregress(data6['x'], data6['y']).rvalue)
		# https://docs.scipy.org/doc/scipy-0.16.1/reference/generated/scipy.stats.linregress.html

plt.plot(data1['x'], data1['y'], 'b.')
plt.show()
plt.plot(data2['x'], data2['y'], 'b.')
plt.show()
plt.plot(data3['x'], data3['y'], 'b.')
plt.show()
plt.plot(data4['x'], data4['y'], 'b.')
plt.show()
plt.plot(data5['x'], data5['y'], 'b.')
plt.show()
plt.plot(data6['x'], data6['y'], 'b.')
plt.show()






