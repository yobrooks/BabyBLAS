/*OpenMP */
#ifdef _cplusplus
extern "C"{
#endif
void mvv_(int *threads, int *length, double *m, double *v, double *rv);
#ifdef _cplusplus
}
#endif

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void mvv_(int *threads, int *length, double *m, double *v, double *rv){
    printf("Using OpenMP\n");
     omp_set_num_threads(*threads);

    int i, j, len = *length;
    #pragma omp parallel shared(len) private(i, j)
    {
        for(i = 0; i < len; i++){
            *(rv+i) = 0.0;
            for(j = 0; j < len; j++){
                *(rv+i) = *(m +(len*i)+j) * *(v+j);
            }
        }   
    }
}