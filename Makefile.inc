# Makefile variables

F90 = gfortran
CC = gcc -std=c99
FFLAGS = -cpp -O2 -DACCURACY_TEST
CFLAGS = -g
MYLIBS = -L./pthreads -lpthreads_bblas -L./serial -lserial_bblas -L./lbstime -llbstime
SYSLIBS = -lpthread