#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "myalloc.h"
#include "list.h"



sem_t mutex;

struct Myalloc {
    enum allocation_algorithm aalgorithm;
    int size;
    void* memory;
    // Some other data members you want, 
    // such as lists to record allocated/free memory

    struct nodeStruct* allocatedmem;
    struct nodeStruct* freemem; 
};



struct Myalloc myalloc;

void initialize_allocator(int _size, enum allocation_algorithm _aalgorithm) {
    assert(_size > 0);
    sem_init(&mutex, 0, 1);
    myalloc.aalgorithm = _aalgorithm;
    myalloc.size = _size;
    // Add some other initialization 

	void *ptr = malloc((size_t)myalloc.size);
    myalloc.memory = ptr;  
    myalloc.allocatedmem = NULL;
    myalloc.freemem = List_createNode(ptr, _size);
    sem_post(&mutex);
}

void destroy_allocator() {
    sem_wait(&mutex);
    free(myalloc.memory);

    // free other dynamic allocated memory to avoid memory leak
    List_distoryer(myalloc.allocatedmem);
    List_distoryer(myalloc.freemem);
    sem_post(&mutex);

}

void* allocate(int _size) {
    sem_wait(&mutex);
    int sizewithheader = _size + 8;
    void* ptr = NULL;
    struct nodeStruct *emptyblock = NULL;
    struct nodeStruct *currentblock = myalloc.freemem;
    // Allocate memory from myalloc.memory 
    // ptr = address of allocated memory
    int available_mem = available_memory();
    if ( (_size <= 0) || (sizewithheader > available_mem) || (sizewithheader > myalloc.size)){
        return ptr;
    }

    int leftover;
    // refer to https://github.com/jeffwang4321/Operating-Systems/tree/master/Prj5%20-%20Memory%20Allocator
    // algorithm commented as my own understanding
    if (myalloc.aalgorithm == FIRST_FIT){                                   // use FIRST_FIT method
        while(currentblock != NULL && currentblock->item < sizewithheader){ // tranverse the list to find the proper block
            currentblock = currentblock->next;                              // tranverse
        }
        if(currentblock->item > sizewithheader) emptyblock = currentblock;  // save the proper block if found 
    }else if(myalloc.aalgorithm == BEST_FIT){                               // use BEST_FIT method
        int temp = myalloc.size;
        int best = myalloc.size;

        while(currentblock != NULL){                                        // tranverse the list to find the proper block
            leftover = currentblock->item - sizewithheader;                 // calculate the left space if item allocate at this node
            if(leftover >= 0){                                              // if the current block can store the item
                temp = leftover;                                            // save the leftover for later comparation
                if(temp < best){                                            //
                    emptyblock = currentblock;                              // renew the best fit block if temp is smaller
                    best = temp;
                } 
            }
            currentblock = currentblock->next;                              // tranverse
        }
    }else{                                                                  //WORST_FIT case left
        int temp = 0;
        int worst = -1;

        while(currentblock != NULL){                                        // tranverse the list to find the proper block
            leftover = currentblock->item - sizewithheader;                 // calculate the left space is item allocate at current node
            if(leftover >= 0){                                              // if size is big enough
                temp = leftover;                                            // save the leftover for later comparation
                if(temp > worst){                                           // if current leftover greater than previous worst case
                    emptyblock = currentblock;                              // 
                    worst = temp;                                           // update the worst fit block
                }
            }
            currentblock = currentblock->next;                              // tranverse
        }
    }

    if(emptyblock == NULL){
        return ptr;
    }

    int new_emptyblock_item = emptyblock->item - sizewithheader;
    if(new_emptyblock_item == 0 ){
        List_insertTail(&myalloc.allocatedmem, emptyblock);
        emptyblock->item = new_emptyblock_item;
        ptr = emptyblock->nodeptr;
        List_deleteNode(&myalloc.freemem, emptyblock);
    }else{
        struct nodeStruct *newnode = List_createNode(emptyblock->nodeptr + sizewithheader, new_emptyblock_item);
        ptr = emptyblock->nodeptr;

        struct nodeStruct *blockcopy = List_createNode(emptyblock->nodeptr, _size);

        List_insertTail(&myalloc.allocatedmem, blockcopy);
        List_deleteNode(&myalloc.freemem, emptyblock);
        List_insertTail(&myalloc.freemem, newnode); 
    }
    sem_post(&mutex);
    return ptr;
}

void deallocate(void* _ptr){
    sem_wait(&mutex);
    assert(_ptr != NULL);

    // Free allocated memory
    // Note: _ptr points to the user-visible memory. The size information is
    // stored at (char*)_ptr - 8.

    struct nodeStruct *currentblock = myalloc.allocatedmem;
    while(currentblock != NULL && currentblock->nodeptr != (_ptr-8)){
        currentblock = currentblock->next;
    }
    if(currentblock == NULL){ 
        return;
    }
    
    struct nodeStruct *copy = currentblock; 
    currentblock->item += 8;
    struct nodeStruct *mergecheck = myalloc.freemem; 
    int addflg = 0;


    while(mergecheck != NULL){                                                          // check if there are blocks should be merged
        if((mergecheck->nodeptr + mergecheck->item) == copy->nodeptr){                  // if freeblock ahead of deleted block
            mergecheck->item += copy->item + 8;
            addflg = 1;
        }
        if ((mergecheck->nodeptr + mergecheck->item) == (mergecheck->next->nodeptr)){   // check if free block after deleted block
            mergecheck->item += mergecheck->next->item;                                 // merge the following block
            mergecheck->next = mergecheck->next->next;                                  
            List_deleteNode(&myalloc.freemem, mergecheck);                              // delete the merged block
            addflg = 1;
        }
        mergecheck = mergecheck->next;
    }
    if(addflg != 1){
        List_insertTail(&myalloc.freemem, currentblock);                                // if no merge happened, insert the 
    }
    List_deleteNode(&myalloc.allocatedmem, currentblock);                               // delete the allocated node

    struct nodeStruct *temp = currentblock->next;
    currentblock = myalloc.allocatedmem;
    if(currentblock != NULL){ 
        while(currentblock->next != NULL){
            currentblock = currentblock->next; 
        }
        currentblock->next = temp;
    } else{
        myalloc.allocatedmem = temp;
    }    
    sem_post(&mutex);
}


int compact_allocation(void** _before, void** _after) {
    sem_wait(&mutex);
    int compacted = 0;

    // compact allocated memory
    // update _before, _after and compacted_size
    if(available_memory() == 0) return myalloc.size;
    if(List_countNodes(myalloc.freemem) == 0) return myalloc.size;

    struct nodeStruct *currentblock = myalloc.allocatedmem;

    while(currentblock != NULL){
        if(currentblock->next == NULL ){                    // only one allocated block
            break;
        }

        if(currentblock->nodeptr + currentblock->item + 8 < currentblock->next->nodeptr){
            _before[compacted] =  currentblock->next->nodeptr;
            //refer to https://www.tutorialspoint.com/c_standard_library/c_function_memmove.htm
            memmove(currentblock->nodeptr + currentblock->item + 8, currentblock->next->nodeptr, currentblock->next->item + 8); // shift memory forward
            currentblock->next->nodeptr = currentblock->nodeptr + currentblock->item + 8; // 
            _after[compacted] =  currentblock->next->nodeptr; 
            compacted++;
        }
        currentblock = currentblock->next;
    }
    
    struct nodeStruct *newnode = malloc(sizeof(struct nodeStruct));
    newnode->item = available_memory();
    newnode->nodeptr = currentblock->nodeptr + currentblock->item;

    struct nodeStruct *temp; 
    while(myalloc.freemem != NULL){                         // tranverse to delate the previous freelist
        temp = myalloc.freemem->next;                       
        free(myalloc.freemem); 
        myalloc.freemem = temp;
    }

    List_insertTail(&myalloc.freemem, newnode);             // create new freelist
    sem_post(&mutex);
    return compacted;
}

int available_memory() {
    sem_wait(&mutex);
    int available_memory_size = List_sum_memsize(myalloc.freemem);      // use list function to tranverse and sum
    // Calculate available memory size
    sem_post(&mutex);
    return available_memory_size;
}

void print_statistics() {
    sem_wait(&mutex);
    int allocated_size = List_sum_memsize(myalloc.allocatedmem);        // use list function to tranverse and sum
    int allocated_chunks = List_countNodes(myalloc.allocatedmem);       // use list function to count 
    int free_size = List_sum_memsize(myalloc.freemem);                  // use list function to tranverse and sum
    int free_chunks = List_countNodes(myalloc.freemem);                 // use list function to count
    int temp_min = myalloc.size;                                        
    int temp_max = 0;
    struct nodeStruct *temp = myalloc.freemem;                          

    while(temp){                                                        // tranverse the list for the min and max block size
        if(temp->item > temp_max){
            temp_max = temp->item;
        }
        if(temp->item < temp_min){
            temp_min = temp->item;
        }
        temp = temp->next;
    }

    int smallest_free_chunk_size = temp_min;
    int largest_free_chunk_size = temp_max;

    // Calculate the statistics

    printf("Allocated size = %d\n", allocated_size);
    printf("Allocated chunks = %d\n", allocated_chunks);
    printf("Free size = %d\n", free_size);
    printf("Free chunks = %d\n", free_chunks);
    printf("Largest free chunk size = %d\n", largest_free_chunk_size);
    printf("Smallest free chunk size = %d\n", smallest_free_chunk_size);
    sem_post(&mutex);
}



