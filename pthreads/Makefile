include ../Makefile.inc
# Pthread Makefile

all: lib

dot.o : dot.c
	$(CC) $(CFLAGS)  -c dot.c

mvv.o : mvv.c
	$(CC) $(CFLAGS)  -c mvv.c

mmm.o : mmm.c
	$(CC) $(CFLAGS)  -c mmm.c

vvm.o : vvm.c
	$(CC) $(CFLAGS)  -c vvm.c


lib: dot.o vvm.o mvv.o mmm.o 
	ar -rc libpthreads_bblas.a  mmm.o dot.o vvm.o mvv.o
	ranlib libpthreads_bblas.a

clean :
	rm *.o
	touch *.c

pristine:
	make clean
	rm *.a
