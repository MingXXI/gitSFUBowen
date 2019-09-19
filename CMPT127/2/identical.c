#include <stdio.h>

int identical( int a[], int b[], unsigned int len){
	int i;
	int k = 0;
	for (i=0;i<len;i++){
		if (a[i]==b[i]){
		}
		else{
			k=1;
		}
	}
	if(k==1){
		return 0;
	}
	else{
		return 1;
	}
}
