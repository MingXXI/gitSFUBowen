all: gscheck

gscheck: char_stack.o gscheck.o 
	g++ -o gscheck gscheck.o char_stack.o 

gscheck.o: gscheck.cpp char_stack.o char_stack.h
	g++ -c gscheck.cpp

char_stack.o: char_stack.cpp char_stack.h
	g++ -c char_stack.cpp

clean:
	rm -f gscheck *.o
