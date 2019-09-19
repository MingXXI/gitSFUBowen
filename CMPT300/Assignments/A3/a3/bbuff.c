#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include "bbuff.h"

int counter;
void* buffer[BUFFER_SIZE];

sem_t mutex;
sem_t full;
sem_t none;

void bbuff_init(void){

	sem_init(&mutex, 0, 1);
	sem_init(&full, 0, 0);
	sem_init(&none, 0, BUFFER_SIZE);
	counter = 0;

	return;
}

void bbuff_blocking_insert(void* item){

	sem_wait(&none);
	sem_wait(&mutex);

	buffer[counter] = item;
	counter++;

	sem_post(&mutex);
	sem_post(&full);
	
	return;
}

void* bbuff_blocking_extract(void){

	sem_wait(&full);
	sem_wait(&mutex);

	counter--;
	void *candy_ptr = buffer[counter];

	sem_post(&mutex);
	sem_post(&none);

	return candy_ptr;
}

_Bool bbuff_is_empty(void){

	sem_wait(&mutex);
	if(counter > 0){ 
		sem_post(&mutex);
		return false;
	}
	sem_post(&mutex);

	return true;
}