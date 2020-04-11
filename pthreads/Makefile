include ../Makefile.inc
# Pthread Makefile

all: lib

dot.o : dot.cpp
	$(CC) $(CFLAGS)  -c dot.cpp

mvv.o : mvv.c
	$(CC) $(CFLAGS)  -c mvv.cpp

mmm.o : mmm.cpp
	$(CC) $(CFLAGS)  -c mmm.cpp

vvm.o : vvm.cpp
	$(CC) $(CFLAGS)  -c vmm.cpp

ils.o : ils.cpp
	$(CC) $(CFLAGS)  -c ils.cpp

dls.o : dls.cpp
	$(CC) $(CFLAGS)  -c dls.cpp

lib: dot.o ils.o dls.o vvm.o mvv.o mmm.o 
	ar -rc libpthreads_bblas.a  mmm.o dot.o ils.o dls.o vvm.o mvv.o
	ranlib libpthreads_bblas.a

clean :
	rm *.o
	touch *.c

pristine:
	make clean
	rm *.a
