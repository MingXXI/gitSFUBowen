
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "point_array.h"

void point_array_init(point_array_t* pa){
    if(pa != NULL){
        pa->len = 0;
        pa->points = NULL;
    }
}

void point_array_reset( point_array_t* pa ){
    if(pa != NULL){
        free(pa->points);
        pa->points = NULL;
        pa->len=0;
    }
}


int point_array_append( point_array_t* pa, point_t* p ){
    if(pa == NULL){
        return 1;
    } else {
        size_t newsize = pa->len+1;
        pa->points = realloc(pa->points, sizeof(point_t)*newsize);
        if (pa->points == NULL ){
            return 1;
        }
        pa->len += 1;
        pa->points[pa->len-1]= *p;
        return 0;
    }
}

int point_array_remove( point_array_t* pa, unsigned int i ){
    if (pa==NULL){
        return 1;
    }
    if(pa->len==0){
        return 1;
    }
    if(i<pa->len){
        pa->points[i]=pa->points[pa->len-1];
	size_t size=pa->len -1;
        pa->points=realloc(pa->points, sizeof(point_t)*size);
        pa->len -= 1;
        return 0;
    }
    return 1;
}


