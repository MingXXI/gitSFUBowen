#include <iostream> // I/O library.
#include <algorithm> // Includes sort()
#include <ctime> // access to the system clock
#include <time.h> // access to "wall clock"
#include "btree_set.h" 
using namespace std;

double elapsed_time( clock_t start, clock_t finish){
     // returns elapsed time in milliseconds
    return (finish - start)/(double)(CLOCKS_PER_SEC/1000);
}

int main (int argc, char * const argv[]) {

  	int SIZE; // size of array to work on.
  	int TIMES = 10; // number of times to run - mean is reported.

  	srand( time(NULL)); // seed the random number generator.

  	clock_t start, finish; // used to time function calls.

  	cout<< "\nBtree_set Insert Time Test When N=2000 Start!"<<endl;
  	double insert_time = 0;
    btree::btree_set<int,std::less<int>,std::allocator<int>,64> S1 ;
  	SIZE = 2000;
 	for( int t = 0 ; t < TIMES ; t++ ){
    
  	for(int i = 0 ; i < SIZE ; i++ ){
   	   	 	int x = rand() % SIZE*10;
   	     	start = clock();
    	    S1.insert(x);
        	finish = clock();
    	    insert_time += elapsed_time(start,finish);
  	 }
  }
  cout << "The number of nodes in the Btree is: " << S1.nodes() <<endl;
  cout << "the height of the Btree is: "<< S1.height() << endl;
  cout << "The average bytes per value is: "<< S1.average_bytes_per_value() << endl;
	cout << "Inserting Time When N=2000: "<< insert_time/TIMES << endl;

	cout<< "\nBtree_set Insert Time Test When N=4000 Start!"<<endl;
  	insert_time = 0;
    btree::btree_set<int,std::less<int>,std::allocator<int>,64> S2 ;
  	
  	SIZE = 4000;
 	for( int t = 0 ; t < TIMES ; t++ ){
    
  	for(int i = 0 ; i < SIZE ; i++ ){
   	   	 	int x = rand() % SIZE*10;
   	     	start = clock();
    	    S2.insert(x);
        	finish = clock();
    	    insert_time += elapsed_time(start,finish);
  	 	}
  	}
  cout << "The number of nodes in the Btree is: " << S2.nodes() <<endl;
  cout << "the height of the Btree is: "<< S2.height() << endl;
  cout << "The average bytes per value is: "<< S2.average_bytes_per_value() << endl;
	cout << "Inserting Time When N=4000: "<< insert_time/TIMES << endl;

	cout<< "\nBtree_set Insert Time Test When N=6000 Start!"<<endl;
  	insert_time = 0;
    
  	btree::btree_set<int,std::less<int>,std::allocator<int>,64> S3 ;

  	SIZE = 6000;
 	for( int t = 0 ; t < TIMES ; t++ ){
  	  	for(int i = 0 ; i < SIZE ; i++ ){
   	   	 	int x = rand() % SIZE*10;
   	     	start = clock();
    	    S3.insert(x);
        	finish = clock();
    	    insert_time += elapsed_time(start,finish);
  	 	}
  	}
  cout << "The number of nodes in the Btree is: " << S3.nodes() <<endl;
  cout << "the height of the Btree is: "<< S3.height() << endl;
  cout << "The average bytes per value is: "<< S3.average_bytes_per_value() << endl;
	cout << "Inserting Time When N=6000: "<< insert_time/TIMES << endl;

	cout<< "\nBtree_set Insert Time Test When N=8000 Start!"<<endl;
  	insert_time = 0;
    
  	btree::btree_set<int,std::less<int>,std::allocator<int>,64> S4 ;

  	SIZE = 8000;
 	for( int t = 0 ; t < TIMES ; t++ ){
  	  	for(int i = 0 ; i < SIZE ; i++ ){
   	   	 	int x = rand() % SIZE*10;
   	     	start = clock();
    	    S4.insert(x);
        	finish = clock();
    	    insert_time += elapsed_time(start,finish);
  	 	}
  	}
  cout << "The number of nodes in the Btree is: " << S4.nodes() <<endl;
  cout << "the height of the Btree is: "<< S4.height() << endl;
  cout << "The average bytes per value is: "<< S4.average_bytes_per_value() << endl;
	cout << "Inserting Time When N=8000: "<< insert_time/TIMES << endl;

		cout<< "\nBtree_set Insert Time Test When N=10000 Start!"<<endl;
  	insert_time = 0;
    
  	btree::btree_set<int,std::less<int>,std::allocator<int>,64> S5 ;

  	SIZE = 10000;
 	for( int t = 0 ; t < TIMES ; t++ ){
  	  	for(int i = 0 ; i < SIZE ; i++ ){
   	   	 	int x = rand() % SIZE*10;
   	     	start = clock();
    	    S5.insert(x);
        	finish = clock();
    	    insert_time += elapsed_time(start,finish);
  	 	}
  	}
  cout << "The number of nodes in the Btree is: " << S5.nodes() <<endl;
  cout << "the height of the Btree is: "<< S5.height() << endl;
  cout << "The average bytes per value is: "<< S5.average_bytes_per_value() << endl;
	cout << "Inserting Time When N=10000: "<< insert_time/TIMES << endl;

	return 0;
}