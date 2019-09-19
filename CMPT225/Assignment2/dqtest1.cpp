/* Deque Test Program 1 */
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
    dq1->display();

    dq1->push_right(101);
    dq1->display();

    dq1->push_left(2);
    dq1->display();

    dq1->push_right(102);
    dq1->display();

    dq1->push_left(3);
    dq1->display();

    dq1->push_right(103);
    dq1->display();

    dq1->push_left(4);
    dq1->display();

    dq1->push_right(104);
    dq1->display();

    // Move the cursor right to the end
    // Do move right more times to verify what happens.
    dq1->cursor_right();
    dq1->display();
    dq1->cursor_right();
    dq1->display();
    dq1->cursor_right();
    dq1->display();
    dq1->cursor_right();
    dq1->display();
    dq1->cursor_right();
    dq1->display();
    dq1->cursor_right();
    dq1->display();
    dq1->cursor_right();
    dq1->display();

    // Move the cursor all the way to the left.
    while( dq1->cursor_left() ){;}
    dq1->display();

    cout << "\n\nDeque Class Test Program 1 - DONE\n\n";
    return 0;
}
