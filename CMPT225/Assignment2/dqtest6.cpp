/* Deque Test Program 6 */
#include <cstring>
#include <iostream>
#include "Deque.cpp"

using namespace std ;

int main (int argc, char * const argv[]) {
    cout << "\n\nDeque Class Test Program 6 - START\n\n";

    // Make a Deque
    Deque * dq1 = new Deque();
    for( int i = 0 ; i<1000 ; i++ ){
        dq1->push_left(1);
        // dq1->display();
    }
    cout << "Size=" << dq1->size() << endl ;

    // The destructor should delete all the nodes.
    delete dq1 ;

    cout << "\n\nDeque Class Test Program 6 - DONE\n\n";
    return 0;
}
