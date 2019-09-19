#include <stdio.h>
#include <limits.h>

int main(void){
	int a=CHAR_BIT;
	printf("%lu ",sizeof(char)*a);
	printf("%lu ",sizeof(unsigned char)*a);
	printf("%lu ",sizeof(int)*a);
	printf("%lu ",sizeof(unsigned int)*a);
	printf("%lu ",sizeof(long)*a);
	printf("%lu ",sizeof(unsigned long)*a);
	printf("%lu ",sizeof(float)*a);
	printf("%lu ",sizeof(double)*a);
	printf("%lu\n",sizeof(long double)*a);
	
}
