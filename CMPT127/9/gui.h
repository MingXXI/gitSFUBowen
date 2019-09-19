/* gui.h - a very simple GUI interface that wraps FreeGLUT.
   (C) Richard Vaughan 2015
 */

/* --- USER INTERFACE FUNCTIONS ---------------------------------------------------
 */

/* Create a new user interface window using the command line arguments
   from main, with default window size (@width by @height). Callback
   function @display_func will be called once each time the user
   requests it by calling gui_redraw(). Callback function
   @key_down_func will be called whenever a key on the keyboard is
   pressed. Callback function @key_up_func will be called whenever a
   key on the keyboard is released. */
void gui_init( int argc, char** argv, 
        unsigned int width,
        unsigned int height,
        void (*redraw_func)(void),
        void (*key_down_func)(unsigned char, int, int),
        void (*key_up_func)(unsigned char, int, int) 
        );

    /* Request a call of the redraw function registered by the gui_init()
       function. */
    void gui_redraw( void );

    /* Handle all user interface events (keyboard presses, mouse clicks,
       redraw requests, etc. */
    void gui_handle_events( void );


    /* --- DRAWING FUNCTIONS -----------------------------------------------------
     */

    /* Clear the window to the specified background color.*/
    void draw_clear( const float color[4] );

    /* Cause all drawing commands so far to be executed ASAP. */
    void draw_flush( void );

    /* Draw a straight line between (x1,y1) and (x2,y2) in the specified color. */
    void draw_line( float x1, float y1, 
            float x2, float y2, 
            const float color[4] );

/* Draw a triangle with specified corners in the specified color. */
void draw_triangle( float x1, float y1, float x2, float y2, 
        float x3, float y3,
        const float color[4] );

/* Draw a rectangle from one corner (x1,y1) to the opposite corner
   (x2,y2) in the specified color. */
void draw_rectangle( float x1, float y1, 
        float x2, float y2, 
        const float color[4] );

/* Draw a single square point of the specified color. */
void draw_point( float x, float y, const float color[4] );
