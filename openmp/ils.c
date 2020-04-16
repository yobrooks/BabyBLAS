/*#ifdef __cplusplus
extern "C" {
#endif
    void ils_(int *threads, int *length, double *m, double *v, double *rv);
#ifdef __cplusplus
}
#endif

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void ils_(int *threads, int *length, double *m, double *v, double *rv){
    printf("Using OpenMP\n");
    int len = *length;
    int numThreads = *threads;

    omp_set_num_threads(numThreads);

    #pragma 
}*/