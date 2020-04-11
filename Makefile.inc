# Makefile variables

F90 = gfortran
CC = gcc
FFLAGS = -cpp -O2
CFLAGS = -O2 
MYLIBS = -L./serial -lserial_bblas
SYSLIBS = 