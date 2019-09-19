/* Deque Test Program 4 */
#include <cstring>
#include <iostream>
#include "Deque.h"

using namespace std ;

int main (int argc, char * const argv[]) {
    cout << "\n\nDeque Class Test Program 4 - START\n\n";

    // Make a Deque
    Deque dq1;

    // Insert some elements 
    dq1.push_left(1);
    dq1.push_left(2);
    dq1.push_left(3);
    dq1.push_left(4);
    dq1.push_left(5);
    dq1.push_left(6);
    dq1.push_left(7);
    dq1.push_left(8);
    dq1.cursor_left();
    dq1.cursor_left();
    dq1.cursor_left();
    dq1.display();

    // Make a copy
    Deque dq2(dq1);
    dq1.display();

    // Modify the original and the copy differently;
    dq1.cursor_left();
    dq1.set_cursor(8);
    dq2.cursor_right();
    dq2.set_cursor(9);
    dq1.display();
    dq2.display();

    // Make a Deque
    Deque * dq3 = new Deque();

    // Insert some elements 
    dq3->push_left(1);
    dq3->push_left(2);
    dq3->push_left(3);
    dq3->push_left(4);
    dq3->push_left(5);
    dq3->cursor_left();
    dq3->cursor_left();
    dq3->display();
 
    // Make a copy
    Deque * dq4 = new Deque(*dq3);
    dq4->display();

    // Modify the original and the copy differently;
    dq3->cursor_left();
    dq3->set_cursor(8);
    dq4->cursor_right();
    dq4->set_cursor(9);
    dq3->display();
    dq4->display();

    return 0;
}
