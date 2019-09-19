// SOLUTION: Custom string functions

#include "mystring.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *  mystrlen() calculates the length of the string s, 
 *  not including the terminating character '\0'.
 *  Returns: length of s.
 */
int mystrlen (const char *s) 
{
	int length = 0;
	while (s[length] != '\0') {
		length++;
	}
	return length;
}

/*
 *  mystrcpy()  copies the string pointed to by src (including the terminating 
 *  character '\0') to the array pointed to by dst.
 *  Returns: a  pointer to the destination string dst.
 */
char  *mystrcpy (char *dst, const char *src)
{
	int index = -1;
	do {
		index++;
		dst[index] = src[index];
	} while (src[index] != 0);
	return dst;
}

/*
 * mystrcmp() compares two strings alphabetically
 * Returns: 
 * 	-1 if s1  < s2
 *  	0 if s1 == s2
 *  	1 if s1 > s2
 */
int mystrcmp(const char *s1, const char *s2)
{
	while (1) {
		// Does this character differentiate the strings?:
		if (*s1 < *s2) {
			return -1;
		}
		if (*s1 > *s2) {
			return 1;
		}
		if (*s1 == 0 && *s2 == 0) {
			break;
		}

		// Move on
		s1++;
		s2++;
	}
	return 0;
}

/*
 * mystrdup() creates a duplicate of the string pointed to by s. 
 * The space for the new string is obtained using malloc.  
 * If the new string can not be created, a null pointer is returned.
 * Returns:  a pointer to a new string (the duplicate) 
 	     or null If the new string could not be created for 
	     any reason such as insuffient memory. 
 */
char *mystrdup(const char *src)
{
	int length = mystrlen(src);
	int bytesRequired = length + 1;
	char* newString = malloc(bytesRequired);

	if (newString != NULL) {
		mystrcpy(newString, src);
	}

	return newString;
}

