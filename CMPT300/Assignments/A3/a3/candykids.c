#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <assert.h>
#include <semaphore.h>
#include <time.h>
#include "bbuff.h"
#include "stats.h"



typedef struct {
	int factory_number;
	double creation_ts_ms;
} candy_t;

double current_time_in_ms(void){
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return now.tv_sec *1000.0 + now.tv_nsec/1000000.0;
}

_Bool stop_thread = false;

void *factory_thread_function(void* param)
{
	srand(time(NULL));
	int factorytag = *((int *) param);

	while(!stop_thread){
		int factorywait = rand()%4;
		printf("\tFactory %d ships candy & waits %ds\n", factorytag, factorywait);
		
		candy_t* candynew = malloc(sizeof(candy_t));
   		candynew->factory_number = factorytag;
    	candynew->creation_ts_ms = current_time_in_ms();
    	
    	bbuff_blocking_insert(candynew);
    	stats_record_produced(factorytag);

		sleep(factorywait);
	}

	return NULL;
}


void *kids_thread_function(void* param){

	srand(time(NULL));
	int candyEaten = 0;

	while(1){
		int waitkid = rand()%2;
		candy_t* candykid = bbuff_blocking_extract();
		if(candykid != NULL){
			candyEaten ++;
			stats_record_consumed(candykid->factory_number, current_time_in_ms() - candykid->creation_ts_ms);
		}
		sleep(waitkid);
		free(candykid);
	}

	return NULL;
}

int main(int argc, char * argv[]){


	// 1. Extract arguments
	int factory = atoi(argv[1]);
	int kidsnum = atoi(argv[2]);
	int seconds = atoi(argv[3]);

	if (factory <= 0 || kidsnum <= 0 || seconds <= 0)
	{
		printf("%s\n", "Error: All arguments must be positive.");
		exit(-1);
	}

	// 2. Initialize Modules
	bbuff_init();
	stats_init(factory);

	// 3. Launch factory threads
	pthread_t factory_thread[factory];
	int factory_amount[factory];

	for (int i = 0; i<factory; i++){
		factory_amount[i] = i;
	}

	for (int i = 0; i<factory; i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		if(pthread_create(&factory_thread[i],&attr, factory_thread_function, &factory_amount[i])){
			printf("Error: Fail to Creat Factory Thread\n");
			exit(1);
		}

	}

	// 4. Launch kid threads
	pthread_t kids_thread[kidsnum];

	for (int i = 0; i<kidsnum; i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		if(pthread_create(&kids_thread[i],&attr, kids_thread_function, NULL)){
			printf("Error: Fail to Creat Kids Thread\n");
			exit(1);
		}
	}

	// 5. Wait for requested time
	for (int p = 1; p<seconds; p++){
		sleep(1);
		printf("Time %ds\n", p);
	}

	// 6. Stop factory threads
	stop_thread = true;
	for (int i = 0; i<factory; i++){
		pthread_join(factory_thread[i], NULL);
	}

	// 7. Wait until no more candy
	while (bbuff_is_empty() == false){
		printf("Waiting for all candy to be consumed\n");
		sleep(1);
	}

	// 8. Stop kid threads
	for (int i = 0; i < kidsnum; i++) {
		pthread_cancel(kids_thread[i]);
		pthread_join(kids_thread[i], NULL);
	}
	// 9. Print statistics
	stats_display();

	// 10. Cleanup any allocated memory
	stats_cleanup();

	return 0;
}
