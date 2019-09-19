#include <stdio.h>

int main()
{
    int arr[3],i,j;
    scanf("%d""%d""%d",&arr[0],&arr[1],&arr[2]);
    if(arr[2]==1){
        for (i=0;i<arr[1]; i++){
            for (j=0; j<arr[0];j++)
                printf("%c",'#');
                printf("\n");
        }
    } else {
        for (i=0; i<arr[1];i++)
            if (i==0 | i == arr[1]-1){
                for (j=0;j<arr[0];j++)
                printf("%c",'#');
                printf("\n");
            }
            else
                for (j=0; j<arr[0];j++){
                    if (j==0){
                        printf("%c",'#');
                    }
                    else if (j==arr[0]-1){
                        printf("%c",'#');
                        printf("\n");
                    }
                    else
                        printf("%c",'.');
                }
    }
    
}

