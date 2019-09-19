#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
from monthly_totals_hint import *

def date_to_month_pandas(year, month):
    # You may need to modify this function, depending on your data types.
    return '%04i-%02i' % (year, month)


def pivot_months_pandas(data):
    """
        Create monthly precipitation totals for each station in the data set.
        
        This should use Pandas methods to manipulate the data.
        """
    # ...
    data_copy = data                  #save the original data and have one copy for further process
    vectorized_date = np.vectorize(date_to_month_pandas)
    data_copy['month'] = vectorized_date(data_copy['date'].dt.year, data_copy['date'].dt.month)     #modify the date to month we going to use in following analysis
    
    monthly = data_copy.groupby(['name','month']).aggregate('sum').reset_index()     #aggregate sum the precipitation regarding to group by name and month
    monthly = monthly.pivot(index = 'name', columns = 'month', values = 'precipitation')     #pivot the monthly dataset
    
    data_copy['counts'] = 1
    counts = data_copy.groupby(['name', 'month']).aggregate('count').reset_index()     #aggregate count up the observations regarding to group by name and month
    counts = counts.pivot(index = 'name', columns = 'month', values = 'counts')     #pivot the counts dataset
    
    return monthly, counts


def pivot_months_loops(data):
    """
        Create monthly precipitation totals for each station in the data set.
        
        This does it the hard way: using Pandas as a dumb data store, and iterating in Python.
        """
    # Find all stations and months in the data set.
    stations = set()
    months = set()
    for i,r in data.iterrows():
        stations.add(r['name'])
        m = date_to_month(r['date'])
        months.add(m)
    
    # Aggregate into dictionaries so we can look up later.
    stations = sorted(list(stations))
    row_to_station = dict(enumerate(stations))
    station_to_row = {s: i for i,s in row_to_station.items()}

    months = sorted(list(months))
    col_to_month = dict(enumerate(months))
    month_to_col = {m: i for i,m in col_to_month.items()}

# Create arrays for the data, and fill them.
precip_total = np.zeros((len(row_to_station), 12), dtype=np.uint)
obs_count = np.zeros((len(row_to_station), 12), dtype=np.uint)
    
    for _, row in data.iterrows():
        m = date_to_month(row['date'])
        r = station_to_row[row['name']]
        c = month_to_col[m]
        
        precip_total[r, c] += row['precipitation']
        obs_count[r, c] += 1

    # Build the DataFrames we needed all along (tidying up the index names while we're at it).
    totals = pd.DataFrame(
                          data=precip_total,
                          index=stations,
                          columns=months,
                          )
totals.index.name = 'name'
    totals.columns.name = 'month'
    
    counts = pd.DataFrame(
                          data=obs_count,
                          index=stations,
                          columns=months,
                          )
                          counts.index.name = 'name'
                          counts.columns.name = 'month'
                          
    return totals, counts



def main():
    data = get_precip_data()
    totals, counts = pivot_months_pandas(data)
    totals.to_csv('totals.csv')
    counts.to_csv('counts.csv')
    np.savez('monthdata.npz', totals=totals.values, counts=counts.values)


if __name__ == '__main__':
    main()



