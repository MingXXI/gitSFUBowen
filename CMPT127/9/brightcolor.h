
/* brightcolor.h - generate nice bright, unique RGBA colors.
   (C) Richard Vaughan 2015
 */

#define BRIGHT_COLOR_GOLDEN_RATIO 1.618;

/* Initialize a table of nice bright usable unique colors. Call this
   before calling any other bright_color functions.  Parameter @alpha
   sets the alpha channel density (transparency) for all colors. */
void bright_color_init( float alpha );

/* Get a nice bright color from index @i in the color table. */
void bright_color( int i, float color[4] );
