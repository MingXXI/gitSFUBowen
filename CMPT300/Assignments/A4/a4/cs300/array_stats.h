#include <linux/syscalls.h>
// Define the array_stats struct for the array_stats syscall.
#ifndef _ARRAY_STATS_H_
#define _ARRAY_STATS_H_

struct array_stats {
  long min;
  long max;
  long sum;
};

asmlinkage long sys_array_stats(struct array_stats *stats, long data[], long size);

#endif
