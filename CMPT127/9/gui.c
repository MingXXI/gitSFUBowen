/* gui.c - a very simple GUI interface that wraps FreeGLUT.
   (C) Richard Vaughan 2015
 */

#include <GL/freeglut.h>
#include "gui.h"

/* -- GUI FUNCTIONS ---------------------------------------*/

void gui_init( int argc, 
        char** argv, 
        unsigned int width,
        unsigned int height,
        void (*display_func)(void),
        void (*key_down_func)(unsigned char, int, int),
        void (*key_up_func)(unsigned char, int, int) 
        )
{
    // configure a window and display context
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( width, height );
    glutCreateWindow( argv[0] );
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glutIgnoreKeyRepeat( 1 ); // disable key repeat
    glPointSize(4); // big chunky points

    // set the projection matrix for a 2D top-down view.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    // install callbacks if supplied
    if( display_func )
        glutDisplayFunc(display_func );

    if( key_down_func )
        glutKeyboardFunc( key_down_func ); // when a key goes down

    if( key_up_func )
        glutKeyboardUpFunc( key_up_func ); // when a key goes up
}

void gui_redraw( void )
{
    glutPostRedisplay();
}

void gui_handle_events( void )
{
    glutMainLoopEvent();
}

/* -- DRAWING FUNCTIONS -----------------------------------------*/

void draw_clear( const float color[4] )
{
    glClearColor( color[0], color[1], color[2], color[3] ); //  background color
    glClear(GL_COLOR_BUFFER_BIT); // clear screen
}

void draw_flush( void )
{
    glFlush(); 
}

void draw_line( float x1, float y1, float x2, float y2, const float color[4] )
{
    glColor4fv( color );
    glBegin(GL_LINES);
    glVertex2f( x1, y1 );
    glVertex2f( x2, y2 );
    glEnd();
}

void draw_triangle( float x1, float y1, 
        float x2, float y2, 
        float x3, float y3,
        const float color[4] )
{
    glColor4fv( color );
    glBegin(GL_TRIANGLES);
    glVertex2f( x1, y1 );
    glVertex2f( x2, y2 );
    glVertex2f( x3, y3 );
    glEnd();

    const float dark = 0.2;
    glColor4f( dark * color[0], dark * color[1], dark * color[2], 1.0 );

    glLineWidth( 2.0 );
    glBegin(GL_LINE_LOOP);
    glVertex2f( x1, y1 );
    glVertex2f( x2, y2 );
    glVertex2f( x3, y3 );
    glEnd();

}

void draw_rectangle( float x1, float y1, 
        float x2, float y2, 
        const float color[4] )
{
    glColor4fv( color );
    glRectf( x1, y1, x2, y2 );

    const float dark = 0.2;
    glColor4f( dark * color[0], dark * color[1], dark * color[2], 1.0 );

    glLineWidth( 2.0 );
    glBegin(GL_LINE_LOOP);
    glVertex2f( x1, y1 );
    glVertex2f( x2, y1 );
    glVertex2f( x2, y2 );
    glVertex2f( x1, y2 );
    glEnd();
}

void draw_point( float x, float y, const float color[4] )
{
    glColor4fv( color );
    glBegin( GL_POINTS );
    glVertex2f( x, y );
    glEnd();
}
