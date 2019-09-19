#include <stdint.h> // for uint8_t
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "image3.hpp"

using namespace std;

  
  /* Constructs an image of 0x0 pixels. */
Image::Image()
:cols(0),
rows(0),
pixels(NULL){
}
  
  /* Frees all memory allocated for img */
Image::~Image(){
    if (pixels != NULL){
        delete[] pixels;
    }
    pixels = NULL;
}
  
  /* Changes the size of an image, allocating memory as necessary, and
     setting all pixels to fillcolor. Returns 0 on success, or a
     non-zero error code.*/ 
int Image::resize( unsigned int width,  unsigned int height, uint8_t fillcolor ){
    delete[] pixels;
    pixels= new uint8_t* [height];
    if(pixels == NULL){
        return 1;
    }
    for (int i = 0; i<height; i++){
        pixels[i]= new uint8_t [width];
        if(pixels[i] == NULL){
            return 1;
        }
        for (int j=0; j<width; j++){
            pixels[i][j] = fillcolor;
        }
    }
    cols=width;
    rows=height;
    return 0;
}
  
  /* Sets the color of the pixel at (x,y) to color. Returns 0 on
     success, else a non-zero error code. If (x,y) is not a valid
     pixel, the call fails and the image does not change.*/
int Image::set_pixel( unsigned int x, unsigned int y, uint8_t color ){
    if(pixels == NULL){
        return 1;
    }
    if (x> (cols-1) || y>(rows-1) || x*y<0){
        return 1;
    }
    pixels[y][x]=color;
    return 0;
}
  
  /* Gets the color of the pixel at (x,y) and stores at the address
     pointed to by colorp. Returns 0 on success, else a non-zero error
     code. */
int Image::get_pixel( unsigned int x, unsigned int y, uint8_t* colorp ){
    if(pixels==NULL || colorp == NULL){
        return 1;
    }
    if(x> (cols-1) || y>(rows-1) || x*y<0){
        return 1;
    }
    *colorp = pixels[y][x];
    return 0;
}
  
  /* Saves the image in the file filename. In a format that can be
     loaded by load().  Returns 0 on success, else a non-zero error
     code. */
int Image::save( const char* filename ){
    if (cols < 0 || rows < 0){
        return 1;
    }

    FILE* f3=fopen(filename,"w");
    if (!f3){
        return 1;
    }
    if (fwrite(&cols, sizeof(unsigned int), 1, f3)!= 1 || fwrite(&rows, sizeof(unsigned int), 1, f3)!= 1){
        return 1;
    }
    for (int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            if(fwrite(&pixels[i][j],sizeof(uint8_t),1,f3)!= 1){
                return 1;
            }
        }
    }
    if (fclose(f3)!= 0){
        return 1;
    }
    return 0;
}

  /* Load an image from the file filename, replacing the current
     image size and data. The file is in a format that was saved by
     save().  Returns 0 success, else a non-zero error code . */
int Image::load( const char* filename ){
    FILE* f = fopen(filename, "r");
    if (f == NULL) return 1;
    if(fread(&this->cols,sizeof(unsigned int),1,f) != 1) return 1;
    if(fread(&this->rows,sizeof(unsigned int),1,f) != 1) return 1;
    
    
    if(this->cols == 0 && this->rows == 0)
    {
        this->pixels = NULL;
        if(fclose(f) != 0) return 1;
        return 0;
    }
    resize(this->cols, this->rows, 1);
    for(int y = 0; y < this->rows;y++)
    {
        for(int x = 0; x < this->cols; x++)
        {
            if(fread(&this->pixels[y][x],sizeof(uint8_t),1,f) != 1) return 1;
        }
    }
    if(fclose(f) != 0) return 1;
    return 0;
}

