import sys
from pyspark.sql import SparkSession, functions, types, Row
import re
import math


spark = SparkSession.builder.appName('correlate logs').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+

line_re = re.compile(r"^(\S+) - - \[\S+ [+-]\d+\] \"[A-Z]+ \S+ HTTP/\d\.\d\" \d+ (\d+)$")


def line_to_row(line):
    """
    Take a logfile line and return a Row object with hostname and bytes transferred. Return None if regex doesn't match.
    """
    m = line_re.match(line)
    if m:
        # TODO
        return Row(hostname = m.group(1), bytes = float(m.group(2)))
    else:
        return None

def not_none(row):
    """
    Is this None? Hint: .filter() with it.
    """
    return row is not None


def create_row_rdd(in_directory):
    log_lines = spark.sparkContext.textFile(in_directory)
    # TODO: return an RDD of Row() objects
    log_lines = log_lines.map(line_to_row).filter(not_none)
    return log_lines

def main(in_directory):
    logs = spark.createDataFrame(create_row_rdd(in_directory)).cache()

    # TODO: calculate r.
    count_hostname = logs.groupby('hostname').agg(functions.count('hostname').alias('count_hostname')).sort('hostname')

    sum_bytes = logs.groupby('hostname').agg(functions.sum('bytes').alias('sum_bytes')).sort('hostname')

    table = count_hostname.join(sum_bytes,'hostname')
    table = table.withColumn('xy', table['count_hostname']*table['sum_bytes'])
    table = table.withColumn('x^2', table['count_hostname']**2)
    table = table.withColumn('y^2', table['sum_bytes']**2)

    n = table.count()
    sum_table = table.groupby().sum().collect()
    sum_x = sum_table[0][0]
    sum_y = sum_table[0][1]
    sum_x_sq = sum_table[0][3]
    sum_y_sq = sum_table[0][4]
    sum_xy = sum_table[0][2]

    r = (n*sum_xy-sum_x*sum_y)/(math.sqrt(n*sum_x_sq-sum_x**2)*math.sqrt(n*sum_y_sq-sum_y**2))


    table.show()
    # TODO: it isn't zero.
    print("r = %g\nr^2 = %g" % (r, r**2))


if __name__=='__main__':
    in_directory = sys.argv[1]
    main(in_directory)
