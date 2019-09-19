#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "imgops.h"



void draw_circle( uint8_t img[],unsigned int cols,unsigned int rows,int x,int y,int r,uint8_t color ){
    int i,j;
    float leftx,lefty,rightx,righty;
    for (i=0;i<cols;i++){
        for(j=0;j<rows;j++){
            leftx=i-0.5;
            rightx=i+0.5;
            lefty=j-0.5;
            righty=j+0.5;
            if(sqrt(pow((leftx-x),2)+pow((lefty-y),2))<r | sqrt(pow((leftx-x),2)+pow((righty-y),2))<r |sqrt(pow((rightx-x),2)+pow((lefty-y),2))<r |sqrt(pow((rightx-x),2)+pow((righty-y),2))<r){
                set_pixel(img,cols,rows,i,j,color);
            }
        }
    }
}
