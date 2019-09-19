# Makefile for building multi-file application

# final executable to build:
TARGET= candykids
# .o files to link in (for all .c files)
# OBJS = candykids.o bbuff.o stats.o

# Add support for pthread and real-time clock here:
CFLAGS = -g -std=c99 -Wall -Werror -D_POSIX_C_SOURCE=199309L -lrt -pthread 



CC_C = gcc

all: clean $(TARGET)

%.o : %.c
	$(CC) -c $(CFLAGS) $<


$(TARGET): 
	$(CC_C) $(CFLAGS) candykids.c bbuff.c stats.c -o $@

clean:
	rm -f $(TARGET)
	rm -f %.o









