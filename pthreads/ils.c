/*#ifdef __cplusplus
extern "C" {
#endif
    void ils_(int *threads, int *length,  double *m, double *v, double *rv);
#ifdef __cplusplus
}
#endif

#include <stdio.h>  
#include <stdlib.h>
#include <pthread.h>

/* Prototypes */
/*int zerosInDiag(int N, double *a);
int converged(int N, double *a, double *b);
void *ils_worker();

struct ILSargs{
    
};

void ils_(int *threads, int *length, double *m, double *v, double *rv){
    int len = *length;
    int ITERATION_MAX = 2000;

    if(!zerosInDiag(len, m)){
        //Do Jacobi Iterative Method
        double *x0 = malloc(len*sizeof(double)); //create temp vector for initial values
        //fill the result vector rv with initial values of 0
        //fill x0 vector with values of vector v
        for(int i = 0; i < len; i++){
            *(rv+i) = 0.0;
            *(x0+i) = *(v+i);
        }

        ITERATION_MAX = fmax(ITERATION_MAX, len/3);

        /* Set up Pthreads Parallelization */
        /*int numThreads = *threads;
        pthread_t* mythread = (pthread_t*) malloc(numThreads*sizeof(pthread_t));
        int *numRows = (int*)malloc(numThreads*sizeof(int));
        struct ILSargs* thread_data;
        int start, stop;
        
        for(int i = 0; i < numThreads; i++){
            *(numRows)
        }
    }
}*/