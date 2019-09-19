#include <stdint.h> // for uint8_t

class Image {
 
public:
  // made these public so I can peek at them
  unsigned int cols;
  unsigned int rows;
  uint8_t* pixels;
  
  /* Constructs an image of 0x0 pixels. */
  Image();
  
  /* Frees all memory allocated for img */
  ~Image();
  
  /* Changes the size of an image, allocating memory as necessary, and
     setting all pixels to fillcolor. Returns 0 on success, or a non-zero error code.*/ 
  int resize( unsigned int width,  unsigned int height, uint8_t fillcolor );
  
  /* Sets the color of the pixel at (x,y) to color. Returns 0 on success, else a non-zero 
     error code. If (x,y) is not a valid pixel, the call fails and the image does not change.*/
  int set_pixel( unsigned int x, unsigned int y, uint8_t color );
  
  /* Gets the color of the pixel at (x,y) and stores at the address pointed to 
     by colorp. Returns 0 on success, else a non-zero error code. */
  int get_pixel( unsigned int x, unsigned int y, uint8_t* colorp );
};

