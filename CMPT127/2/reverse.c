#include <stdio.h>

void reverse( int arr[], unsigned int len){
	int brr[len];
	for (int i=0;i<len;i++){
		brr[i]=arr[len-1-i];
	}
	for (int i=0;i<len;i++){
		arr[i]=brr[i];
	}
}
