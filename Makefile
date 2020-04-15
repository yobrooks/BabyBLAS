#Top level Makefile

include Makefile.inc

#MUST ADD PTHREADS
all : testdriver serial lbstime

testdriver: testdriver.o serial lbstime
	$(F90) testdriver.o -o testdriver $(MYLIBS) $(SYSLIBS)

testdriver.o: testdriver.f90
	$(F90) $(FFLAGS) testdriver.f90 -c

serial:
	cd serial && $(MAKE)

lbstime:
	cd lbstime && $(MAKE)

clean:
	cd serial && $(MAKE) clean
	cd lbstime && $(MAKE) clean
	rm *.o
	touch *.f90

pristine: 
	cd serial && $(MAKE) pristine
	cd lbstime && $(MAKE) pristine 
	rm *.o	
	rm testdriver
	touch *.f90

.PHONY: serial lbstime