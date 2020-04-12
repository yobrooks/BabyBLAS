/*OPEN MP Matrix Multiplication*/
#ifdef _cplusplus
extern "C"{
#endif
    void mmm_(int *threads, int *length, double *ma, double *mb, double *mc);
#ifdef _cplusplus
}
#endif

#include <omp.h>
#include <stdio.h>

void mmm_(int *threads, int *length, double *ma, double *mb, double *mc){
    //Set number of threads to use
    omp_set_num_threads(*threads);
    int len = *length;
    int i, j, k;
    //printf("ABOUT TO PARALLEL\n");
   //printf("LENGTH %i \n", length);
   // printf("THREADS %i \n", threads);
    #pragma omp parallel shared(len) private(i, j, k)
    {
        for(i = 0; i < len; i++){
            for(j = 0; j < len; j++){
                *(mc+(i*len+j)) = 0.0;
                for(k = 0; k < len; k++){
                    *(mc+(i*len+j)) = *(mc+(i*len+j)) + *(ma+(i*len+k)) * *(mb+(k*len+j));
                }
            }
        }
    }

    //printf("END PARALLEL\n");
}
