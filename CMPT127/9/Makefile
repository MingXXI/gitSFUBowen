# Makefiles help manage the compilation process.  To use this
# Makefile, run 'make' in the directory containing this file.

# compiler options
CFLAGS = -g 
LDFLAGS += -lm -lglut -lGL

# need these flags on OSX
#CFLAGS += -I/usr/local/include
#LDFLAGS += -L/usr/local/lib -lglut -framework OpenGL

SRC = roids.c brightcolor.c gui.c

all: roids

roids:  $(SRC)
	gcc  $(CFLAGS) $(SRC) -o roids $(LDFLAGS)

clean:
	rm -f  roids *.o
