#include<stdio.h>

int scrambled(unsigned int a[],unsigned int b[],unsigned int len)
{
    
    int c[100]={0};
    int d[100]={0};
    int i,j,k;
    for (i=0;i<len;i++){
        c[a[i]]++;
    }
    for (j=0;j<len;j++){
        d[b[j]]++;
    }
    for (k=0;k<100;k++){
        if (c[k] != d[k]){
            return 0;
        }
    }
    return 1;
}

