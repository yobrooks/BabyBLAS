/*OpenMP */
void mvv(int threads, int length, double *m, double *v, double *rv);

#include <omp.h>

void mvv(int threads, int length, double *m, double *v, double *rv){
    
     omp_set_num_threads(threads);

    int i, j;
    #pragma omp parallel shared(length) private(i, j)
    {
        for(i = 0; i < length; i++){
            *(rv+i) = 0.0;
            for(j = 0; j < length; j++){
                *(rv+i)  = *(rv+i) + *(m+(i*length+j)) + *(v+j);
            }
        }   
    }
}