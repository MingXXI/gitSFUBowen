#include "Deque.h"
#include <iostream>
using namespace std;

Deque::Deque(){ // Constructs a new empty deque.
	left_p = NULL;
	right_p = NULL;
	current_size = 0;
	cursor = NULL;
}

Deque::Deque(const Deque& dq){
	left_p = NULL;
	right_p = NULL;
	current_size = 0;
	cursor = NULL;
	node *tmp = dq.left_p;
	node *cursor_place = dq.cursor;
	int place = 0;
	int num;
	while (cursor_place){
		cursor_place = cursor_place->next;
		place += 1;
	}
	while (tmp){
		num = tmp->data;
		push_right(num);
		tmp = tmp->prev;
	}
	for(int i = 0; i<place-1; i++){
		cursor = cursor->prev;
	}
	delete tmp;
	delete cursor_place;
}

Deque::~Deque(){// Destructor.
	while(left_p != NULL){
		pop_left();
	}
	delete cursor;
	delete left_p;
    delete right_p;
}

void Deque::push_left(int item){  // Inserts <item> at left end.
	if (left_p != NULL){
		left_p->next = new node(item, left_p, NULL);
		left_p = left_p->next;
	} else{
		left_p = new node(item, NULL, NULL);
	}
	if (current_size == 0){
		right_p = left_p;
		cursor = left_p;
	}
	current_size += 1;
}

void Deque::push_right(int item){  // Inserts <item> at right end.
	if (right_p != NULL){
		right_p->prev = new node(item, NULL, right_p);
		right_p = right_p->prev;
	} else{
		right_p = new node(item, NULL, NULL);
	}
	if(current_size == 0){
		left_p = right_p;
		cursor = right_p;
	}
	current_size += 1;
}

int Deque::pop_left (){  // removes item on left end.
        		  // Pre: Deque is not empty.
	node *temp = left_p;
	int tempnum = left_p->data;
	if (current_size == 1){
		cursor = NULL;
		left_p = NULL;
		right_p = NULL;
		delete temp;
		current_size -= 1;
		return tempnum;
	}
	if(cursor == left_p){
		cursor = cursor->prev;
	}
	left_p = left_p->prev;
	left_p->next = NULL;
	delete temp;
	current_size -= 1;
	return tempnum;
}

int Deque::pop_right(){  // removes item on right end.
        		  // Pre: Deque is not empty.
	int tempnum = right_p->data;
	node *temp = right_p;
	if (current_size == 1){
		cursor = NULL;
		left_p = NULL;
		right_p = NULL;
		delete temp;
		current_size -= 1;
		return tempnum;
	}
	if (cursor == right_p){
		cursor = cursor->next;
	}
 	right_p = right_p->next;
 	right_p->prev = NULL;
	delete temp;
	current_size -= 1;
	return tempnum;
}

bool Deque::empty(){  // Returns true iff the Deque contains no items.
	return (current_size == 0);
}

int Deque::size(){  // Returns the current number of items in the deque.
	return current_size;
}

bool Deque::cursor_left(){  // Move cursor left.
	if (cursor->next != NULL){
		cursor = cursor->next;
		return 1;
	}
	return 0;
}

bool Deque::cursor_right(){  // Move cursor right.
	if (cursor->prev != NULL){
		cursor = cursor->prev;
		return 1;
	}
	return 0;
}

int Deque::peek_left(){  // Returns the left-most item without removing it.
				  // Pre: Deque is not empty.
	return left_p->data;
}

int Deque::peek_right(){  // Returns the right-most item without removing it.
				   // Pre: Deque is not empty.
	return right_p->data;
}

int Deque::get_cursor(){  // Return value the cursor currently is at, 
				   // Pre: Deque is not empty.
	return cursor->data;
}
void Deque::set_cursor(int i){
	cursor->data = i;
}    
        // Pre: Deque is not empty.

void Deque::display(){ // prints a depiction of the deque contents to standard output.
	node *temp = left_p;
	cout << "[" ;
	for (int i=0; i<current_size; i++){
		cout << temp->data << ";" ;
		temp = temp->prev;
	}
	delete temp;
	cout << "] " ;
	if (current_size == 0){
		cout << "size=" << current_size << ", " << "cursor=NULL." << endl; 		
	} else{
		cout << "size=" << current_size << ", " << "cursor=" << get_cursor() << "." << endl; 
	}
	
}    

void Deque::verbose_display(){ // like display, but includes node addresses and pointer values.
	node *temp = left_p;
	for (int i=0; i<current_size; i++){
		cout << "the address of node at index " << i << " is: " << temp << " which value is: " << temp->data << endl;
		temp = temp->prev;
	}
	delete temp;
}
















