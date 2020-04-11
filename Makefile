#Top level Makefile

include Makefile.inc

all : driver serial

driver: driver.o serial
	$(F90) driver.o -o driver $(MYLIBS) $(SYSLIBS)

driver.o: driver.f90
	$(F90) $(FFLAGS) driver.f90 -c

serial:
	cd serial && $(MAKE)

clean:
	cd serial && $(MAKE) clean
	rm *.o
	touch *.f90

pristine: 
	cd serial && $(MAKE) pristine 
	rm *.o	
	rm driver
	touch *.f90