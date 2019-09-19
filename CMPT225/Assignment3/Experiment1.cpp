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

  int SIZE = 2000; // size of array to work on.
  int TIMES = 10; // number of times to run - mean is reported.

  srand( time(NULL)); // seed the random number generator.

  clock_t start, finish; // used to time function calls.

  cout<< "\n\nBtree_set Insert Time Test on Size 16 Start!"<<endl;
  double insert_time = 0;
    
  btree::btree_set<int,std::less<int>,std::allocator<int>,16> S1 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S1.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 16: "<< insert_time/TIMES << endl;

cout<< "\n\nBtree_set Insert Time Test on Size 32 Start!"<<endl;
  insert_time = 0;
    
  btree::btree_set<int,std::less<int>,std::allocator<int>,32> S2 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S2.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 32: "<< insert_time/TIMES << endl;

cout<< "\n\nBtree_set Insert Time Test on Size 64 Start!"<<endl;
  insert_time = 0;
    
  btree::btree_set<int,std::less<int>,std::allocator<int>,64> S3 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S3.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 64: "<< insert_time/TIMES << endl;


cout<< "\n\nBtree_set Insert Time Test on Size 128 Start!"<<endl;
  insert_time = 0;
    
  btree::btree_set<int,std::less<int>,std::allocator<int>,128> S4 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S4.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 128: "<< insert_time/TIMES << endl;


cout<< "\n\nBtree_set Insert Time Test on Size 256 Start!"<<endl;
  insert_time = 0;
    
  btree::btree_set<int,std::less<int>,std::allocator<int>,256> S5 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S5.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 256: "<< insert_time/TIMES << endl;

cout<< "\n\nBtree_set Insert Time Test on Size 512 Start!"<<endl;
  insert_time = 0;
    
btree::btree_set<int,std::less<int>,std::allocator<int>,512> S6 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S6.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 512: "<< insert_time/TIMES << endl;

cout<< "\n\nBtree_set Insert Time Test on Size 1024 Start!"<<endl;
  insert_time = 0;
    
btree::btree_set<int,std::less<int>,std::allocator<int>,1024> S7 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S7.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 1024: "<< insert_time/TIMES << endl;

cout<< "\n\nBtree_set Insert Time Test on Size 2048 Start!"<<endl;
  insert_time = 0;
    
btree::btree_set<int,std::less<int>,std::allocator<int>,2048> S8 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S8.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 2048: "<< insert_time/TIMES << endl;

cout<< "\n\nBtree_set Insert Time Test on Size 4096 Start!"<<endl;
  insert_time = 0;
    
btree::btree_set<int,std::less<int>,std::allocator<int>,4096> S9 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S9.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 4096: "<< insert_time/TIMES << endl;

cout<< "\n\nBtree_set Insert Time Test on Size 8192 Start!"<<endl;
  insert_time = 0;
btree::btree_set<int,std::less<int>,std::allocator<int>,8192> S10 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S10.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 8192: "<< insert_time/TIMES << endl;

cout<< "\n\nBtree_set Insert Time Test on Size 16384 Start!"<<endl;
  insert_time = 0;
btree::btree_set<int,std::less<int>,std::allocator<int>,16384> S11 ;
    
  for( int t = 0 ; t < TIMES ; t++ ){
    for(int i = 0 ; i < SIZE ; i++ ){
        int x = rand() % SIZE*10;
        start = clock();
        S11.insert(x);
        finish = clock();
        insert_time += elapsed_time(start,finish);
    }
  }
cout << "Inserting Time on Size 16384: "<< insert_time/TIMES << endl;


	cout << "\n\nbtree_set Class Time Test - DONE\n\n";

	return 0;
}