#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

// refer to solution provided for assignment 1


/*
 * Allocate memory for a node of type struct nodeStruct and initialize
 * it with the value item. Return a pointer to the new node.
 */
struct nodeStruct* List_createNode(void *ptr, int item){
	struct nodeStruct *node = malloc(sizeof(struct nodeStruct));
	if (node != NULL){
		node->item = item;
		node->nodeptr = ptr;
	}
	return node;
}



void List_distoryer (struct nodeStruct *headRef){
	struct nodeStruct *temp;
    while(headRef){
        temp = headRef->next;
        free(headRef);
        headRef = temp;
    }
}



/*
 * Insert node at the head of the list.
 */
void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node){
	if(headRef){
		node->next = *headRef;
		*headRef = node;
	}
}


/*
 * Insert node after the tail of the list.
 */
void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node){

	node->next = NULL;

	// Handle empty list
	if (*headRef == NULL) {
		*headRef = node;
	}
	else {
		// Find the tail and insert node
		struct nodeStruct *current = *headRef;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = node;
	}
}


/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
int List_countNodes (struct nodeStruct *head){
	int i = 0;
	nodeStruct *ptr = head;
	for(;ptr; ptr = ptr->next, i++);
	return i;
}


/*
 * Return the first node holding the value item, return NULL if none found
 */
struct nodeStruct* List_findNode(struct nodeStruct *head, int item){
	nodeStruct *ptr = head;
	while(ptr){
		if (ptr->item == item){
			return ptr;
		}else{
			ptr = ptr->next;
		}
	}
	return NULL;
}

/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set to a valid node 
 * in the list. For example, the client code may have found it by calling 
 * List_findNode(). If the list contains only one node, the head of the list 
 * should be set to NULL.
 */
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node){
	assert(headRef != NULL);
	assert(*headRef != NULL);

	// Is it the first element?
	if (*headRef == node) {
		*headRef = node->next;
	}
	else {
		// Find the previous node:
		struct nodeStruct *previous = *headRef;
		while (previous->next != node) {
			previous = previous->next;
			assert(previous != NULL);
		}

		// Unlink node:
		assert(previous->next == node);
		previous->next = node->next;
	}

	// Free memory:
	free(node);
}

/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort (struct nodeStruct **headRef){
	nodeStruct *p, *target;
	int changed = 1;

	if ((target = (nodeStruct *)malloc(sizeof(nodeStruct))) == NULL){
		exit(1);
	}

	target->next = *headRef;
	if (*headRef != NULL && target->next != NULL){
		while(changed == 1){
			changed = 0;
			p = target->next;
			while (p->next != NULL){
				if (p->item > p->next->item){
					int temp = p->item;
					p->item = p->next->item;
					p->next->item = temp;
					changed = 1;
				}
				if (p->next != NULL){
					p = p->next;
				}
			}
		}
		p = target->next;
		free(target);
		*headRef = p;
	}
}


int List_sum_memsize(struct nodeStruct *head){
	int sum = 0;
	struct nodeStruct *curr = head;
	while(curr != NULL){
		sum += curr->item+8;
		curr = curr->next;
	}
	return sum;
}
















