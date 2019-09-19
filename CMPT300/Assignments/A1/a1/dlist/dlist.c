#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"


struct nodeStruct* List_createNode(int item){
	struct nodeStruct *node = (nodeStruct *)malloc(sizeof(nodeStruct));
	if (node){
		node->item = item;
		node->next = NULL;
		node->prev = NULL;
	}
	return node;
}



/*
 * Insert node at the head of the list.
 */
void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node){
	if(headRef){
		node->prev = NULL;
		node->next = *headRef;
		*headRef = node;
	}
}


/*
 * Insert node after the tail of the list.
 */
void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node){
	nodeStruct *ptr = *headRef;

	if (ptr){
		for (; ptr->next; ptr = ptr->next);
		ptr->next = node;
		node->prev = ptr;
		node->next = NULL;

	}else{
		*headRef = node;
		node->next = NULL;
		node->prev = NULL;
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
	nodeStruct *temp = *headRef;
	if (node->next == NULL){
		if(node->prev == NULL){
			temp->next = NULL;
			temp->prev = NULL;
			*headRef = NULL;
			free(node);
		}else{
			node->prev->next = NULL;
			free(node);
		}
	}else{
		if(node->prev == NULL){
			temp = temp->next;
			temp->prev = NULL;
			free(node);
		}else{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			free(node);
		}
	}
}

/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort (struct nodeStruct **headRef){
	nodeStruct *p,*q, *target;
	int changed = 1;

	if ((target = (nodeStruct *)malloc(sizeof(nodeStruct))) == NULL){
		exit(1);
	}

	target->next = *headRef;
	if (*headRef != NULL && target->next != NULL){
		while(changed == 1){
			changed = 0;
			q = target;
			p = target->next;
			while (p->next != NULL){
				if (p->item > p->next->item){
					int temp = p->item;
					p->item = p->next->item;
					p->next->item = temp;
					changed = 1;
				}
				q = p;
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



















