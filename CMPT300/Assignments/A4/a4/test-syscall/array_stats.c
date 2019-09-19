#include "array_stats.h"


asmlinkage long sys_array_stats(struct array_stats *stats, long data[], long size)
{
	printk("\n\n\n\n\n\n\n\n \n\n\n\n\n\n");
	struct array_stats stats_copy;
	printk("\n\n\n\n\n\n\n\n \n\n\n\n\n\n");
	long stats_min = 0;
	long stats_max = 0;
	long stats_sum = 0;
	long stats_data = 0;
	//long len = 0;
	long result = 0;

	if (size<=0) return -EINVAL;
	
	if (!stats || !size) return -EFAULT;

	for (int i=0; i<size; i++){
		data_size = sizeof(data[i]);
		if (copy_from_user(&stats_data, &data[i], data_size)){
			printk("\n\n\n\n\n\n\n\n %ld\n\n\n\n\n\n", stats_min);
			return -EFAULT;
		}
		if (stats_min > stats_data)
		{
			stats_min = stats_data;
		}
		//printk("--min %ld\n", stats_min);
		if (stats_max < stats_data)
		{
			stats_max = stats_data;
		}
		//printk("--max %ld\n", stats_max);
		
		stats_sum += stats_data;
		//printk("--sum %ld\n", stats_sum);
		
		//printk("--data %ld\n", stats_data);
		i++;
	}
	stats_copy.min = stats_min;
	stats_copy.max = stats_max;
	stats_copy.sum = stats_sum;
	/* copy buf into dst, which is in the user’s address space */
	if (copy_to_user(stats, &stats_copy,sizeof(stats_copy))){
		return -EFAULT;
	}
	//printk("--STATSmax %ld\n", stats->min);
	//printk("--STATSmax %ld\n", stats->max);
	//printk("--STATSmax %ld\n", stats->sum);
	return 0;
}
