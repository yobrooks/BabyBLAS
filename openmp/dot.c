#ifdef _cplusplus
extern "C"{
#endif
double dot_(int *threads, int *length, double *a, double *b);
#ifdef _cplusplus
}
#endif

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
double dot_(int *threads, int *length, double *a, double *b){
    printf("Using OpenMP\n");
    omp_set_num_threads(*threads);

    int len = *length;
    int i; double product = 0.0;
    #pragma omp parallel for schedule(static) private(i) reduction(+:product)
            for(i = 0; i < len; i++){
                product = product + *(a+i) * *(b+i);
            } 
    return product;  
}