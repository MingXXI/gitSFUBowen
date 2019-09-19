/* Deque Test Program 2 */
#include <cstring>
#include <iostream>
#include "Deque.h"

using namespace std ;

int main (int argc, char * const argv[]) {
    cout << "\n\nDeque Class Test Program 1 - START\n\n";

    // Make a Deque
    Deque * dq1 = new Deque();
    dq1->display();

    // Insert some elements from both ends.
    dq1->push_left(1);
    dq1->push_right(101);
    dq1->push_left(2);
    dq1->push_right(102);
    dq1->push_left(3);
    dq1->push_right(103);
    dq1->push_left(4);
    dq1->push_right(104);
    dq1->display();
    while( dq1->size() > 0 ){
	cout << "removing " << dq1->peek_left() << endl ;
        dq1->pop_left();
	dq1->display();
    }

    dq1->push_left(1);
    dq1->push_right(101);
    dq1->push_left(2);
    dq1->push_right(102);
    dq1->push_left(3);
    dq1->push_right(103);
    dq1->push_left(4);
    dq1->push_right(104);
    dq1->display();
    while( dq1->size() > 0 ){
	cout << "removing " << dq1->peek_right() << endl ;
        dq1->pop_right();
	dq1->display();
    }

    cout << "\n\nDeque Class Test Program 2 - DONE\n\n";
    return 0;
}
