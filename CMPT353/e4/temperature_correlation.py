from math import cos, asin, sqrt
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import gzip
import sys


def points_distance(lat1, lon1, lat2, lon2):
    p = np.pi/180 #     
    a = 0.5 - cos((lat2 - lat1) * p)/2 + cos(lat1 * p) * cos(lat2 * p) * (1 - cos((lon2 - lon1) * p)) / 2
    return 12742 * asin(sqrt(a)) #2*R*asin...
    #Function of distance calculation refer to: 
    #https://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula/21623206
    #which is provided on the exercise description website

distance_vec = np.vectorize(points_distance)

def distance(city, stations):
    city_lat = city['latitude']
    city_lon = city['longitude']
    
    distance_data = pd.DataFrame(columns = ['distance'])
    distance_data['distance'] = distance_vec(city_lat, city_lon, stations['latitude'], stations['longitude'])
    return distance_data['distance']

def best_tmax(city, stations):
	stations['distance'] = distance(city, stations)
	index = stations['distance'].idxmin()
	del stations['distance']

	return stations.iloc[index]['avg_tmax']


stations = sys.argv[1]
city_data = sys.argv[2]
output = sys.argv[3]

stations = gzip.open(stations, 'rt', encoding='utf-8')
stations = pd.read_json(stations, lines=True)
stations['avg_tmax'] /= 10

city_data = pd.read_csv(city_data, header = 0)
city_data = city_data.dropna(how = 'any')
print(city_data)
city_data['area'] /= 1000000
city_data = city_data[city_data['area'] <= 10000] 

city_data['best_tmax'] = city_data.apply(best_tmax, stations = stations, axis = 1)
city_data['density'] = city_data['population']/city_data['area']

plt.plot( city_data['best_tmax'],city_data['density'], 'r.')
plt.title('Temperature vs Population Density')
plt.xlabel('Avg Max Temperature (\u00b0C)')
plt.ylabel('Population Density (people/km\u00b2)')
plt.savefig(output)




