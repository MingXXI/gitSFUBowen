#include "array_stats.h"
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE3(array_stats, struct array_stats*, stats, long*, data, long, size)
{
	struct array_stats stats_copy;
	long stats_min;
	long stats_max;
	long stats_sum = 0;
	long stats_data;
	int i = 0;

	if (size<=0) return -EINVAL;
	
	if (!stats || !size) return -EFAULT;

	while (i<size){
		int data_size = sizeof(data[i]);
		if (copy_from_user(&stats_data, &data[i], data_size)){
			return -EFAULT;
		}
		if(i == 0){
			stats_min = stats_data;
			stats_max = stats_data;
		}
		if (stats_min > stats_data)
		{
			stats_min = stats_data;
		}
		if (stats_max < stats_data)
		{
			stats_max = stats_data;
		}
		stats_sum += stats_data;
		
		i++;
	}
	stats_copy.min = stats_min;
	stats_copy.max = stats_max;
	stats_copy.sum = stats_sum;

	if (copy_to_user(stats, &stats_copy,sizeof(stats_copy))){
		return -EFAULT;
	}
	return 0;
}
