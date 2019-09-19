/* Deque Test Program 3 */
#include <cstring>
#include <iostream>
#include "Deque.h"

using namespace std ;

int main (int argc, char * const argv[]) {
    cout << "\n\nDeque Class Test Program 3 - START\n\n";

    // Make a Deque
    Deque * dq1 = new Deque();
    dq1->display();

    // Insert some elements 
    dq1->push_left(1);
    dq1->push_left(2);
    dq1->push_left(3);
    dq1->push_left(4);
    dq1->push_left(5);
    dq1->push_left(6);
    dq1->push_left(7);
    dq1->push_left(8);
    dq1->display();
    // add 10 to each 
    int i = 0 ;
    do{
        dq1->set_cursor( 10 + dq1->get_cursor());
	dq1->display();
    }while( dq1->cursor_left());

    cout << "\n\nDeque Class Test Program 3 - DONE\n\n";
    return 0;
}
