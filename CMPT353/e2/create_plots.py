import pandas as pd
import sys
import matplotlib.pyplot as plt

filename1 = sys.argv[1]
filename2 = sys.argv[2]

data1 = pd.read_csv(filename1, sep=' ', header=None, index_col=1, names=['lang', 'page', 'views', 'bytes'])
sorted1 = data1.sort_values(by = ['views'], ascending = False)

data2 = pd.read_csv(filename2, sep=' ', header=None, index_col=1, names=['lang', 'page', 'views', 'bytes'])
data1['views2'] = data2['views']

plt.figure(figsize=(10, 5)) # change the size to something sensible
plt.subplot(1, 2, 1)        # subplots in 1 row, 2 columns, select the first
plt.plot(sorted1['views'].values)           # build plot 1
plt.title('Popularity Distribution')
plt.xlabel('Rank')
plt.ylabel('Views')

plt.subplot(1, 2, 2)        # ... and then select the second
plt.xscale('log')
plt.yscale('log')
plt.plot(data1['views'], data1['views2'], 'b.')                 # build plot 2
plt.title('Daily Correlation')
plt.xlabel('Day 1 Views')
plt.ylabel('Day 2 Views')
plt.savefig('wikipedia.png')











