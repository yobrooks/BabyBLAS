include ../Makefile.inc
# Pthread Makefile

all: lib

dot.o : dot.cpp
	$(CC) $(CFLAGS)  -c dot.cpp

mvv.o : mvv.cpp
	$(CC) $(CFLAGS)  -c mvv.cpp

mmm.o : mmm.cpp
	$(CC) $(CFLAGS)  -c mmm.cpp

vvm.o : vvm.cpp
	$(CC) $(CFLAGS)  -c vmm.cpp


lib: dot.o vvm.o mvv.o mmm.o 
	ar -rc libpthreads_bblas.a  mmm.o dot.o vvm.o mvv.o
	ranlib libpthreads_bblas.a

clean :
	rm *.o
	touch *.c

pristine:
	make clean
	rm *.a
