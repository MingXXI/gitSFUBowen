CC=cc
CXX=CC
CCFLAGS= -g -std=c99 -Wall -Werror

all: test_list test

# Compile all .c files into .o files
# % matches all (like * in a command)
# $< is the source file (.c file)
%.o : %.c
	$(CC) -c $(CCFLAGS) $<



# Build test_list if necessary
test_list: list.o test_list.o
	$(CC) -o test_list list.o test_list.o

test: test_list
	./test_list


clean:
	rm -f core *.o test_list
