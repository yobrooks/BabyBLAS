#ifdef __cplusplus
extern "C" {
#endif
double dot_(int *threads, int *length, double *a, double *b);
#ifdef __cplusplus
}
#endif

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*Function Prototypes*/
void *dot_thread_worker();

/*Struct For Thread Data*/
struct DOTargs{
    int rowStart;
    int rowStop;
    int threadNum;
    double *aPtr;
    double *bPtr;
    double *threadResultPtr;
};

double dot_(int *threads, int *length, double *a, double *b){
    int numThreads = *threads;
    int len = *length;
    double product = 0.0;
    if(len < numThreads){
      for(int i = 0; i < len; i++){
          product = product + a[i] * b[i]; 
      }
    }
    else{
        pthread_t *thread_id = (pthread_t *) malloc (numThreads * sizeof(pthread_t));
        int *numRows = (int *) malloc(numThreads * sizeof(int));
        double *thread_results = (double*)calloc(numThreads, sizeof(double));
        struct DOTargs *thread_data;

        for (int i=0; i<numThreads; i++){
            *(numRows+i) = len/numThreads;
        }
        for (int i=0; i< len % numThreads; i++){
            *(numRows+i) = *(numRows+i)+1;
        }

        int stop = 0; int start;
        for(int i = 0; i < numThreads; i++){
            start = stop;
            stop = start + *(numRows+i);
            thread_data = (struct DOTargs*)malloc(sizeof(struct DOTargs));
            thread_data->rowStart = start;
            thread_data->rowStop = stop;
            thread_data->aPtr = a;
            thread_data->bPtr = b;
            thread_data->threadNum = i;
            thread_data->threadResultPtr = thread_results;

            pthread_create(thread_id+i, NULL, &dot_thread_worker, thread_data);
        }

        //add all the results from the threads to get the final dot product
        for(int i=0; i < numThreads ; i++) {
            pthread_join(*(thread_id+i), NULL); 
            product = product + *(thread_results+i);
        }

        free(numRows);
        free(thread_id);
    }
    return product;
}

void *dot_thread_worker(struct DOTargs *thread_args){
    double *A, *B, tempDot = 0.0;
    int start = thread_args->rowStart;
    int stop = thread_args->rowStop;
    A = thread_args->aPtr;
    B = thread_args->bPtr;
    double *myresults = thread_args->threadResultPtr;

    //find the dot product for this particular thread
    for(int i = start; i < sstop; i++){
        tempDot = tempDot + *(A+i)* *(B+i);
    }

    *(myresults+thread_args->threadNum) = tempDot;
    free(thread_args);
    pthread_exit(NULL);
}
