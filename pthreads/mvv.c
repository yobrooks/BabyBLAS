/* Matrix Vector Multiplication --> resultant Vector */
#ifdef __cplusplus
extern "C" {
#endif
void mvv_(int *threads, int *length, double *m, double *v, double *rv);
#ifdef __cplusplus
}
#endif

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
/* Function Prototypes*/
void singleMVV(int *length, double *m, double *v, double *rv);
void *mvv_thread_worker();

/*Struct for Thread Data*/
struct MVVargs{
    int N;
    int rowStart;
    int rowStop;
    double *mPtr;
    double *vPtr;
    double *rvPtr;
};

void mvv_(int *threads, int *length, double *m, double *v, double *rv){
    printf("Using PThreads\n");
    if(*length < *threads){
        singleMVV(length, m, v, rv);
    }else{
        int len = *length;
        int numThreads = *threads;
        pthread_t *thread_id = (pthread_t*)malloc(numThreads * sizeof(pthread_t)); 
        int *numRows = (int*)malloc(numThreads * sizeof(int));
        struct MVVargs *thread_data;
        for(int i=0; i<numThreads; i++){
            *(numRows+i) = len/numThreads;
        }

        for(int i=0; i<(len%numThreads); i++){
            *(numRows+i) = *(numRows+i)+1;
        }

        int startRow, stopRow = 0;
        for(int i = 0; i < numThreads; i++){
            startRow = stopRow;
            stopRow = startRow+*(numRows+i);
            thread_data = (struct MVVargs*)malloc(sizeof(struct MVVargs));
            thread_data->N = len;
            thread_data->rowStart = startRow;
            thread_data->rowStop = stopRow;
            thread_data->mPtr = m;
            thread_data->vPtr = v;
            thread_data->rvPtr = rv;

            pthread_create(thread_id+i, NULL, &mvv_thread_worker, thread_data);
        }
        for(int i = 0; i < numThreads; i++){
            pthread_join(*(thread_id+i), NULL);
        }

        free(numRows);
        free(thread_id);
    }
}

    void singleMVV(int *length, double *m, double *v, double *rv){
        int len = *length;
        for(int i = 0; i < len; i++){
            *(rv+i) = 0.0;
            for(int j = 0; j < len; j++){
                *(rv+i)  = *(m+(i*len+j)) + *(v+j);
            }
        }
    }

    void *mvv_thread_worker(struct MVVargs *thread_args){
        double *M, *V, *RV;
        //int rowStart = thread_args->rowStart;
       // int rowStop = thread_args->rowStop;
        M = thread_args->mPtr; V = thread_args->vPtr; RV = thread_args->rvPtr;

        for(int i = thread_args->rowStart; i < thread_args->rowStop; i++){
            *(RV+i) = 0.0;
            for(int j = 0; j < thread_args->N; j++){
                *(RV+i)  = *(M+(i*thread_args->N+j)) + *(V+j);
            }
        }
        free(thread_args);
        pthread_exit(NULL);
    }
