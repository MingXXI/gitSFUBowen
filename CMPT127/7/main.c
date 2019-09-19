#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <time.h>
#include <assert.h>

int main( int argc, char* argv[] )
{
    srand(time(NULL));
    //test element_create at the first
    int testval = rand()%1000;
    element_t* eltest = element_create(testval);
    eltest->next = (element_t*)365;
    free(eltest);
    eltest = element_create(testval);
    if(eltest->next != NULL)
    {
        printf("error: then element->next is not point to NULL\n");
        return 1;
    }
    
    
    if (eltest->val != testval)
    {
        printf("error: the element val is wrong\n");
        return 1;
    }
    if(eltest->next != NULL)
    {
        printf("error: create element is not point to NULL\n");
        return 1;
    }
    
    //testing for list_create 10 times.
    list_t* list;
    for (int i = 0; i < 10; i++)
    {
        list = list_create(); //empty case
        if (list == NULL || list->head != NULL || list->tail != NULL)
        {
            printf("create Linked list failed\n");
            return 1;
        }
        list->head = malloc(sizeof(element_t));
        list->tail = malloc(sizeof(element_t));
        free(list->head);
        free(list->tail);
        free(list);
    }
    
    // append test. create 5 elements;
    list = list_create();
    int val_append;
    int appendarray[5] = {0,0,0,0,0};
    for(int i = 0; i < 5; i++)
    {
        val_append = rand()%20;
        if(list_append(list, val_append) != 0)
        {
            printf("error: append cal failed return non-zero code\n");
            return 1;
        }
        appendarray[i] = val_append;
    }
    
    if(list->head == NULL || list->head->val != appendarray[0])
    {
        printf("error: after append, the head is pointing to the wrong element or NULL\n");
        return 1;
    }
    if(list->tail == NULL || list->tail->val != appendarray[4])
    {
        printf("error: after append, the tail is pointing to the wrong element or NULL\n");
        return 1;
    }
    
    element_t* curr_append = list->head;
    for (int i = 0; i < 5; i++)
    {
        if(appendarray[i] != curr_append->val)
        {
            printf("error: after append, the element is wrong\n");
            return 1;
        }
        curr_append = curr_append->next;
    }
    free(curr_append);
    list_destroy(list);
    list = list_create();
    int testvalappend = rand()%20;
    if(list_append(list,testvalappend) != 0)
    {
        printf("append failed\n");
        return 1;
    }
    if(list->head->val != testvalappend || list->tail->val != testvalappend)
    {
        printf("append failed\n");
        return 1;
    }
    list_destroy(list);
    
    
    printf("list_append successed\n");
    
    // testing for prepend
    list = list_create();
    int val_prepend;
    int prependarray[5] = {0,0,0,0,0};
    for (int i = 0; i < 5; i++)
    {
        val_prepend = rand()%10;
        if(list_prepend(list, val_prepend) != 0)
        {
            printf("error: the prepend does not work\n");
            return 1;
        }
        prependarray[i] = val_prepend;
    }
    printf("the list after prepend:\n");
    list_print(list);
    
    if (list->head == NULL || list->head->val != prependarray[4])
    {
        printf("error:the prepend head is wrong\n");
        return 1;
    }
    if (list->tail == NULL || list->tail->val != prependarray[0])
    {
        printf("error: the prepend tail is wrong\n");
        return 1;
    }
    
    element_t* curr_prepend = list->head;
    for (int i = 4; i >= 0; i--)
    {
        if(prependarray[i] != curr_prepend->val)
        {
            printf("error: the prepend val is not right\n");
            return 1;
        }
        curr_prepend = curr_prepend->next;
    }
    free(curr_prepend);
    list_destroy(list);
    list = list_create();
    list_print(list);
    int oneval = rand()%20;
    if(list_prepend(list,oneval) != 0)
    {
        printf("prepend failed\n");
        return 1;
    }
    if(list->head->val != oneval || list->tail->val != oneval)
    {
        printf("prepend failed\n");
        return 1;
    }
    printf("the prepend is working\n");
    list_destroy(list);
    
    //test list_print;
    list = list_create();
    for (int i = 0; i < 5; i++)
    {
        list_append(list,i);
        printf("the curr linked list :\n");
        list_print( list );
        printf("\n");
    }
    
    int index = 4;
    element_t* el = list_index( list, index );
    
    if( el == NULL )
    {
        printf( "index %d not found\n", index );
        return 1; // fail
    }
    
    printf( "value at index %d is %d\n", index, el->val );
    
    list_destroy(list);
    list = list_create();
    list_index(list, index);
    
    printf("all test passed \n");
    return 0; // tests pass
}
