#Top level Makefile

include Makefile.inc

all : driver pthreads openmp serial lbstime

driver: driver.o serial lbstime pthreads openmp
	$(F90) driver.o -o driver $(MYLIBS) $(SYSLIBS)

driver.o: driver.f90
	$(F90) $(FFLAGS) driver.f90 -c

serial:
	cd serial && $(MAKE)

pthreads: 
	cd pthreads && $(MAKE)

openmp: 
	cd openmp && $(MAKE)

lbstime:
	cd lbstime && $(MAKE)

clean:
	cd serial && $(MAKE) clean
	cd lbstime && $(MAKE) clean
	cd openmp && $(MAKE) clean
	cd pthreads && $(MAKE) clean
	rm *.o
	touch *.f90

pristine: 
	cd serial && $(MAKE) pristine
	cd lbstime && $(MAKE) pristine
	cd pthreads && $(MAKE) pristine 
	cd openmp && $(MAKE) pristine  
	rm *.o	
	rm driver
	touch *.f90

.PHONY: serial openmp pthreads lbstime