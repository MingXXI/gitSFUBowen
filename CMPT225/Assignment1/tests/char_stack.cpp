/* File: char_stack.cpp

  Implementation of functions for basic simple array-based implementation of a stack.

*/
#include "char_stack.h"// contains the declarations of the variables and functions.
#include <stdio.h>
#include <iostream>
using namespace std;

char_stack::char_stack(){
	current = new char;
	next = current;
	length = 0;
}

void char_stack::push(char item){
	*next = item;
	next += 1;
	length +=1;
}

char char_stack::pop(){
	char temp = *(next-1);
	next -= 1;
	length -= 1;
	return temp;
}

char char_stack::top(){
	char temp = *(next-1);
	return temp;
}

bool char_stack::empty(){
	if (length == 0){
		return true;
	} else {
		return false;
	}
}

int char_stack::size(){
	return length;
}
// Fill this in.