/*
   roids.c (c) Richard Vaughan 2015
   An Asteroids variant with a Mondrian flavour for artistic destruction.
 */

#include <assert.h>
#include <math.h>
#include <stdint.h> // for uint8_t
#include <stdio.h>
#include <stdlib.h> // for realloc()
#include <string.h>
#include <unistd.h> // for usleep()

#include "brightcolor.h" // library for generating nice, bright colors
#include "gui.h" // library for creating a graphical user interface

// gameplay parameters

const double SHIP_SIZE = 0.05;
const double SHIP_BASE_WIDTH = 2.2;
const double SHIP_SPIN_SPEED = 0.1; 
const double SHIP_THRUST = 0.0003; // acceleration on the ship when thrusting
const double SHOT_THRUST = 5e-5; // acceleration a shot imparts on roids it hits
const double SHOT_LIFETIME = 80; // shot moves this many steps before being deleted
const double SHOT_SPEED = 0.01;
const float ROID_SIZE = 0.1;
const float ROID_SPEED_MAX = 0.003;
const size_t ROIDS_PER_LEVEL = 2;
const unsigned int ROID_LIFETIME = 5; // roid splits this many times

// graphics/ui settings

const float BACKGROUND_COLOR[4] = {0.2, 0.4, 0.2, 1.0};
const float ALPHA = 0.9;
const unsigned int WIDTH = 700;
const unsigned int HEIGHT = 700;
const size_t SLEEP_USEC = 2e4; // sleep to slow down the loop

// structures to represent the entities in the game

typedef struct roid {
    float x; // position of roid centre
    float y; //   "
    float width; // size
    float height; // size
    float dx; // movement in x per update step
    float dy; // movement in y per update step
    float color[4]; // draw color in gui
    unsigned int lifetime; // when this counter reaches zero, roid is split or deleted
} roid_t;

typedef struct {
    float x; // ship centre position
    float y; // ship centre position
    float a; // ship orientation in radians
    float size; // ship size
    float dx; // ship movement in x per update step
    float dy; // ship movement in y per update step
    float da; // ship rotation speed in a per update step
    int thrust; // 1 if thrust key is pressed, else 0
} ship_t;

typedef struct {
    float x; // shot position
    float y; // shot position
    float dx; // shot movement in x per update step
    float dy; // shot movement in y per update step
    unsigned int lifetime; // when this counter reaches zero, shot is deleted
} shot_t;

// GLOBAL VARIABLES

// The player's ship. 
ship_t ship;

roid_t* roids = NULL; // array of asteroids that currently exist
size_t numroids = 0; // length of array

shot_t* shots = NULL; // array of shots that currently exist
size_t numshots = 0; // length of array

int paused = 0; // while non-zero, nothing is updated


// -- functions that operate on the ship ------------------------------------------------

ship_t ship_create()
{
    ship_t ship;
    ship.size = SHIP_SIZE; // specified by fraction of world (1x1)
    ship.x = 0.5; // position
    ship.y = 0.5;
    ship.a = M_PI/2.0; // heading
    ship.dx = 0; // speed
    ship.dy = 0; 
    ship.da = 0.0;
    ship.thrust = 0; // ship is not thrusting

    return ship;
}

/* First, update the current speed by accelerating (adding speed due
   to thrust @SHIP_THRUST in direction of current
   heading). Update the position and orientation of a ship for one
   timestep, according to the current speeds, and wrapping around the
   toroidal world (which is 1x1 units across). */
void ship_update( ship_t* ship )
{
    ship->x += ship->dx;
    ship->y += ship->dy;
    ship->a += ship->da;

    ship->dx += ship->thrust * SHIP_THRUST * cos(ship->a);
    ship->dy += ship->thrust * SHIP_THRUST * sin(ship->a);      

    ship->x = fmod( ship->x + 1.0, 1.0 );
    ship->y = fmod( ship->y + 1.0, 1.0 );
    ship->a = fmod( ship->a, 2.0 * M_PI );
}

void ship_draw( const ship_t* ship )
{
    float shipcolor[4] = { 1,1,0,1 };
    float thrustcolor[4] = { 1, 0.2, 0, 0.8 };

    float dx = ship->size * cos( ship->a );
    float dy = ship->size * sin( ship->a );

    float lx = ship->size/2.0 * cos( fmod( ship->a + SHIP_BASE_WIDTH, 2.0*M_PI) );
    float ly = ship->size/2.0 * sin( fmod( ship->a + SHIP_BASE_WIDTH, 2.0*M_PI) );

    float rx = ship->size/2.0 * cos( fmod( ship->a - SHIP_BASE_WIDTH, 2.0*M_PI) );
    float ry = ship->size/2.0 * sin( fmod( ship->a - SHIP_BASE_WIDTH, 2.0*M_PI) );

    draw_triangle( ship->x + dx, ship->y + dy,
            ship->x + lx, ship->y + ly,
            ship->x + rx, ship->y + ry,
            shipcolor );

    if( ship->thrust )
    {
        
        draw_triangle( ship->x - dx, ship->y - dy,
                ship->x + lx, ship->y + ly,
                ship->x + rx, ship->y + ry,
                thrustcolor );                 
        draw_triangle( ship->x - dx-1, ship->y - dy,
                ship->x + lx-1, ship->y + ly,
                ship->x + rx-1, ship->y + ry,
                thrustcolor );  
        draw_triangle( ship->x - dx+1, ship->y - dy,
                ship->x + lx+1, ship->y + ly,
                ship->x + rx+1, ship->y + ry,
                thrustcolor );  
        draw_triangle( ship->x - dx, ship->y - dy-1,
                ship->x + lx, ship->y + ly-1,
                ship->x + rx, ship->y + ry-1,
                thrustcolor );  
        draw_triangle( ship->x - dx, ship->y - dy+1,
                ship->x + lx, ship->y + ly+1,
                ship->x + rx, ship->y + ry+1,
                thrustcolor );  
        draw_triangle( ship->x - dx-1, ship->y - dy-1,
                ship->x + lx-1, ship->y + ly-1,
                ship->x + rx-1, ship->y + ry-1,
                thrustcolor );  
        draw_triangle( ship->x - dx-1, ship->y - dy+1,
                ship->x + lx-1, ship->y + ly+1,
                ship->x + rx-1, ship->y + ry+1,
                thrustcolor );  
        draw_triangle( ship->x - dx+1, ship->y - dy-1,
                ship->x + lx+1, ship->y + ly-1,
                ship->x + rx+1, ship->y + ry-1,
                thrustcolor );  
        draw_triangle( ship->x - dx+1, ship->y - dy+1,
                ship->x + lx+1, ship->y + ly+1,
                ship->x + rx+1, ship->y + ry+1,
                thrustcolor );  





    }
    if(ship->x + dx>1 || ship->y + dy>1 ||
            ship->x + lx>1 || ship->y + ly>1 ||
            ship->x + rx>1 || ship->y + ry>1 || ship->x + dx<0 || ship->y + dy<0 ||
            ship->x + lx<0 || ship->y + ly<0 ||
            ship->x + rx<0 || ship->y + ry<0){
        draw_triangle( ship->x + dx -1, ship->y + dy,ship->x + lx-1, ship->y + ly,
            ship->x + rx-1, ship->y + ry,
            shipcolor );
        draw_triangle( ship->x + dx+1, ship->y + dy,
            ship->x + lx+1, ship->y + ly,
            ship->x + rx+1, ship->y + ry,
            shipcolor );
        draw_triangle( ship->x + dx, ship->y + dy-1,
            ship->x + lx, ship->y + ly-1,
            ship->x + rx, ship->y + ry-1,
            shipcolor );
        draw_triangle( ship->x + dx, ship->y + dy+1,
            ship->x + lx, ship->y + ly+1,
            ship->x + rx, ship->y + ry+1,
            shipcolor );
        draw_triangle( ship->x + dx-1, ship->y + dy-1,
            ship->x + lx-1, ship->y + ly-1,
            ship->x + rx-1, ship->y + ry-1,
            shipcolor );
        draw_triangle( ship->x + dx-1, ship->y + dy+1,
            ship->x + lx-1, ship->y + ly+1,
            ship->x + rx-1, ship->y + ry+1,
            shipcolor );
        draw_triangle( ship->x + dx+1, ship->y + dy-1,
            ship->x + lx+1, ship->y + ly-1,
            ship->x + rx+1, ship->y + ry-1,
            shipcolor );
        draw_triangle( ship->x + dx+1, ship->y + dy+1,
            ship->x + lx+1, ship->y + ly+1,
            ship->x + rx+1, ship->y + ry+1,
            shipcolor );
    }

    


    /* TASK 3 */
    /* TODO: 
       more drawing so that the ship and its thrust jet appears to
       wrap around the 1x1 world correctly.
     */
}

// -- functions that operate on shots --------------------------------

/* Initialize a shot structure. The initial location of the shot is
   the nose of the ship, the magnitude of the speed is SHOT_SPEED, in
   the same direction that the ship is pointing. The initial lifetime
   is @SHOT_LIFETIME.
 */
shot_t shot_create()
{
    shot_t s;
    s.x = ship.x + ship.size * cos( ship.a );
    s.y = ship.y + ship.size * sin( ship.a );
    s.dx = SHOT_SPEED * cos( ship.a );
    s.dy = SHOT_SPEED * sin( ship.a );
    s.lifetime = SHOT_LIFETIME;
    return s;
}

/* Add a new shot to the end of the array @shots and increment
   numshots by 1. The new shot should be initialized by
   shot_create(). */
void shot_add( void )
{
    shots = realloc( shots, ++numshots * sizeof(shot_t) );
    shots[numshots-1] = shot_create();
}

/* Update the position of a shot for one timestep, according to the
   current speeds, and wrapping around the toroidal world (which is
   1x1 units across). */
void shot_update( shot_t* shot )
{
    shot->x += shot->dx;
    shot->y += shot->dy;

    shot->x = fmod( shot->x + 1.0, 1.0 );
    shot->y = fmod( shot->y + 1.0, 1.0 );

    shot->lifetime--; // will be deleted when this gets to zero
}

/* Render the shot in the GUI */
void shot_draw( const shot_t* shot )
{
    float color[4] = {1,1,1,1}; // white 
    draw_point( shot->x, shot->y, color );
}

/* remove all shots with age zero from the global array @shots. Update
   the counter @numshots to reflect the new artay length. */
void shots_harvest( void )
{
    for( int i=0; i<numshots; i++ )
        if( shots[i].lifetime == 0 ) 
        {
            // copy the last roid over the expired one
            shots[i] = shots[--numshots];         
            i--;
        }
}

// -- functions that operate on roids -------------------------------

/* Initialize a new roid structure */
roid_t roid_create( void )
{
    roid_t roid;

    // initial position and speed set at random
    roid.x = drand48();
    roid.y = drand48();
    roid.dx = (drand48() * 2.0 * ROID_SPEED_MAX) - ROID_SPEED_MAX;
    roid.dy = (drand48() * 2.0 * ROID_SPEED_MAX) - ROID_SPEED_MAX;

    // roid size is fixed
    roid.width = ROID_SIZE * BRIGHT_COLOR_GOLDEN_RATIO; 
    roid.height = ROID_SIZE; 

    // this roid has not been shot yet
    roid.lifetime = ROID_LIFETIME;

    // force one of the axes to have a zero coordinate
    // so the roid starts at the edge of the screen
    if( drand48() > 0.5 )
        roid.x = 0;
    else
        roid.y = 0;

    // set the draw color to a nice bright color
    bright_color( random(), roid.color );

    return roid;
}

/* Add @num new roids to the global array @roids and increase
   @roidcount by @num. New roids are initialized by roid_create() */
void roids_add( size_t num )
{
    numroids += num;

    roids = realloc( roids, numroids * sizeof(roid_t));
    for( int i=0; i<numroids; i++ )
        roids[i] = roid_create();    
}

/* Update the position of a roid for one timestep,
   according to the current speeds, and wrapping around the toroidal
   world (which is 1x1 units across). */
void roid_update( roid_t* roid ) 
{
    roid->x += roid->dx; 
    roid->y += roid->dy;  
    roid->x = fmod( roid->x + 1.0, 1.0 );
    roid->y = fmod( roid->y + 1.0, 1.0 );  
}

/* Split a roid along its longest axis into two equal halves. The
   halves should occupy the same rectangular area of the world as the
   original roids. The orginal roid should be modified to become the
   left or bottom half. The right or top half should be a new roid
   added to to the end of the roids array. Global @numroids is
   incremented by one to count the new right-hand roid. The new roid
   should have a random bright color. The original roid should keep
   its existing color. */
void roid_split( unsigned int index )
{
    // add room for one more roid
    roids = realloc( roids, ++numroids * sizeof(roid_t));

    roid_t* original = &roids[index]; // original roid
    roid_t* newbie = &roids[numroids-1]; // new roid

    double shiftx = 0;
    double shifty = 0;

    if( original->width > original->height )
    {
        original->width /= 2;
        shiftx = original->width/2;
    }
    else
    {
        original->height /= 2;
        shifty = original->height/2;
    }

    memcpy( newbie, original, sizeof(roid_t));

    original->x -= shiftx;
    original->y -= shifty;

    newbie->x += shiftx;
    newbie->y += shifty;

    bright_color( random(), newbie->color );
}

/* Draw one or more rectangles to represent a roid. Roids that overlap
   the edge of the world are drawn so that the whole roid area is
   visible, E.g. a roid extending over the right-edge of the world has
   its right side visible at the left side of the world. */
void roid_draw( const roid_t* roid )
{
    // draw a rectangle around centre of the roid.
    draw_rectangle( roid->x-roid->width/2.0, roid->y-roid->height/2.0, 
            roid->x+roid->width/2.0, roid->y+roid->height/2,
            roid->color );

    /* TASK 4 */
    /* TODO: 
       more drawing so that the roids appear to wrap around the
       1x1 world correctly.
     */
    if(roid->x-roid->width/2.0 <0 || roid->y-roid->height/2.0 <0 || 
            roid->x+roid->width/2.0 <0 || roid->y+roid->height/2 <0 ||
            roid->x-roid->width/2.0 >1 || roid->y-roid->height/2.0 >1 || 
            roid->x+roid->width/2.0 >1 || roid->y+roid->height/2 >1
            ){
        draw_rectangle( 1+roid->x-roid->width/2.0, roid->y-roid->height/2.0, 
            1+roid->x+roid->width/2.0, roid->y+roid->height/2,
            roid->color );
        draw_rectangle( roid->x-roid->width/2.0, 1+roid->y-roid->height/2.0, 
            roid->x+roid->width/2.0, 1+roid->y+roid->height/2,
            roid->color );
        draw_rectangle( 1+roid->x-roid->width/2.0, 1+roid->y-roid->height/2.0, 
            1+roid->x+roid->width/2.0, 1+roid->y+roid->height/2,
            roid->color );
        draw_rectangle( roid->x-1-roid->width/2.0, roid->y-roid->height/2.0, 
            roid->x-1+roid->width/2.0, roid->y+roid->height/2,
            roid->color );
        draw_rectangle( roid->x-roid->width/2.0, roid->y-1-roid->height/2.0, 
            roid->x+roid->width/2.0, roid->y-1+roid->height/2,
            roid->color );
        draw_rectangle( roid->x-1-roid->width/2.0, roid->y-1-roid->height/2.0, 
            roid->x-1+roid->width/2.0, roid->y-1+roid->height/2,
            roid->color );
        draw_rectangle( roid->x-1-roid->width/2.0, roid->y+1-roid->height/2.0, 
            roid->x-1+roid->width/2.0, roid->y+1+roid->height/2,
            roid->color );
        draw_rectangle( roid->x+1-roid->width/2.0, roid->y-1-roid->height/2.0, 
            roid->x+1+roid->width/2.0, roid->y-1+roid->height/2,
            roid->color );
    }
    
}

/* Remove all roids that have lifetime of zero from the global array
   @roids. Update @numroids to reflect the new length of the array. */
void roids_harvest( void )
{
    for( int i=0; i<numroids; i++ )
        if( roids[i].lifetime == 0  ) 
        {
            // copy the last roid over the expired one
            roids[i] = roids[--numroids];
            i--;
        }  
}

// -- shots interactimg with roids -----------------------------------

/* Returns non-zero (true) if the shot is located in the rectangle
   occupied by the roid, else zero (false). Takes into account the
   toroidal shape of the world (sized 1x1 units). */
int shot_roid_hit( const shot_t* shot, const roid_t* roid )
{
    /* TASK 5 */
    /* TODO: modify this code so it takes into account the toroidal
       shape of the world.
     */

    return( (shot->x >= roid->x - roid->width/2 &&
            shot->x <= roid->x + roid->width/2 &&
            shot->y >= roid->y - roid->height/2 &&
            shot->y <= roid->y + roid->height/2) || 

            (shot->x >= roid->x + 1 - roid->width/2 &&
            shot->x <= roid->x + 1 + roid->width/2 &&
            shot->y >= roid->y - roid->height/2 &&
            shot->y <= roid->y + roid->height/2) ||

            (shot->x >= roid->x - 1 - roid->width/2 &&
            shot->x <= roid->x - 1 + roid->width/2 &&
            shot->y >= roid->y - roid->height/2 &&
            shot->y <= roid->y + roid->height/2) ||

            (shot->x >= roid->x - roid->width/2 &&
            shot->x <= roid->x + roid->width/2 &&
            shot->y >= roid->y + 1 - roid->height/2 &&
            shot->y <= roid->y + 1 + roid->height/2) ||

            (shot->x >= roid->x - roid->width/2 &&
            shot->x <= roid->x + roid->width/2 &&
            shot->y >= roid->y - 1 - roid->height/2 &&
            shot->y <= roid->y - 1 + roid->height/2) ||

            (shot->x >= roid->x + 1 - roid->width/2 &&
            shot->x <= roid->x + 1 + roid->width/2 &&
            shot->y >= roid->y - 1 - roid->height/2 &&
            shot->y <= roid->y - 1 + roid->height/2) ||

            (shot->x >= roid->x - 1 - roid->width/2 &&
            shot->x <= roid->x - 1 + roid->width/2 &&
            shot->y >= roid->y + 1 - roid->height/2 &&
            shot->y <= roid->y + 1 + roid->height/2) ||

            (shot->x >= roid->x + 1 - roid->width/2 &&
            shot->x <= roid->x + 1 + roid->width/2 &&
            shot->y >= roid->y + 1 - roid->height/2 &&
            shot->y <= roid->y + 1 + roid->height/2) ||

            (shot->x >= roid->x - 1 - roid->width/2 &&
            shot->x <= roid->x - 1 + roid->width/2 &&
            shot->y >= roid->y - 1 - roid->height/2 &&
            shot->y <= roid->y - 1 + roid->height/2) ); 

}

/* Modify roid speed by applying a force with magnitude @SHOT_THRUST
   in the same direction as the shot */
void shot_roid_push( const shot_t* shot, roid_t* roid )
{
    // add some speed in the direction the shot hit from
    const double angle =  atan2( roid->y - shot->y, roid->x - shot->x );
    roid->dx += SHOT_THRUST * cos(angle);
    roid->dy += SHOT_THRUST * sin(angle);
}

// -- callback functions used to respond to the GUI ---------------------

// Callback to redraw the window contents
void display(void)
{
    draw_clear( BACKGROUND_COLOR ); // clears window

    ship_draw( &ship );

    for( int i=0; i<numroids; i++ )
        roid_draw( &roids[i] );

    for( int i=0; i<numshots; i++ )
        shot_draw( &shots[i] );

    draw_flush(); // finish all drawing right now
}

/* Callback for a GUI key-press event. @key is the key pressed, @x and
   @y are the current mouse pointer location when it was pressed. */
void key_down( unsigned char key, int x, int y )
{
    /* TASK 1 */
    /* TODO:
       using a switch/case statement:
       if key is 'z', set ship rotation speed ship.da to SHIP_SPIN_SPEED
       if key is 'x', set ship rotation speed ship.da to -SHIP_SPIN_SPEED
       if key is 'p', invert the truth value of paused 
       (ie. non-zero to zero, zero to non-zero)
       if key is 'm', set ship.thrust to 1.

       if key is ' ', call shot_add()
     */

	switch (key){
		case 'z':
			ship.da = SHIP_SPIN_SPEED;
			break;
		case 'x':
			ship.da = -SHIP_SPIN_SPEED;
			break;
		case 'p':
			if (paused == 0){
				paused = 1;
			} else {
				paused = 0;
			}
			break;
		case 'm':
			ship.thrust = 1;
			break;
		case ' ':
			shot_add();
			break;
	}
}	

/* Callback for a GUI key-release event. @key is the key pressed, @x and
   @y are the current mouse pointer location when it was pressed. */
void key_up( unsigned char key, int x, int y )
{
    /* TASK 2 */
    /* TODO:     
       using a switch/case statement
       if key is 'z' or 'x', set ship rotation speed ship.da to zero.
       if key is 'm', set ship.thrust to zero.
     */
	switch (key){
		case 'z':
		case 'x':
			ship.da = 0;
			break;
		case 'm':
			ship.thrust = 0;
			break;
	}
}

// -- main: program start and main loop logic --------------------------------
int main(int argc, char** argv)
{
    // initialize the graphics systems
    bright_color_init( ALPHA );

    // the last three arguments are pointers to callback functions to
    // handle redrawing the window, key-presses and key-releases,
    // respectively. See gui.h for details.
    gui_init( argc, argv, WIDTH, HEIGHT, display, key_down, key_up );

    ship = ship_create();

    size_t level = 0;

    while( 1 )
    {
        gui_handle_events(); // check for any action in the user interface      

        // if we are starting up or all the roids are gone, start a new level
        if( numroids == 0 )
        {
            level++;
            printf( "LEVEL %lu\n", level );
            roids_add( level * ROIDS_PER_LEVEL ); // create new roids
        }

        if( ! paused )
        {     
            // check each roid for shot hits
            for( int j=0; j<numroids; j++ )
            {
                if( roids[j].lifetime == 0 ) // if roid has already taken enough hits, skip over it.
                    break;

                for( int i=0; i<numshots; i++ )
                {
                    if( shots[i].lifetime && shot_roid_hit( &shots[i], &roids[j] ))
                    {
                        roids[j].lifetime--;
                        shots[i].lifetime = 0; // this shot is done

                        // split roid into 2 smaller roids
                        roid_split( j ); 

                        // momentum transfer from shot to both pieces
                        shot_roid_push( &shots[i], &roids[j] );
                        shot_roid_push( &shots[i], &roids[numroids-1] );

                        break; // only one shot can impact a roid per update
                    }
                }
            }

            // now destroy all roids and shots with lifetime == 0
            roids_harvest();        
            shots_harvest();

            ship_update( &ship );   

            for( int i=0; i<numshots; i++ )
                shot_update( &shots[i] );

            for( int i=0; i<numroids; i++ )
                roid_update( &roids[i] );

            // ask the GUI to redraw the window when it's ready to do so.
            gui_redraw();
        }

        usleep( SLEEP_USEC ); // slow things down for humans
    }

    return 0;
}
