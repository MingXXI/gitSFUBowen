from xml.dom.minidom import parse, parseString
from pykalman import KalmanFilter
from math import cos, asin, sqrt
import pandas as pd
import numpy as np
import sys

def output_gpx(points, output_filename):
    """
    Output a GPX file with latitude and longitude from the points DataFrame.
    """
    from xml.dom.minidom import getDOMImplementation
    def append_trkpt(pt, trkseg, doc):
        trkpt = doc.createElement('trkpt')
        trkpt.setAttribute('lat', '%.8f' % (pt['lat']))
        trkpt.setAttribute('lon', '%.8f' % (pt['lon']))
        trkseg.appendChild(trkpt)
    
    doc = getDOMImplementation().createDocument(None, 'gpx', None)
    trk = doc.createElement('trk')
    doc.documentElement.appendChild(trk)
    trkseg = doc.createElement('trkseg')
    trk.appendChild(trkseg)
    
    points.apply(append_trkpt, axis=1, trkseg=trkseg, doc=doc)
    
    with open(output_filename, 'w') as fh:
        doc.writexml(fh, indent=' ')

def get_data(filename):

    data = parse(filename)
    processed_data = data.getElementsByTagName('trkpt')
    gps_data = pd.DataFrame(columns = ['lat','lon'])
    
    for i in range(len(processed_data)):
        lat = float(processed_data[i].attributes['lat'].value)
        lon = float(processed_data[i].attributes['lon'].value)
        gps_data.loc[i] = (lat, lon)

    return gps_data
    


def points_distance(lat1, lon1, lat2, lon2):
    p = np.pi/180 #     
    a = 0.5 - cos((lat2 - lat1) * p)/2 + cos(lat1 * p) * cos(lat2 * p) * (1 - cos((lon2 - lon1) * p)) / 2
    return 12742 * asin(sqrt(a)) #2*R*asin...
    #Function of distance calculation refer to: 
    #https://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula/21623206
    #which is provided on the exercise description website

distance_vec = np.vectorize(points_distance)

def distance(data):
    start_lat = data['lat']
    start_lon = data['lon']
    end_lat = data['lat'].shift(periods = -1)
    end_lon = data['lon'].shift(periods = -1)
    
    distance_data = pd.DataFrame(columns = ['distance'])
    distance_data['distance'] = distance_vec(start_lat, start_lon, end_lat, end_lon)
    distance_sum = distance_data['distance'].sum()
    return distance_sum*1000

def smooth(data):

    initial_state = data.iloc[0]
    observation_covariance = np.diag([17.5/10**5, 17.5/10**5]) ** 2 # TODO: shouldn't be zero
    transition_covariance = np.diag([10/10**5, 10/10**5]) ** 2 # TODO: shouldn't be zero
    transition = [[1,0],[0,1]] # TODO: shouldn't (all) be zero

    kf = KalmanFilter(initial_state_mean = initial_state, initial_state_covariance = observation_covariance, observation_covariance = observation_covariance, transition_covariance = transition_covariance, transition_matrices = transition)
    kalman_smoothed, _ = kf.smooth(data)
    smoothed_data = pd.DataFrame(kalman_smoothed, columns = ['lat', 'lon'])
    
    return smoothed_data


def main():
    points = get_data(sys.argv[1])
    print('Unfiltered distance: %0.2f' % (distance(points),))
    
    smoothed_points = smooth(points)
    print('Filtered distance: %0.2f' % (distance(smoothed_points),))
    output_gpx(smoothed_points, 'out.gpx')


if __name__ == '__main__':
    main()