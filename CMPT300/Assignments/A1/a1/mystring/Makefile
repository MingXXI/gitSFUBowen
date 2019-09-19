## This is a simple Makefile with lost of comments 
## Check Unix Programming Tools handout for more info.

# Define what compiler to use and the flags.
CC=cc
CXX=CC
CCFLAGS= -g -std=c99 -Wall -Werror

# A rule in Makefile has the form:
#
# target: dependencies
#	command
#
# where "target" and "dependencies" are files (most of the time).
# These means that if "target" does not exist or the modification 
# date of the dependencies are older than the modification time of
# "target" then "command" is executed.
#
# For example, the rule 
#
# mystring.o : mystring.c
#	$(CC) -c $(CCFLAGS) mystring.c
#
# means that if mystring.o does not exist, or if mystring.c is older
# than mystring.o, then execute "$(CC) -c $(CCFLAGS) mystring.c".
#
# The goal of make is to execute the minimum set of commands that
# are necessary to build the target files. i.e., it does not rebuild
# files that it expects need not be rebuilt because they have not changed.
#
# Usually, the first target in a Makefile is called "all". 
# The dependencies of "all" are the files (or make targets) that we want to build.
#

all: test_mystring test

# Compile all .c files into .o files
# % matches all (like * in a command)
# $< is the source file (.c file)
%.o : %.c
	$(CC) -c $(CCFLAGS) $<



# Build test_mystring if necessary
test_mystring: mystring.o test_mystring.o
	$(CC) -o test_mystring mystring.o test_mystring.o

test: test_mystring
	./test_mystring


clean:
	rm -f core *.o test_mystring

