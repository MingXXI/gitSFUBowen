import sys
from pyspark.sql import SparkSession, functions, types

spark = SparkSession.builder.appName('weather ETL').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

observation_schema = types.StructType([
    types.StructField('station', types.StringType()),
    types.StructField('date', types.StringType()),
    types.StructField('observation', types.StringType()),
    types.StructField('value', types.IntegerType()),
    types.StructField('mflag', types.StringType()),
    types.StructField('qflag', types.StringType()),
    types.StructField('sflag', types.StringType()),
    types.StructField('obstime', types.StringType()),
])


def main():
    in_directory = sys.argv[1]
    out_directory = sys.argv[2]

    weather = spark.read.csv(in_directory, schema=observation_schema)

    # TODO: finish here.

    weather = weather.filter(weather.qflag.isNull())
    weather = weather.filter(weather.station.startswith('CA'))
    weather = weather.filter(weather.observation == 'TMAX')
    weather['value'] /= 10
    weather['tmax'] = weather['value']

    new_weather = weather.select('station','date','tmax')



    cleaned_data.write.json(out_directory, compression='gzip', mode='overwrite')


if __name__=='__main__':
    main()
