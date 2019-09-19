from pandas.plotting import register_matplotlib_converters
register_matplotlib_converters()
import matplotlib.pyplot as plt
import datetime as dt
import pandas as pd
from scipy import stats
import numpy as np
import sys

def weeknum(d):
    return d.weekday()

def isocalendar(d):
    return d.isocalendar()
        # from the assignment description

OUTPUT_TEMPLATE = (
    "Initial (invalid) T-test p-value: {initial_ttest_p:.3g}\n"
    "Original data normality p-values: {initial_weekday_normality_p:.3g} {initial_weekend_normality_p:.3g}\n"
    "Original data equal-variance p-value: {initial_levene_p:.3g}\n"
    "Transformed data normality p-values: {transformed_weekday_normality_p:.3g} {transformed_weekend_normality_p:.3g}\n"
    "Transformed data equal-variance p-value: {transformed_levene_p:.3g}\n"
    "Weekly data normality p-values: {weekly_weekday_normality_p:.3g} {weekly_weekend_normality_p:.3g}\n"
    "Weekly data equal-variance p-value: {weekly_levene_p:.3g}\n"
    "Weekly T-test p-value: {weekly_ttest_p:.3g}\n"
    "Mann–Whitney U-test p-value: {utest_p:.3g}"
)


def main():
    reddit_counts = sys.argv[1]

    counts = pd.read_json(reddit_counts, lines=True)
    # ...
    counts = counts[counts['subreddit'] == 'canada']
    counts['week_num'] = counts['date'].apply(weeknum)

    data_2012 = counts[counts['date'].dt.year == 2012]
    data_2013 = counts[counts['date'].dt.year == 2013]
    counts = pd.concat([data_2012, data_2013], axis = 0, ignore_index = True)
        #https://jingyan.baidu.com/article/91f5db1b79205a1c7f05e3ae.html
    data_Sat = counts[counts['week_num'] == 5]
    data_Sun = counts[counts['week_num'] == 6]

    data_weekend = pd.concat([data_Sat, data_Sun], axis=0, ignore_index=True)
        #https://jingyan.baidu.com/article/91f5db1b79205a1c7f05e3ae.html
    data_weekday = counts[counts['week_num'] != 5]
    data_weekday = data_weekday[data_weekday['week_num'] != 6]

    initial_Ttest = stats.ttest_ind(data_weekend['comment_count'], data_weekday['comment_count']).pvalue

    normality_pvalue_weekday = stats.normaltest(data_weekday['comment_count']).pvalue
    normality_pvalue_weekend = stats.normaltest(data_weekend['comment_count']).pvalue

    levene_pvalue= stats.levene(data_weekend['comment_count'], data_weekday['comment_count']).pvalue

    # log test
    '''print("log:::")
    data_weekend['log'] = data_weekend['comment_count'].apply(np.log)
    data_weekday['log'] = data_weekday['comment_count'].apply(np.log)
    print(stats.normaltest(data_weekend['log']).pvalue) # 0.3149388682066669, good
    print(stats.normaltest(weekday['log']).pvalue) # 0.0004015914200681448, bad
    print(stats.levene(data_weekend['log'], data_weekday['log']).pvalue) # 0.0004190759393372205, bad
    '''

    # exp test
    '''print("exp:::")
    data_weekend['exp'] = data_weekend['comment_count'].apply(np.exp)
    data_weekday['exp'] = data_weekday['comment_count'].apply(np.exp)
    print(stats.normaltest(data_weekend['exp']).pvalue) # nan 
    print(stats.normaltest(data_weekday['exp']).pvalue) # nan 
    print(stats.levene(data_weekend['exp'], data_weekday['exp']).pvalue) #gives inf
    '''

    # sqrt test
    data_weekday['root'] =data_weekday['comment_count'].apply(np.sqrt) #bad
    data_weekend['root'] = data_weekend['comment_count'].apply(np.sqrt) #good
    transformed_weekday_normality = stats.normaltest(data_weekday['root']).pvalue # 0.03687221613365125 bad
    transformed_weekend_normality = stats.normaltest(data_weekend['root']).pvalue # 0.10760562894667387 good
    transformed_levene = stats.levene(data_weekend['root'], data_weekday['root']).pvalue # 0.5560544297516696 good

    del data_weekend['root']
    del data_weekday['root']

    '''print("sq:::")
    data_weekend['sq'] = (data_weekend['comment_count'])**2 # 2.991195568683962e-11 bad
    data_weekday['sq'] = (data_weekday['comment_count'])**2 # 2.7798243005635955e-29 bad
    print(stats.normaltest(data_weekend['sq']).pvalue)
    print(stats.normaltest(data_weekday['sq']).pvalue)
    print(stats.levene(data_weekend['sq'], data_weekday['sq']).pvalue) # 7.391434727467261e-08 bad
    '''

    data_weekend['iso'] = data_weekend['date'].apply(isocalendar)
    data_weekend['year']= data_weekend['iso'].apply(pd.Series).astype(int)[0]
    data_weekend['week'] = data_weekend['iso'].apply(pd.Series).astype(int)[1]

    del data_weekend['iso']
    data_weekend_iso = data_weekend.groupby(['year','week']).mean()
    del data_weekend_iso['week_num']

    data_weekday['iso'] = data_weekday['date'].apply(isocalendar)
    data_weekday['year']= data_weekday['iso'].apply(pd.Series).astype(int)[0]
    data_weekday['week'] = data_weekday['iso'].apply(pd.Series).astype(int)[1]

    del data_weekday['iso']
    data_weekday_iso = data_weekday.groupby(['year','week']).mean()
    del data_weekday_iso['week_num']

    weekday_normality = stats.normaltest(data_weekday_iso['comment_count']).pvalue
    weekend_normality = stats.normaltest(data_weekend_iso['comment_count']).pvalue
    weekly_levene = stats.levene(data_weekend_iso['comment_count'], data_weekday_iso['comment_count']).pvalue
    weekly_ttest_pvalue = stats.ttest_ind(data_weekend_iso['comment_count'],data_weekday_iso['comment_count']).pvalue

    #Mann-Whitney Utest
    utest_pvalue = stats.mannwhitneyu(data_weekend['comment_count'],data_weekday['comment_count']).pvalue






    print(OUTPUT_TEMPLATE.format(
        initial_ttest_p= initial_Ttest,
        initial_weekday_normality_p= normality_pvalue_weekday,
        initial_weekend_normality_p= normality_pvalue_weekend,
        initial_levene_p= levene_pvalue,
        transformed_weekday_normality_p= transformed_weekday_normality,
        transformed_weekend_normality_p= transformed_weekend_normality,
        transformed_levene_p= transformed_levene,
        weekly_weekday_normality_p= weekday_normality,
        weekly_weekend_normality_p= weekend_normality,
        weekly_levene_p= weekly_levene,
        weekly_ttest_p= weekly_ttest_pvalue,
        utest_p= utest_pvalue,
    ))


if __name__ == '__main__':
    main()