#Top level Makefile

include Makefile.inc

#MUST ADD PTHREADS
all : driver serial openmp lbstime

driver: driver.o serial lbstime openmp
	$(F90) driver.o -o driver $(MYLIBS) $(SYSLIBS)

driver.o: driver.f90
	$(F90) $(FFLAGS) driver.f90 -c

serial:
	cd serial && $(MAKE)

openmp:
	cd openmp && $(MAKE)

lbstime:
	cd lbstime && $(MAKE)

clean:
	cd serial && $(MAKE) clean
	cd openmp && $(MAKE) clean
	cd lbstime && $(MAKE) clean
	rm *.o
	touch *.f90

pristine: 
	cd serial && $(MAKE) pristine
	cd openmp && $(MAKE) pristine
	cd lbstime && $(MAKE) pristine 
	rm *.o	
	rm driver
	touch *.f90

.PHONY: serial openmp lbstime