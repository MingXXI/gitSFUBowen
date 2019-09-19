#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include "image.hpp"

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
	if (x > (cols-1) || y > (rows-1) || x < 0 || y < 0){
		return 1;
	}
	pixels[ ( cols * y ) + x ] = color;
	return 0;
}

int Image::get_pixel( unsigned int x, unsigned int y, uint8_t* colorp){
	if(pixels == NULL || colorp ==NULL){
		return 1;
	}
	if (x > (cols-1) || y > (rows-1) || x < 0 || y < 0){
		return 1;
	}
	*colorp = pixels[(y * cols) + x];
	return 0;
}
