#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int sorted(const void * n1, const void * n2){
    return (*(int*)n1 - *(int*)n2);
}// low to high,  if high to low :return (*(int*)n2 - *(int*)n1);


void list_sort(list_t* list){
    int i=0;
    for (element_t* el = list->head ; el ; el = el->next){
        i++;
    }
    int* arr=malloc(sizeof(int)*i);
    int count = 0;
    for (element_t* el = list->head ; el ; el = el->next){
        arr[count]=el->val;
        count += 1;
    }
    qsort(arr,i,sizeof(int),sorted);
    list_destroy (list);
    list=list_create();
    list_append(list, arr[0]);
    for (int j=1; j<i; j++){
        list_append(list, arr[j]);
    }
    
}
