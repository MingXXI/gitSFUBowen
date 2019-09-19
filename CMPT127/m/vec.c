#include "vec.h"
#include <stdio.h>

//task 1

int vec_first(vec_t *v, double* result){
	if (v==NULL || v->dim == 0 || v->data == NULL){
		return -1;
	}else{
		*result=v->data;
		return 0;
	}
}

//task 2

int vec_last( vec_t *v, double* result){
	if (v==NULL || v->dim == 0 || v->data == NULL){
		return -1;
	}else{
		*result=v->data+(sizeof(v->data)/sizeof(double)-1);
		return 0;
	}

}

//task 3

int vec_max(vec_t *v, double* result){
	if (v==NULL || v->dim == 0 || v->data == NULL){
		return -1;
	}else{
		double max=v->data[0];
		for (int i=0; i<sizeof((v->data)/sizeof(double));i++){
			if (v->data[i]>max){
				*result=v->data+i;
			}
		}
		return 0;	
	}
}


//task 4

int vec_min(vec_t *v, double *result){
	if (v==NULL || v->dim == 0 || v->data == NULL){
		return -1;
	}else{
		double min=v->data[0];
		for (int i=0; i<sizeof((v->data)/sizeof(double));i++){
			if (v->data[i]<min){
				*result=v->data+i;
			}
		}
		return 0;	
	}
}


//task 5

int vec_sum(vec_t *v, double* result){
	if (v==NULL || v->dim == 0 || v->data == NULL){
		return -1;
	}else{
		double sum=0;
		for (int i=0; i<sizeof((v->data)/sizeof(double));i++){
			sum=sum + v->data[i];
			*result= sum;
		}
		return 0;	
	}
}

//task 6

int vec_dotprod(vec_t *v1, vec_t *v2, double *result){
	if (v1==NULL || v1->dim == 0 || v1->data == NULL){
		return -1;
	}else if (v2==NULL || v2->dim == 0 || v2->data == NULL){
		return -1;
	}else if (v2->dim != v1->dim){
		return -1;
	}else {
		double prod1=0;
		for (int i=0; i<sizeof((v1->data)/sizeof(double));i++){
			prod1=prod1+(v1->data[i]*v2->data[i]);
		}
		*result=prod1;
		return 0;
	}
}
















