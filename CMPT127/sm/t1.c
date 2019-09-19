#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    float n = atof(argv[1]);
    int number = round(n);
    unsigned int count=round(atof(argv[2]));
    printf("n=%d count=%d\n",number,count);
}
