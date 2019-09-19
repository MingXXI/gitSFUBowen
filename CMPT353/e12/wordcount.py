import string, re
import numpy as np
import sys
from pyspark.sql import SparkSession, functions, types
from pyspark.sql.functions import desc, asc

spark = SparkSession.builder.appName('wordcount').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

def main(in_dir,out_dir):
    # data = spark.read.text(data1)
    # data = data.filter(data['value'] != '')
    # data.show()
    # wordbreak = r'[%s\s]+' % (re.escape(string.punctuation),)
    # data = data.withColumn('words', functions.explode(functions.split(functions.col('value'),wordbreak)))
    # data = data.withColumn('words', functions.lower(data['words']))
    # data = data.filter(data['words'] != '')

    # data = data.groupBy('words').agg(functions.count(data['words']))
    # data = data.sort(functions.col('words').asc())
    # data = data.sort(functions.col('count(words)').desc())
    # # data = data[data['words'] != '']

    # data.write.csv(data2, mode = 'overwrite')

    data = spark.read.text(in_dir)
    wordbreak = r'[%s\s]+' % (re.escape(string.punctuation),)
    data = data.withColumn('words', functions.explode(functions.split('value',wordbreak)))
    data = data.withColumn('words', functions.lower(data['words']))
    data = data.filter(data['words'] != '')
    data = data.select('words')

    data = data.groupBy('words').agg(functions.count(data['words']).alias('count'))


    data = data.sort(asc('words'))
    data = data.sort(desc('count'))

    data.write.csv(out_dir, mode = 'overwrite')


if __name__=='__main__':
    in_dir = sys.argv[1]
    out_dir = sys.argv[2]
    main(in_dir, out_dir)
