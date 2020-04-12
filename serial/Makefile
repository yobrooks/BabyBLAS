include ../Makefile.inc

all: lib

dot.o : dot.c
	$(CC) $(CFLAGS) -c dot.c

vvm.o : vvm.c
	$(CC) $(CFLAGS) -c vvm.c

mmm.o : mmm.c
	$(CC) $(CFLAGS) -c mmm.c

mvv.o : mvv.c
	$(CC) $(CFLAGS) -c mvv.c


lib: dot.o vvm.o mmm.o mvv.o
	ar -rc libserial_bblas.a dot.o vvm.o mmm.o  mvv.o
	ranlib libserial_bblas.a

clean : 
	rm *.o
	touch *.c

pristine: 
	make clean
	rm *.a