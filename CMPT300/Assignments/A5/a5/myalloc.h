#ifndef __MYALLOC_H__
#define __MYALLOC_H__


enum allocation_algorithm {FIRST_FIT, BEST_FIT, WORST_FIT};

void initialize_allocator(int _size, enum allocation_algorithm _aalgorithm);

void* allocate(int _size);
void deallocate(void* _ptr);
int available_memory();
void print_statistics();
int compact_allocation(void** _before, void** _after);
void destroy_allocator();

#endif
