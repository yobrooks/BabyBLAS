#ifdef __cplusplus
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
int zerosInDiag(int N, double *a);
int converged(int N, double *a, double *b);
void *ils_worker();

struct ILSargs{
    int N;
    double *aPtr;
    double *bPtr;
    double *rvPtr;
    double *x0Ptr;
    int rowStart;
    int rowStop;
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
        int numThreads = *threads;
        pthread_t* mythread = (pthread_t*) malloc(numThreads*sizeof(pthread_t));
        int *numRows = (int*)malloc(numThreads*sizeof(int));
        struct ILSargs* thread_data;
        
        for(int i = 0; i < numThreads; i++){
            *(numRows+i) = len/numThreads;
        }
        for(int i = 0; i < len%numTheads; i++){
            *(numRows+i) = *(numRows+i) + 1;
        }

        int stop, start, iteration = 0;
        while(!converged(len, rv, x0) && iteration < ITERATION_MAX){
            for(int i = 0; i < len; i++){
                *(x0+i) = *(rv+i);
            }
            start = 0;
            stop = 0;
            //let parallel do the reduction work
            for(int i = 0; i < numThreads; i++){
                thread_data = (struct ILSargs*)malloc(sizeof(struct ILSargs));
                start = stop;
                stop = start + *(numRows+i);
                thread_data->N = len;
                thread_data->aPtr = m;
                thread_data->bPtr = v;
                thread_data->rvPtr = rv;
                thread_data->x0Ptr = x0;
                thread_data->rowStart = start;
                thread_data->rowStop = stop;
                pthread_create(mythread+i, NULL, &ils_thread_worker, thread_data);
            }

            for(int i = 0; i < numThreads; i++){
                pthread_join(*(mythread+i), NULL);
            }
            iteration++;
        }

        free(x0);
        free(mythread);
        free(numRows);

        if(iteration == ITERATION_MAX){
            printf(" *** ITERATIVE SOLVER FAILED TO REACH CONVERGENCE AFTER  ***\n");
        }
    }
    else{
        printf(" *** FOUND A ZERO ELEMENT ALONG MATRIX DIAGONAL ***\n");
    }
}

void ils_thread_worker(struct ILSargs *thread_args){
    //unpack data for thread
    double *a = thread_args->aPtr;
    double *b = thread_args->bPtr;
    double *rv = thread_args->rvPtr;
    double *x0 = thread_args->x0Ptr;
    int start = thread_args->rowStart;
    int stop = thread_data->rowStop;
    int N = thread_args->N;


    for(int i = start; i < stop; i++){
        
    }
}