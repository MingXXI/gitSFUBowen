CC=gcc
CXX=g++
CCFLAGS= -g -std=c99 -D _GNU_SOURCE -static 

SRC1 = test_process_ancestors.c 
SRC2 = test_array_stats.c

%.o : %.c
	$(CC) -c $(CCFLAGS) $<

test_execute: $(SRC1) $(SRC2)
	$(CC) -o test_process_ancestors $(CCFLAGS) $(SRC1)
	$(CC) -o test_array_stats $(CCFLAGS) $(SRC2) 

transfer:
	scp -P 2222 test_process_ancestors test_array_stats root@localhost:~

clean:
	rm -f test_process_ancestors test_array_stats *.o
