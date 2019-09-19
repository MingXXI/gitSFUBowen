import pandas as pd
import numpy as np
import difflib
import sys

movie_list = sys.argv[1]
movie_ratings = sys.argv[2]
output = sys.argv[3]

movie_list = open(movie_list).readlines()
movie_list = list(map(lambda s: s.strip(), movie_list))
movie_list = pd.DataFrame(movie_list, columns = ['title'])

movie_ratings = pd.read_csv(movie_ratings)


close_titles = np.vectorize(difflib.get_close_matches)
title = movie_ratings['title']
movie_ratings['title'] = movie_ratings['title'].apply(lambda title: difflib.get_close_matches(title, movie_list['title'], n=500))
movie_ratings['title'] = movie_ratings.title.apply(''.join) 
		#https://stackoverflow.com/questions/13207697/how-to-remove-square-brackets-from-list-in-python
movie_ratings = movie_ratings[movie_ratings.title != '']
movie_ratings = movie_ratings.reset_index(drop = True)
		#https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.reset_index.html

movie_ratings = movie_ratings.groupby('title', 0).mean()

movie_ratings = movie_list.merge(movie_ratings, on='title')
movie_ratings['rating'] = movie_ratings['rating'].round(2)
		#https://pandas.pydata.org/pandas-docs/version/0.22/generated/pandas.DataFrame.round.html

movie_ratings.to_csv(output, header = ['title', 'rating'], index = False)
