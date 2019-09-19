#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "imgops.h"
void draw_rectangle( uint8_t array[],unsigned int cols,unsigned int rows,int x,int y,int rect_width,int rect_height,uint8_t color ){
    int i,j;
    int leftx,upy,rightx,downy;
    if(rect_width!=0 & rect_height!=0){
        if(x+rect_width>x){
            leftx=x;
            rightx=x+rect_width-1;
        }else{
            leftx=rect_width+x+1;
            rightx=x;
        }
        if(y+rect_height>y){
            upy=y;
            downy=y+rect_height-1;
        }else {
            upy=y+rect_height+1;
            downy=y;
        }
        for (i=0;i<cols;i++){
            for (j=0;j<rows;j++){
                if(i==leftx | i==rightx){
                    if(j>=upy & j<=downy){
                        set_pixel(array, cols, rows, i, j, color);
                    }
                }
                if (j==upy | j==downy){
                    if(i>=leftx && i <= rightx){
                        set_pixel(array,cols,rows,i,j,color);
                    }
                }
            }
        }
    }
}

