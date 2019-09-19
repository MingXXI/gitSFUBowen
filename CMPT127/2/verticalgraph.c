
#include <stdio.h>
int main()
{
    int arr[80];
    int i,j=0,top=0,k,l;
    while (scanf("%d",&i) != EOF){
        arr[j]=i;
        j++;
        if (i>top){
            top=i;
        }
    }
    for (k=0;k<top;k++){
        for (l=0;l<j;l++){
            if (arr[l]<(top-k)){
                printf(" ");
            }else{
                printf("#");
            }
        }
        printf("\n");
    
    }
    
}
