// Test application for the array_stats syscall.

#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "array_stats.h"

// Sys-call number:
#define _ARRAY_STATS_ 341

/**
 * Prototypes
 */
void test_positive_few(void);
void test_negative_few(void);
void test_many(void);
void test_bad_addr(void);
static void do_syscall_working(long data[], long size);
static void do_syscall_failing(struct array_stats *stats, long data[], long size, long ret_code);
static void test_internal(_Bool success, int lineNum, char* argStr);
static void test_print_summary(void);


/***********************************************************
 * main()
 ***********************************************************/
int main(int argc, char *argv[])
{
	test_positive_few();
	test_negative_few();
	test_many();

	test_bad_addr();

	test_print_summary();
	return 0;
}


/***********************************************************
 * Testing routines for specific test
 ***********************************************************/
void test_positive_few()
{
	do_syscall_working((long[]){1}, 1);
	do_syscall_working((long[]){1, 2}, 2);
	do_syscall_working((long[]){1, 2, 3}, 3);
	do_syscall_working((long[]){0, 2, 4, 6}, 4);
	do_syscall_working((long[]){5, 3, 4, 1}, 4);
}
void test_negative_few()
{
	do_syscall_working((long[]){-1}, 1);
	do_syscall_working((long[]){-1, -2}, 2);
	do_syscall_working((long[]){-1, 2, 3}, 3);
	do_syscall_working((long[]){0, -2, 4, -6}, 4);
}

void fill(long data[], long size)
{
	for (int i = 0; i < size; i++) {
		data[i] = rand();
		if (i % 2 == 0) {
			data[i] *= -1;
		}
	}
}
#define MEG (1024*1024)
void test_many()
{
	for (int i = 1; i <= 5; i++) {
		long size = MEG * i;
		long *data = malloc(sizeof(data[0]) * size);
		fill(data, size);
		do_syscall_working(data, size);
		free(data);
	}
}

void test_bad_addr()
{
	struct array_stats stats;
	// 0 or negative sizes
	do_syscall_failing(&stats, (long[]){1}, 0, EINVAL);
	do_syscall_failing(&stats, (long[]){1}, -1, EINVAL);
	do_syscall_failing(&stats, (long[]){1}, -10000, EINVAL);

	// Bad data pointers
	do_syscall_failing(&stats, NULL, 1, EFAULT);
	do_syscall_failing(&stats, (long*)1LL, 1, EFAULT);
	do_syscall_failing(&stats, (long*)123456789012345689LL, 1, EFAULT);

	// Bad size (read off end)
	do_syscall_failing(&stats, (long[]){1}, 10*MEG, EFAULT);

	// Bad stats pointers, or read-only memory
	do_syscall_failing(NULL, (long[]){1}, 1, EFAULT);
	do_syscall_failing((void*)1, (long[]){1}, 1, EFAULT);
	do_syscall_failing((void*)test_bad_addr, (long[]){1}, 1, EFAULT);
}



/***********************************************************
 * Custom testing framework
 ***********************************************************/
// Track results:
static int numTests = 0;
static int numTestPassed = 0;

static int current_syscall_test_num = 0;
static int last_syscall_test_num_failed = -1;
static int num_syscall_tests_failed = 0;

// Macro to allow us to get the line number, and argument's text:
#define TEST(arg) test_internal((arg), __LINE__, #arg)

// Actual function used to check success/failure:
static void test_internal(_Bool success, int lineNum, char* argStr)
{
	numTests++;
	if (!success) {
		if (current_syscall_test_num != last_syscall_test_num_failed) {
			last_syscall_test_num_failed = current_syscall_test_num;
			num_syscall_tests_failed++;
		}
		printf("-------> ERROR %4d: test on line %d failed: %s\n",
				numTestPassed, lineNum, argStr);
	} else {
		numTestPassed++;
	}
}

static void test_print_summary(void)
{
	printf("\nExecution finished.\n");
	printf("%4d/%d tests passed.\n", numTestPassed, numTests);
	printf("%4d/%d tests FAILED.\n", numTests - numTestPassed, numTests);
	printf("%4d/%d unique sys-call testing configurations FAILED.\n", num_syscall_tests_failed, current_syscall_test_num);
}


/***********************************************************
 * Routines to double check array answers
 ***********************************************************/
static long find_max(long data[], long size)
{
	long max = data[0];
	for (int i = 0; i < size; i++) {
		if (data[i] > max) {
			max = data[i];
		}
	}
	return max;
}
static long find_min(long data[], long size)
{
	long min = data[0];
	for (int i = 0; i < size; i++) {
		if (data[i] < min) {
			min = data[i];
		}
	}
	return min;
}
static long find_sum(long data[], long size)
{
	long sum = 0;
	for (int i = 0; i < size; i++) {
		sum += data[i];
	}
	return sum;
}

/***********************************************************
 * Functions to actually make the sys-call and test results
 ***********************************************************/
static int do_syscall(struct array_stats *stats, long *data, long size)
{
	current_syscall_test_num++;
	printf("\nTest %d: ..Diving to kernel level\n", current_syscall_test_num);
	int result = syscall(_ARRAY_STATS_, stats, data, size);
	int my_errno = errno;
	printf("..Rising to user level w/ result = %d", result);
	if (result < 0) {
		printf(", errno = %d", my_errno);
	} else {
		my_errno = 0;
	}
	printf("\n");
	return my_errno;

}
static void do_syscall_working(long data[], long size)
{
	struct array_stats stats;
	int result = do_syscall(&stats, data, size);
	printf("Stats: min = %ld, max = %ld, sum = %ld\n",
			stats.min, stats.max, stats.sum);

	TEST(result == 0);
	TEST(stats.min == find_min(data, size));
	TEST(stats.max == find_max(data, size));
	TEST(stats.sum == find_sum(data, size));
}
static void do_syscall_failing(struct array_stats *stats, long data[], long size, long ret_code)
{
	int result = do_syscall(stats, data, size);
	TEST(result == ret_code);
}

