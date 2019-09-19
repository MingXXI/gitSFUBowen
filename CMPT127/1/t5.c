#include <stdio.h>
#include <math.h>

int main ()
{
    float i=0.0;
    while (scanf("%f",&i)!= EOF) {
        int a = floor(i);
        int b = round(i);
        int c = ceil(i);
        printf("%d %d %d\n",a,b,c);
    }
    printf("Done.\n");
    
}
