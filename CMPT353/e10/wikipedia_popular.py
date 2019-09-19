import sys
import re
from pyspark.sql import SparkSession, functions, types

spark = SparkSession.builder.appName('Wikipedia publishes').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

Wiki_schema = types.StructType([
    types.StructField('language', types.StringType()),
    types.StructField('title', types.StringType()),
    types.StructField('times', types.IntegerType()),
    types.StructField('return', types.IntegerType()),
])
def find_hour(string):
	return re.search(r"\d{8}-\d{2}",string)[0]

def main(in_directory, out_directory):
    wiki = spark.read.csv(in_directory, sep = ' ', schema = Wiki_schema).withColumn('filename', functions.input_file_name())

    path_to_hour = functions.udf(find_hour, returnType=types.StringType())
    wiki = wiki.withColumn('date', path_to_hour(functions.input_file_name()))
    # wiki = wiki.cache()
    wiki = wiki.filter(wiki.language=='en')
    wiki = wiki.filter(wiki.title!='Main_Page')
    wiki = wiki.filter(~wiki.title.startswith('Special:'))
    # wiki = wiki.cache()
    wiki = wiki.groupby('date').max('times').join(wiki,'date')
    wiki = wiki.cache()
    wiki = wiki[wiki['times'] == wiki['max(times)']]
    wiki = wiki.select('date','title','times')
    # wiki = wiki.cache()
    wiki = wiki.sort(wiki['date'], wiki['title'])

    wiki.write.csv(out_directory, mode='overwrite')

if __name__=='__main__':
    in_directory = sys.argv[1]
    out_directory = sys.argv[2]
    main(in_directory, out_directory)
