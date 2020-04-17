#Top level Makefile

include Makefile.inc

#MUST ADD PTHREADS
all : poundsdriver pthreads openmp serial lbstime

poundsdriver: poundsdriver.o serial lbstime pthreads openmp
	$(F90) poundsdriver.o -o poundsdriver $(MYLIBS) $(SYSLIBS)

poundsdriver.o: poundsdriver.f90
	$(F90) $(FFLAGS) poundsdriver.f90 -c

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
	rm poundsdriver
	touch *.f90

.PHONY: serial openmp pthreads lbstime