#include "Deque.cpp"
#include <iostream>
using namespace std;

int main(){
	cout << "Begin" << endl;
	Deque test;
	cout << "deque has been assigned" << endl;
	test.push_left(1);
	cout << "1st push done" << endl;
	test.push_right(2);
	cout << "2nd push done" << endl;
	test.push_right(3);
	cout << "3rd push done" << endl;
	test.push_left(0);
	cout << "4th push done" << endl;
	test.push_left(0);
	test.push_left(0);
	test.push_left(0);
	test.push_left(0);
	test.display();
	cout << "display done" << endl;
	test.verbose_display();
	cout << "verbose display done" << endl;
	test.set_cursor(9);
	test.display();
	Deque  test2(test);
	test2.verbose_display();
	test.~Deque();
	test2.verbose_display();
	test2.set_cursor(11);
	test.display();
	test2.display();
	return 0;
} 