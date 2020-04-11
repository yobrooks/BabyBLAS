include ../Makefile.inc

all: lib

dot.o : dot.cpp
	$(CC) $(CFLAGS) -c dot.cpp

vvm.o : vvm.cpp
	$(CC) $(CFLAGS) -c vvm.cpp

mmm.o : mmm.cpp
	$(CC) $(CFLAGS) -c mmm.cpp

mvv.o : mvv.cpp
	$(CC) $(CFLAGS) -c mvv.cpp

ils.o : ils.cpp
	$(CC) $(CFLAGS) -c ils.cpp

dls.o : dls.cpp
	$(CC) $(CFLAGS) -c dls.cpp

lib: dot.o vvm.o mmm.o mvv.o ils.o dls.o
	ar -rc libserial_bblas.a dot.o vvm.o mmm.o  mvv.o ils.o dls.o
	ranlib libserial_bblas.a

clean : 
	rm *.o
	touch *.cpp

pristine: 
	make clean
	rm *.a