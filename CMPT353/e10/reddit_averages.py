import sys
from pyspark.sql import SparkSession, functions, types

spark = SparkSession.builder.appName('reddit averages').getOrCreate()
spark.sparkContext.setLogLevel('WARN')

assert sys.version_info >= (3, 5) # make sure we have Python 3.5+
assert spark.version >= '2.3' # make sure we have Spark 2.3+


comments_schema = types.StructType([
    types.StructField('archived', types.BooleanType()),
    types.StructField('author', types.StringType()),
    types.StructField('author_flair_css_class', types.StringType()),
    types.StructField('author_flair_text', types.StringType()),
    types.StructField('body', types.StringType()),
    types.StructField('controversiality', types.LongType()),
    types.StructField('created_utc', types.StringType()),
    types.StructField('distinguished', types.StringType()),
    types.StructField('downs', types.LongType()),
    types.StructField('edited', types.StringType()),
    types.StructField('gilded', types.LongType()),
    types.StructField('id', types.StringType()),
    types.StructField('link_id', types.StringType()),
    types.StructField('name', types.StringType()),
    types.StructField('parent_id', types.StringType()),
    types.StructField('retrieved_on', types.LongType()),
    types.StructField('score', types.LongType()),
    types.StructField('score_hidden', types.BooleanType()),
    types.StructField('subreddit', types.StringType()),
    types.StructField('subreddit_id', types.StringType()),
    types.StructField('ups', types.LongType()),
    #types.StructField('year', types.IntegerType()),
    #types.StructField('month', types.IntegerType()),
])


def main(in_directory, out_directory):
    comments = spark.read.json(in_directory, schema = comments_schema)

    # schema, cache
    # real    0m18.698s
    # user    0m41.537s
    # sys 0m1.759s

    # schema, no cache
    # real    0m22.164s
    # user    0m45.059s
    # sys 0m1.852s

    # no schema, cache
    # real    0m22.823s
    # user    0m47.346s
    # sys 0m1.942s

    # no schema, no cache
    # real    0m26.111s
    # user    0m51.807s
    # sys 0m1.935s






    # TODO: calculate averages, sort by subreddit. Sort by average score and output that too.
    averages_by_subreddit = comments.groupby('subreddit').avg()
    averages_by_subreddit = averages_by_subreddit.cache()
    averages_by_subreddit = averages_by_subreddit.sort(averages_by_subreddit['subreddit'])
    averages_by_score = averages_by_subreddit.sort(averages_by_subreddit['avg(score)'])
    averages_by_subreddit.write.csv(out_directory + '-subreddit', mode='overwrite')
    averages_by_score.write.csv(out_directory + '-score', mode='overwrite')


if __name__=='__main__':
    in_directory = sys.argv[1]
    out_directory = sys.argv[2]
    main(in_directory, out_directory)
