include ../Makefile.inc
# OpenMP Makefile

all: lib

dot.o : dot.c
	$(CC) $(CFLAGS)  -c dot.c

mvv.o : mvv.c
	$(CC) $(CFLAGS)  -c mvv.c

mmm.o : mmm.c
	$(CC) $(CFLAGS)  -c mmm.c

vvm.o : vvm.c
	$(CC) $(CFLAGS)  -c vvm.c

#ils.o : ils.c
#	$(CC) $(CFLAGS)  -c ils.c

#dls.o : dls.c
#	$(CC) $(CFLAGS)  -c dls.c

#MUST ADD LINEAR SOLVERS
lib: dot.o vvm.o mvv.o mmm.o 
	ar -rc libopenmp_bblas.a  mmm.o dot.o vvm.o mvv.o
	ranlib libopenmp_bblas.a

clean :
	rm *.o
	touch *.c

pristine:
	make clean
	rm *.a

