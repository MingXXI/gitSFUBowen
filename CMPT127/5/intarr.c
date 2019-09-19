/* 
 * intarr.h
 *
 * Provides a bounds-checked, resizable array of integers with
 * random-access and stack interfaces, and several utility functions
 * that operate on them.
 * 
 */

/* DO NOT CHANGE THIS FILE - YOUR CODE WILL BE COMPILED AGAINST THE
   ORIGINAL. NON-COMPILING CODE WILL FAIL ALL THE TASKS!

   FOR TASKS WITH MORE THAN ONE FUNCTION, YOU MUST IMPLEMENT ALL
   FUNCTIONS TO PASS THE TASK.
*/

/* Structure type that encapsulates our safe int array. */
 #include <assert.h>
 #include <stdint.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 #include "intarr.h"
  
/* A type for returning status codes */
/* LAB 5 TASK 1 */

// Create a new intarr_t with initial size len.  If successful
// (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated intarr_t.  If unsuccessful, returns a null pointer.
intarr_t* intarr_create( unsigned int len ){
	intarr_t *n1= NULL;
	n1= malloc(sizeof(intarr_t));
	if (n1 != NULL){
		n1->data=malloc(len*sizeof(int));
		if (n1->data == NULL){
			free(n1);
		}
		else{
			n1->len=len;
		}
	}
	return n1;
}

// frees all memory allocated for ia. If the pointer is null, do
// nothing. If the ia->data is null, do not attempt to free it.
void intarr_destroy( intarr_t* ia ){
	if (ia==NULL){
	}else{
		if (ia->data != NULL){
			free(ia->data);
		}
		else{
			free(ia);
		}
	}
}

/* LAB 5 TASK 2 */

// If index is valid, set the value at ia->data[index] to val and return
// INTARR_OK. Otherwise, leave the array unmodified and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_set( intarr_t* ia, 
			    unsigned int index, 
			    int val ){
	if (ia==NULL){
		return INTARR_BADARRAY;
	}else {
		if (index< ia->len){
			ia->data[index]=val;
			return INTARR_OK;
		}else {
			return INTARR_BADINDEX;
		}
	}
	return 0;
}

// If index is valid and i is non-null, set *i to ia->data[index] and return
// INTARR_OK. Otherwise no not modify *i and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_get( const intarr_t* ia, 
			    unsigned int index, 
			    int* i ){
	if(ia==NULL){
		return INTARR_BADARRAY;
	}
	if(index<ia->len && i!= NULL){
		*i=ia->data[index];
		return INTARR_OK;
	} else {
		return INTARR_BADINDEX;
	} 

}
/* LAB 5 TASK 3 */

// Return a duplicate of ia, allocating new storage for the duplicate
// data (we call this a "deep copy"). If unsuccessful (i.e. memory
// allocation for the copy fails, or ia is null), return a null pointer. 
intarr_t* intarr_copy( const intarr_t* ia ){
	if (ia == NULL){
		return NULL;
	}else {
		intarr_t *copy= intarr_create(ia->len);
		copy->data= malloc(ia->len * sizeof(int));
		copy->len= ia->len;
		memcpy(copy->data, ia->data, ia->len * sizeof(int));
		return copy;
	}
}

/* LAB 5 TASK 4 */

// sort ia by value smallest-to-largest, so that data[i] < data[i+1]
// for all valid i, then return INTARR_OK. Works in-place: contents of
// ia are sorted on return. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_sort( intarr_t* ia ){
	if (ia==NULL){
		return INTARR_BADARRAY;
	}else {
		for (int i=0; i<ia->len; i++){
			int smallest=ia->data[i];
			for (int j=i+1; j<ia->len; j++){
				if (ia->data[j]<smallest){
					int change=smallest;
					smallest=ia->data[j];
					ia->data[j]=change;
				}
			ia->data[i]=smallest;
			}
		}
		return INTARR_OK;
	}
}

/* LAB 5 TASK 5 */

// Find the first occurence of the target in the array, searching from
// index 0. If the target is found and i is non-null, set *i to the
// location index and return INTARR_OK. If target does not occur in
// the array, leave *i unmodified and return INTARR_NOTFOUND. If ia is
// null, return INTARR_BADARRAY.
intarr_result_t intarr_find( intarr_t* ia, int target, int* i ){
	if (ia == NULL){
    		return INTARR_BADARRAY;
  	}
  	for (int k = 0; k < ia->len; k++){
    		if (ia->data[k] == target){
      			if ( i != NULL){
        			*i = k;
        			return INTARR_OK;
      			}
    		}
  	}
  	return INTARR_NOTFOUND;
}
	

/* LAB 5 TASK 6 */

// Append val to the end of ia (allocating space for it). If
// successful, return INTARR_OK, otherwise return
// INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
// Take a look at TASK 7 below and see if it might be helpful
intarr_result_t intarr_push( intarr_t* ia, int val ){
	if (ia==NULL){
		return INTARR_BADARRAY;
	}
	ia->data=realloc(ia->data,sizeof(int)*(ia->len+1));
	if(!ia){
		return INTARR_BADALLOC;
	}
	ia->data[ia->len]=val;
	ia->len+=1;
	return INTARR_OK;
}
// If the array is not empty, remove the value with the highest index
// from the array, and, if i is non-null, set *i to the removed value,
// then return INTARR_OK. If the array is empty, leave *i unmodified
// and return INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
// Take a look at TASK 7 below and see if it might be helpful
intarr_result_t intarr_pop( intarr_t* ia, int* i ){
	if(ia==NULL){
		return INTARR_BADARRAY;
	}
	if(ia->len==0){
		return INTARR_BADINDEX;
	}
	*i=ia->data[ia->len-1];
	ia->data=realloc(ia->data,sizeof(unsigned int)*(ia->len-1));
	ia->len -=1;

	return INTARR_OK;
}

/* LAB 5 TASK 7 */

// Resize ia to contain newlen values. If newlen is less than the
// original array length, the end of the array is discarded. If newlen
// is greater than the original array length, intialize all the new
// integers to zero. If the allocation is successful, return
// INTARR_OK, otherwise return INTARR_BADALLOC. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_resize( intarr_t* ia, unsigned int newlen ){
	if(ia==NULL){
		return INTARR_BADARRAY;
	}
	if (newlen>ia->len){
		ia->data=realloc(ia->data,sizeof(int)*newlen);
		if (!ia){
			return INTARR_BADALLOC;
		}
		for(int i=ia->len;i<newlen;i++){
			ia->data[i]=0;
		}
		ia->len=newlen;
		return INTARR_OK;
	} else if (newlen<ia->len){
		ia->data=realloc(ia->data,sizeof(int)*newlen);
		if(!ia){
			return INTARR_BADALLOC;
		}
		ia->len=newlen;
		return INTARR_OK;
	} else{
		return INTARR_OK;
	}
}
/* LAB 5 TASK 8 */

// Get a deep copy of a portion of ia from index first to index last
// inclusive. If successful, return a pointer to a newly-allocated
// intarr_t containing a copy of the specfied section. If an error
// occurs, i.e. ia is null, first or last are out of bounds, last <
// first, or memory allocation fails, return a null pointer.
intarr_t* intarr_copy_subarray( intarr_t* ia, 
				unsigned int first, 
				unsigned int last ){
	if(ia==NULL || first<0 || last > ia->len || last<first){
		return NULL;
	}
	intarr_t *new=NULL;
	new=malloc(sizeof(intarr_t));
	if(new){
		new->data=malloc(sizeof(int)*(last-first+1));
		new->len=last-first+1;
		for (int i=0;i<new->len;i++){
			new->data[i]=ia->data[i+first];
		}
		return new;
	}else {
		return NULL;
	}
}

/* LAB 5 ENDS HERE */

/* -------------------------------------------------------------- */
