import pandas as pd
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
from statsmodels.stats.multicomp import pairwise_tukeyhsd

data = pd.read_csv('data.csv')

mean = data.mean(axis = 0)
mean = mean.sort_values()

anova = stats.f_oneway(data['qs1'],data['qs2'],data['qs3'],data['qs4'],data['qs5'],data['merge1'],data['partition_sort'])

melt_data = pd.melt(data)
posthoc = pairwise_tukeyhsd(melt_data['value'], melt_data['variable'], alpha=0.05)

#output
print('Here is the means of the runtimes for these 7 sorting methods in ascending order:')
print(mean)
print('The ANOVA pvalue is:', anova.pvalue, 'meaning there is a difference among the means of runtimes of different sorting methods.')
print('Here is the posthoc table')
print(posthoc)
