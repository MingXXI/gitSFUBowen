#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

#include "point_array.h"

void point_print( point_t* p )
{
  if( p == NULL )
  {
     puts( "(NULL)" );
     return;
  }
  
  printf( "(%.1f, %.1f %.1f) ",
	  p->x, p->y, p->z );
}

void point_array_print( point_array_t* pa )
{
  if( pa == NULL )
  {
      puts( "(NULL)" );
      return;
  }

  printf( "len:%d\n", 
	  (int)pa->len );

  for( int i=0; i<pa->len; i++ )
  {
      printf( " [%d]-", i );
      
      point_print( pa->points+i );
      printf( "\n" );
  }
  printf( "\n" );
}

// returns the current system time in microseconds
uint64_t time_now_usec( void )
{
  struct timeval now;
  gettimeofday( &now, NULL );
  return (uint64_t) now.tv_sec * 1e6 + now.tv_usec;     
}

int main( int argc, char** argv )
{
  printf( "#           LENGTH          APPEND(usec)    REMOVE(usec)\n" ); 
  fflush(stdout);

  point_t p;
  p.x = drand48();
  p.y = drand48();
  p.z = drand48();
  
  size_t pts = 16;

  for( int rep = 0; rep<12; rep++ )
  {
      point_array_t A;
      point_array_init( &A );
      
      uint64_t start_append = time_now_usec();
      
      for( unsigned long i=0; i<pts; i++ )
      {
        point_array_append( &A, &p );    
      }
      
      uint64_t app_time = time_now_usec() - start_append;
      
      uint64_t start_remove = time_now_usec();
      
      for( int i=0; i<pts; i++ )
        point_array_remove( &A, random() % A.len );
           
      uint64_t rem_time = time_now_usec() - start_remove;
      
      printf( "%d\t%10lu\t%10lu\t%10lu\t\n", 
	      rep,
	      (unsigned long)pts, 
	      (unsigned long)app_time,
	      (unsigned long)rem_time ); 

      uint64_t app_limit = 1e6; 
      if( app_time > app_limit )
	  {
          printf( "# appending %lu points look too long (limit %lu usec)\n",
              (unsigned long)pts, (unsigned long)app_limit );	   
          fflush(stdout);
          return 1;
	  }

      uint64_t rem_limit = 1e6; 
      if( rem_time > rem_limit )
	  {
          printf( "# removing %lu points look too long (limit %lu usec)\n",
              (unsigned long)pts, (unsigned long)rem_limit );	   
          fflush(stdout);
          return 1;
	  }      

      pts *= 2;
  }
  return 0;
}
