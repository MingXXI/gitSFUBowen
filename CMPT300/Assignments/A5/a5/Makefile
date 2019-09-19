TARGET = myalloc
OBJS = main.o myalloc.o list.o

CFLAGS = -Wall -g -std=c99 -D_POSIX_C_SOURCE=199309L -lrt -pthread
CC = gcc

all: clean $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
