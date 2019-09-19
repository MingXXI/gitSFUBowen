#include <stdio.h>
#include <math.h>

int main (void)
{
	float i=0.0;
	scanf( "%f",&i);
	int a = floor(i);
	int b = round(i);
	int c = ceil(i);
	printf("%d %d %d\n",a,b,c);
	return 0;
}

