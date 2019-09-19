#include <stdio.h>
#include <math.h>

int main(){
    int x=0;
    int y=0;
    int z=0;
    int i;
    int j;
    scanf("%d %d %d",&x,&y,&z);
    for (j=z-1;j>0;j--){
        int left = floor(j*(x/(2.0*z)) );
        int right = ceil((x-1) + -j * (x/(2.0*z)));
        if (j==z-1){
            for (i=0;i<=right;i++){
                if( i>=left & i<=right){
                    printf("#");
                }
                else {
                    printf(" ");
                }
            }
        }
        else {
            for (i=0;i<=right;i++){
            if (i==left | i==right){
                printf("#");
            }
            else if( i>left & i<right){
                printf(".");
            }
            else {
                printf(" ");
            }
            }
        }
        printf("\n");
    }
    for (i=0; i<x; i++){
        printf("#");
    }
    printf("\n");

}

