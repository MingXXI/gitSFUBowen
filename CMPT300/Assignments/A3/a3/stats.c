#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>
#include <string.h>


#include "stats.h"

typedef struct
{
	int factoryNum;
	int made;
	int eaten;
	double minDelay;
	double maxDelay;
	double avgDelay;
	double totalDelay;
} stat_t;

stat_t *stats;
int producers;

void stats_init(int num_producers){
	producers = num_producers;
	stats = malloc(sizeof(stat_t)*num_producers);
	
	for (int i = 0; i < num_producers; i++)
	{
		stats[i].factoryNum = i;
		stats[i].made = 0;
		stats[i].eaten = 0;
		stats[i].minDelay = DBL_MAX;
		stats[i].maxDelay = 0.0;
		stats[i].avgDelay = 0.0;
		stats[i].totalDelay = 0.0;
	}
}

void stats_cleanup(void){
	if(stats != NULL){
		free(stats);
	}
}

void stats_record_produced(int factory_number){
	stats[factory_number].made ++;
}

void stats_record_consumed(int factory_number, double delay_in_ms){
	stats[factory_number].eaten ++;
	stats[factory_number].totalDelay += delay_in_ms;
	stats[factory_number].avgDelay = (stats[factory_number].totalDelay) / (stats[factory_number].eaten);
	if(delay_in_ms < stats[factory_number].minDelay){
		stats[factory_number].minDelay = delay_in_ms;
	}
	if(delay_in_ms > stats[factory_number].maxDelay){
		stats[factory_number].maxDelay = delay_in_ms;
	}
}

void stats_display(void){     
	printf("%s\n", "Statistics:");
	printf("%8s%20s%20s%20s%20s%20s\n", "Factory#", "#Made", "#Eaten", "Min Delay[ms]", "Avg Delay[ms]", "Max Delay[ms]");

	for(int i = 0; i < producers; i++){
		if(stats[i].made != stats[i].eaten){
			printf("%s\n", "ERROR: Mismatch between number made and eaten.");
		}
		else{
			printf("%8d%20d%20d%20.5f%20.5f%20.5f\n", stats[i].factoryNum, stats[i].made, stats[i].made, stats[i].minDelay, stats[i].avgDelay, stats[i].maxDelay);
		}
	} 
}