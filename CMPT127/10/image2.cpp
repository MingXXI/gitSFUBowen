#include "image2.hpp"
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

Image::Image()
:cols (0),
rows(0),
pixels(NULL){
    
}

Image::~Image(){
    if(pixels != NULL){
        delete[] pixels;
    }
    pixels = NULL;
}

int Image::resize( unsigned int width, unsigned int height, uint8_t fillcolor){
    delete[] pixels;
    pixels= new uint8_t [width * height];
    if (pixels == NULL){
        return 1;
    }
    for (int i = 0; i< height*width ; i++){
        pixels[i] = fillcolor;
    }
    cols = width;
    rows = height;
    return 0;
}

int Image::set_pixel( unsigned int x, unsigned int y, uint8_t color ){
    if(pixels == NULL){
        return 1;
    }
    if (x > (cols-1) || y > (rows-1) || x*y < 0){
        return 1;
    }
    pixels[ ( cols * y ) + x ] = color;
    return 0;
}

int Image::get_pixel( unsigned int x, unsigned int y, uint8_t* colorp){
    if(pixels == NULL || colorp ==NULL){
        return 1;
    }
    if (x > (cols-1) || y > (rows-1) || x*y < 0){
        return 1;
    }
    *colorp = pixels[(y * cols) + x];
    return 0;
}


int Image::save( const char* filename) {
    if(filename == NULL ){
        return 1;
    }
    if (cols<0 || rows<0){
        return 1;
    }
    
    FILE* f2 = fopen(filename,"w");
    if (!f2){
        return 1;
    }
    if (fwrite(&cols, sizeof(unsigned int), 1, f2)!= 1 || fwrite(&rows, sizeof(unsigned int), 1, f2)!= 1){
        return 1;
    }
    if (fwrite(pixels, sizeof(uint8_t), rows*cols, f2)!= rows*cols){
        return 1;
    }
    if (fclose(f2)!= 0){
        return 1;
    }
    return 0;
}


int Image::load( const char* filename){
    FILE* f2 = fopen(filename, "r");
    if (!f2){
        return 1;
    }
    
    if(fread(&cols, sizeof(unsigned int), 1, f2)!= 1 || fread(&rows, sizeof(unsigned int), 1, f2)!= 1){
        return 1;
    }
    delete[] pixels;
    pixels = new uint8_t [cols*rows];
    if(fread(pixels, sizeof(uint8_t), cols*rows, f2)!= rows*cols){
        return 1;
    }
    if(fclose(f2)!=0){
        return 1;
    }
    return 0;
}








