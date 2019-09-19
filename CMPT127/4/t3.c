#include <stdint.h>
#include <stdlib.h>
#include "imgops.h"

unsigned int size( uint8_t array[],unsigned int cols, unsigned int
rows,unsigned int p,unsigned int q ){
	unsigned int sum = 0;
	for (int i = -1; i <= 1; i ++){
		for (int j = -1; j <= 1; j++){
			if (! (i == 0 && j == 0)){
				int icols = (i + p + cols) % cols;
				int jrows = (j + q + rows) % rows;
				sum += (get_pixel(array,cols,rows,icols,jrows) > 0);
			}
		}
	}
	return sum;
}
void life( uint8_t array[], unsigned int cols, unsigned int rows ){
	uint8_t * clone = copy( array, cols, rows );
	for (int i = 0; i < cols; i ++){
		for (int j = 0; j < rows; j ++){
			unsigned int hs = size(clone, cols, rows, i, j);
			if (hs < 2){
				set_pixel( array, cols, rows, i, j, 0 );
			}
			if (hs > 3){
				set_pixel( array, cols, rows, i, j, 0 );
			}
			if ( hs == 3){
				set_pixel( array, cols, rows, i, j, 255 );
			}
		}
	}
	free(clone);
}


