# Makefile variables

F90 = gfortran
CC = gcc -std=c99
FFLAGS = -cpp -O2 
CFLAGS = -g -fopenmp
MYLIBS = -L./serial -lserial_bblas -L./openmp -lopenmp_bblas -L./pthreads -lpthreads_bblas  -L./lbstime -llbstime
SYSLIBS = -lgomp -lpthread
