#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/compiler.h>
#include <asm/percpu.h>
#include <asm-generic/errno-base.h>
#include <linux/errno.h>
#include <linux/string.h>

#include "process_ancestors.h"

asmlinkage long sys_process_ancestors(struct process_info info_array[],
                                      long size,
                                      long *num_filled){
	
	struct process_info process;
	struct list_head *list;
	struct task_struct *task;
	struct task_struct task_struct;
	
	int children = 0;
	int siblings = 0;
	int i = 0;
	int j = 0;	

	if (size<=0) return -EINVAL;
	
	if (!info_array || !num_filled) return -EFAULT;

	for (task = current; task != &init_task; task = task->parent) {
		//reference: https://notes.shichao.io/lkd/ch3/
		
		process.pid = (long)task->pid; 
		process.state = task->state;
		while(j<16){
			process.name[j] = task_struct.comm[j];
			printk("%c", process.name[j]);
			j++;
		}

		memset(process.name, '\0', sizeof(process.name));
		strcpy(process.name, task->comm);

		list_for_each(list, &current->children) {
			children ++;
		}
		list_for_each(list, &current->sibling) {
			siblings ++;
		}
		process.num_children = children;
		process.num_siblings = siblings;	
		children = 0;
		siblings = 0;		

		info_array[i] = process;
		i++;
	}
	return 0;
}
