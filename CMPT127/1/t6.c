#include <stdio.h>

int main()
{
    float a;
    float count=0;
    float min;
    float max;
    float tot=0.0;
    scanf("%f",&a);
    count = count +1;
    min=a;
    max=a;
    tot=tot+a;
    while(scanf("%f",&a)!= EOF){
        tot=tot+a;
        if(a>max){
            max=a;
            count=count+1;
        }
        else if(a<min){
            min=a;
            count=count+1;
        }
        else{
            count=count+1;
        }
    }
    printf("%.2f ""%.2f ""%.2f\n",min,max,(tot/count));
}

