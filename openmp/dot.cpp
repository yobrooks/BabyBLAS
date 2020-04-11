#include <omp.h>
double dot(int threads, int length, double *a, double *b);

double dot(int threads, int length, double *a, double *b){
    omp_set_num_threads(threads);

    int i; double product = 0.0;
     #pragma omp parallel shared(length) private(i) reduction(+:product){
        for(i = 0; i < length; i++){
            product = product + *(a+i) * *(b+i);
        }   
    }
    return product;
}