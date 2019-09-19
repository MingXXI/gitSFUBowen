
# compiler options
CFLAGS = -g -Wall
LIBS = -lm

default: echo "You must specify a target, e.g. t1, t2" 

t0:
	gcc $(CFLAGS) -o $@ test.c t0.c $(LIBS)

t1:
	gcc $(CFLAGS) -o $@ test.c t1.c $(LIBS)

t2:
	gcc $(CFLAGS) -o $@ test.c t2.c $(LIBS)

clean:
	/bin/rm -rf *.dSYM
	/bin/rm -f t0 t1 t2
	/bin/rm -f *.png
	/bin/rm -f *.dat
