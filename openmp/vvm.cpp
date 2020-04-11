/* Open MP */
#include <omp.h>
void vvm(int threads, int length, double *a, double *b, double *m);

void vvm(int threads, int length, double *a, double *b, double *m){
    omp_set_num_threads(threads);

    int i, j;
    #pragma omp parallel shared(length) private(i, j)
    for(i = 0; i < length; i++){
        for(j = 0; j < length; j++){
            *(m+(length*i+j)) = *(a+i) * *(b+j);
        }
    }
}