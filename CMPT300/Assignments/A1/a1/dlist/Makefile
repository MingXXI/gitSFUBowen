CC=cc
CXX=CC
CCFLAGS= -g -std=c99 -Wall -Werror

all: test_dlist test

# Compile all .c files into .o files
# % matches all (like * in a command)
# $< is the source file (.c file)
%.o : %.c
	$(CC) -c $(CCFLAGS) $<



# Build test_dlist if necessary
test_dlist: dlist.o test_dlist.o
	$(CC) -o test_dlist dlist.o test_dlist.o

test: test_dlist
	./test_dlist


clean:
	rm -f core *.o test_dlist
