#ifdef __cplusplus
extern "C" {
#endif
void vvm_(int *threads, int *length, double *a, double *b, double *m);
#ifdef __cplusplus
}
#endif

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*Function Prototypes*/
void *vvm_thread_worker();

struct VVMargs{
    int N;
    int rowStart;
    int rowStop;
    double *aPtr;
    double *bPtr;
    double *mPtr;
};

void vvm_(int *threads, int *length, double *a, double *b, double *m){
    printf("Using PThreads\n");
    int len = *length;
    int numThreads = *threads;
    if(len < numThreads){
        for(int i = 0; i < len; i++){
            for(int j = 0; j < len; j++){
                *(m+(len*i+j)) = *(a+i) * *(b+j);
            }
        }
    }
    else{
        pthread_t *thread_id = (pthread_t *) malloc (numThreads * sizeof(pthread_t));
        int *numRows = (int *) malloc(numThreads * sizeof(int));
        struct VVMargs *thread_data;

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
            thread_data = (struct VVMargs*)malloc(sizeof(struct VVMargs));
            thread_data->rowStart = start;
            thread_data->rowStop = stop;
            thread_data->aPtr = a;
            thread_data->bPtr = b;
            thread_data->mPtr = m;
            thread_data->N = len;

            pthread_create(thread_id+i, NULL, &vvm_thread_worker, thread_data);
        }

        for(int i=0; i < numThreads ; i++) {
            pthread_join(*(thread_id+i), NULL); 
        }

        free(numRows);
        free(thread_id);
    }
}

void *vvm_thread_worker(struct VVMargs *thread_args){
    int N =  thread_args->N;
    int start = thread_args->rowStart;
    int stop  = thread_args->rowStop; 
    double *A = thread_args->aPtr;
    double *B = thread_args->bPtr;
    double *M = thread_args->mPtr;

    for(int i = start; i < stop; i++){
        for(int j = 0; j < N; j++){
            *(M+(N*i)+j) = *(A+i) * *(B+j);
        }
    }
    
    free(thread_args);
    pthread_exit(NULL);
}
