#include <stdio.h>
#include <math.h>

int main (void)
{
	float i=0.0;
	if (scanf("%f",&i)==1) {
		int a = floor(i);
		int b = round(i);
		int c = ceil(i);
		printf("%d %d %d\n",a,b,c);}
	else {
		printf("scanf error: (%d)\n",scanf("%f",&i));}
	return 0;
}

