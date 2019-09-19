from implementations import all_implementations
import pandas as pd
import numpy as np
import time


#creates a random arrays with 5000 entries
rand_array = np.random.rand(5000)

#N is the number of times to run each method
N = 150

#initialize an numpy array to store runtimes for each method
record = np.zeros((7,N))

#This is to indicate which method is used
sort_num = 0

#for loop to test for runtimes and store the values
for sort in all_implementations:
    for i in range(0,N):
        st = time.time()
        res = sort(rand_array)
        en = time.time()
        record[sort_num][i]= en-st
    sort_num += 1
    
#convert numpy array to pandas dataframe and output csv file
record = np.transpose(record)
data = pd.DataFrame(record, columns = ['qs1','qs2','qs3','qs4','qs5','merge1','partition_sort'])
data.to_csv('data.csv', index=False)

