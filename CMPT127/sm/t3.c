#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    float n = atof(argv[1]);
    int number = round(n);
    unsigned int count=round(atof(argv[2]));
    for (int i=0;i<count;i++){
        for (int j=0; j<number; j++){
            printf("#");
        }
	printf("\n");
        if(number % 2 !=0){
            number = number *3 +1;
        }else {
            number = number/2;
        }
    }
}

