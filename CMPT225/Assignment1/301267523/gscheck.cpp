#include "char_stack.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;


int main(){
	char_stack S;
	string line;
	char index;
	int line_count=0;
	int char_count;
	int tab_index;
	string line1;
	string line2;
	int errornum=0;
	while (getline(cin,line)){    //while loop to get input line by line
		char_count = 0;
		line_count += 1;
		while (line[char_count]){   // while loop to identify the position of current charactor
			index = line[char_count];
			char_count += 1;
			if (index == '(' or index == '{' or index == '['){             // opening symbol check
				S.push(index);                                             // push opening symbol to stack
			} else if (index == ')' or index == '}' or index == ']'){      // closing symbol check
				if (S.empty()){	
					tab_index = line.find('\t');							// check if there is a closing symbol without a opening symbol ahead
					if (tab_index != string::npos){
						if (tab_index < char_count){
							line1 = line.substr(0,char_count);					   
							line2 = line.replace(0,tab_index,tab_index,' ');
							line2 = line2.replace(tab_index+1,char_count, char_count-1-tab_index,' ');
							errornum += 1;
							cout<< "Error on line " << line_count << ": Too many " << index << " and halt" << endl;
							cout << line1 << endl << line2 << endl;
						}else {
							line1 = line.substr(0,char_count);					   
							line2 = line.replace(0,char_count,char_count,' ');
							errornum += 1;
							cout<< "Error on line " << line_count << ": Too many " << index << " and halt" << endl;
							cout << line1 << endl << line2 << endl;
						}
					} else{
						line1 = line.substr(0,char_count);					   
						line2 = line.replace(0,char_count,char_count,' ');
						errornum += 1;
						cout<< "Error on line " << line_count << ": Too many " << index << " and halt" << endl;
						cout << line1 << endl << line2 << endl;
					}
					break;
				} else {
					char test = S.top();
					if ((test == '(' and index == ')') or (test == '{' and index =='}')   // check if the symbols match correctly
						or (test == '[' and index == ']') ){
						S.pop();
					} else {
						char expected;
						if (test == '('){
							expected = ')';
						} else if (test == '{'){
							expected = '}';
						} else if (test == '['){
							expected = ']';
						}
						tab_index = line.find('\t');							// check if there is a closing symbol without a opening symbol ahead
						if (tab_index != string::npos){
							if (tab_index < char_count){
								line1 = line.substr(0,char_count);					   
								line2 = line.replace(0,tab_index,tab_index,' ');
								line2 = line2.replace(tab_index+1,char_count, char_count-tab_index,' ');
								errornum += 1;
								cout<< "Error on line " << line_count <<": Read " << index << ", expected "  // identify the position of error
								<< expected << "." << endl;
								cout << line1 << endl << line2 << endl;
							}else {
								line1 = line.substr(0,char_count);					   
								line2 = line.replace(0,char_count,char_count,' ');
								errornum += 1;
								cout<< "Error on line " << line_count <<": Read " << index << ", expected "  // identify the position of error
								<< expected << "." << endl;
								cout << line1 << endl << line2 << endl;
							}
						} else{
							line1 = line.substr(0,char_count);					   
							line2 = line.replace(0,char_count,char_count,' ');
							errornum += 1;
							cout<< "Error on line " << line_count <<": Read " << index << ", expected "  // identify the position of error
								<< expected << "." << endl;
								cout << line1 << endl << line2 << endl;
						}
						break;
					}

				}
			}
		}
		if (errornum == 1){
			break;
		}
	}
	if ((S.size() != 0) and errornum != 1){    // check if there are too many opening symbol
		errornum += 1;
		cout<< "Error on line " << line_count << ": Too many " << S.top() << endl;
	}
	if (errornum == 0){    //no error check
		cout << "No Errors Found!\n";  
	}
}