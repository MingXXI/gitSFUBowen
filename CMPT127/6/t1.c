 #include <assert.h>
 #include <stdint.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include "intarr.h"

int intarr_save_binary(intarr_t* ia, const char* filename){
	FILE* f1=fopen(filename,"w");
	if(ia==NULL || f1==NULL || ia->data==NULL){
		return 1;
	}
	const size_t length = ia->len;
	if (fwrite(&ia->len,sizeof(int), 1, f1)!=1){
		return 1;
	}
	if (fwrite(ia->data,sizeof(int), length, f1)!= length){
		return 1;
	}
	fclose(f1);
	return 0;
}


intarr_t* intarr_load_binary(const char* filename){
	FILE* f2=fopen(filename, "r");
	if(f2 == NULL){
		return NULL;
	}
	int length = 0;
	if(fread(&length, sizeof(int), 1, f2) != 1){
		return NULL;
	}
	intarr_t* new= malloc(sizeof(intarr_t));
	if(new==NULL){
		return NULL;
	}
	new->len = length;
	new->data = malloc(sizeof(int)*length);
	if (new->data==NULL){
		return NULL;
	}
	const size_t datalen = length;
	if( fread(new->data, sizeof(int), datalen, f2) != datalen){
		return NULL;
	}
	
	fclose(f2);
	return new;
		
}

