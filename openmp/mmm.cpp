/*OPEN MP Matrix Multiplication*/
mmm(int threads, int length, double *ma, double *mb, double *mc);

#include <omp.h>
void mmm(int threads, int length, double *ma, double *mb, double *mc){
    //Set number of threads to use
    omp_set_num_threads(threads);

    int i, j, k
    #pragma omp parallel shared(length) private(i, j, k)
    {
        for(i = 0; i < length; i++){
            for(j = 0; j < length; j++){
                *(mc+(i*length+j)) = 0.0;
                for(k = 0; k < length; k++){
                    *(mc+(i*length+j)) = *(mc+(i*length+j)) + *(ma+(i*length+k)) * *(mb+(k*length+j));
                }
            }
        }
    }
}
