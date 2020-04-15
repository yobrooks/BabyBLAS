# Makefile variables

F90 = gfortran
CC = gcc -std=c99
FFLAGS = -cpp -O2 -DACCURACY_TEST -DLS_TEST -DITERATIVE -DDIAGDOM
CFLAGS = -g
MYLIBS = -L./serial -lserial_bblas -L./lbstime -llbstime
SYSLIBS = 
