 #include <assert.h>
 #include <stdint.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include "intarr.h"

int intarr_save_json(intarr_t* ia, const char* filename){
	if (ia==NULL){
		return 1;
	}
	if (filename==NULL){
		return 1;
	}
	FILE *f2=fopen(filename,"w");
	if (f2==NULL){
		return 1;
	}else {
		fprintf(f2,"[ ");
		for (int i=0; i<ia->len; i++){
			fprintf(f2, "%d", ia->data[i]);
			if (i!=ia->len-1){
				fprintf(f2, ", ");
			}else {
				fprintf(f2, " ");
			}
		}
		fprintf(f2, "]");
		fclose(f2);
		return 0;
	}
}

intarr_t* intarr_load_json(const char* filename){
	if (filename==NULL){
		return NULL;
	}
	FILE *f3=fopen(filename,"r");
	if (f3==NULL){
		return NULL;
	}
	intarr_t* copied=intarr_create(0);
	int add;
	char garbage;
	fscanf(f3, "%c", &garbage);
	while(fscanf(f3, "%d",&add) && fscanf(f3, "%c", &garbage)){
		intarr_push(copied,add);
	}
	fclose(f3);
	return copied;
}
