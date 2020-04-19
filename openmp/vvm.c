/* Open MP */
#ifdef _cplusplus
extern "C"{
#endif
void vvm_(int *threads, int *length, double *a, double *b, double *m);
#ifdef _cplusplus
}
#endif

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void vvm_(int *threads, int *length, double *a, double *b, double *m){
    printf("Using OpenMP\n");
    omp_set_num_threads(*threads);

    int i, j, len = *length;
    #pragma omp parallel shared(len) private(i, j)
    for(i = 0; i < len; i++){
        for(j = 0; j < len; j++){
            *(m+(len*i+j)) = *(a+i) * *(b+j);
        }
    }
}