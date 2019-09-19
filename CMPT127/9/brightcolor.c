
/* brightcolor.c - generate nice bright, unique RGBA colors.
   (C) Richard Vaughan 2015
 */

#include <math.h>
#include <stdlib.h>
#include <string.h> // for memcpy()

#include "brightcolor.h"

// lookup table of nice bright colors
static float colors[8*8*8][4];

static void RGBfromHSV( double hue, double saturation, double value, float rgb[3] )
{
    int hi = floor(hue * 6.0);
    float f = hue*6.0 - hi; 
    float v = value;
    float p = value * (1.0 - saturation);
    float q = value * (1.0 - f * saturation);
    float t = value * (1.0 - (1 - f) * saturation);

    switch( hi )
    {
        case 0:
            rgb[0] = v;
            rgb[1] = t;
            rgb[2] = p;
            break;
        case 1:
            rgb[0] = q;
            rgb[1] = v;
            rgb[2] = p;
            break;
        case 2:
            rgb[0] = p;
            rgb[1] = v;
            rgb[2] = t;
            break;
        case 3:
            rgb[0] = p;
            rgb[1] = q;
            rgb[2] = v;
            break;
        case 4:
            rgb[0] = t;
            rgb[1] = p;
            rgb[2] = v;
            break;
        default:
            rgb[0] = v;
            rgb[1] = p;
            rgb[2] = q;
    }
}

/* Initialize a table of nice bright usable unique colors. Parameter
   @alpha sets the alpha channel density (transparency) for all
   colors. */
void bright_color_init( float alpha )
{
    double h = drand48(); // # use random start value

    // a table of nice bright colors
    int num = 8;
    for(  int i=0; i<num; i++ )
        for(  int j=0; j<num; j++ )
            for(  int k=0; k<num; k++ )
            {
                h += 1.0 / BRIGHT_COLOR_GOLDEN_RATIO;

                float col[3];
                RGBfromHSV( fmod(h,1.0), 0.8, 0.99, col );

                int c = (8*8*i)+(8*j)+k;
                colors[c][0] = col[0];
                colors[c][1] = col[1];
                colors[c][2] = col[2];
                colors[c][3] = alpha;
            }
}

/* Get a nice bright color from index @i in the color table. */
void bright_color( int i, float color[4] )
{
    memcpy( color, colors[ i % (8*8*8) ], 4 * sizeof(float) );
}

