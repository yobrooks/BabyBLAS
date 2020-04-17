# Makefile variables

F90 = gfortran
CC = gcc -std=c99
FFLAGS = -cpp -O2 -DACCURACY_TEST -DLS_TEST -DITERATIVE -DDIAGDOM
CFLAGS = -g -fopenmp
MYLIBS = -L./openmp -lopenmp_bblas -L./serial -lserial_bblas  -L./pthreads -lpthreads_bblas  -L./lbstime -llbstime
SYSLIBS = -lgomp -lpthread
