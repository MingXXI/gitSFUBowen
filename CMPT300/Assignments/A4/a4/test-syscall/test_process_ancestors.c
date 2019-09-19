#include <linux/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "process_ancestors.h"

#define _PROCESS_ANCESTORS_ 342
#define ANCESTOR_NAME_LEN 16



void dump(struct process_info *info, int size) {
	struct process_info process;
	for (int i=0; i<size; i++){
		process = info[i];
		printf("info->pid: %ld\n", process.pid);
		printf("info->name: %s\n", process.name);
	// 	for (int i=0; i<10; i++){
	// 		printf("%c", info->name[i]);
	// 	}
	// 	printf("\n");
		printf("info->state: %ld\n", process.state);
		printf("info->uid: %ld\n", process.uid);
		printf("info->nvcsw: %ld\n", process.nvcsw);
		printf("info->nivcsw: %ld\n", process.nivcsw);
		printf("info->num_children: %ld\n", process.num_children);
		printf("info->num_siblings: %ld\n", process.num_siblings);	
	}
}

int main(int argc, char *argv[]){
	
	long size = 2;
	long *num=0;
	int result;
	printf("\nDiving to kernel level\n\n");
	
	//for (int i=0;i<size;i++){
		struct process_info *info;
		result = syscall(_PROCESS_ANCESTORS_, info, size, num);
		dump(info, size);
	//}
	printf("\nRising to user level w/ result = %d\n\n", result);

	return 0;
}
