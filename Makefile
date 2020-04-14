#Top level Makefile

include Makefile.inc

#MUST ADD PTHREADS
all : driver serial lbstime

driver: driver.o serial lbstime
	$(F90) driver.o -o driver $(MYLIBS) $(SYSLIBS)

driver.o: driver.f90
	$(F90) $(FFLAGS) driver.f90 -c

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
	rm driver
	touch *.f90

.PHONY: serial lbstime