/* Matrix Vector Multiplication --> resultant Vector */
#include <pthread.h>
void mvv(int threads, int length, double *m, double *v, double *rv);

/* Function Prototypes*/
void singleMVV(int length, double *m, double *v, double *rv);
void *mvv_thread_worker(MVVargs *thread_args);
/*Struct for Thread Data*/
struct MVVargs{
    int N;
    int rowStart;
    int rowStop;
    double *mPtr;
    double *vPtr;
    double *rvPtr;
};

void mvv(int threads, int length, double *m, double *v, double *rv){
    if(length < threads){
        singleMVV(length, m, v, rv);
    }else{
        pthread_t *thread_id = new pthread_t[threads];
        int *numRows = new int[threads];
        MVVargs *thread_data;
        for(int i=0; i<threads; i++){
            *(numRows+i) = length/threads;
        }

        for(int i=0; i<(length%threads); i++){
            *(numRows+i) = *(numRows+i)+1;
        }

        int startRow, stopRow = 0;
        for(int i = 0; i < threads; i++){
            startRow = stopRow;
            stopRow = startRow+*(numRows+i);
            thread_data = new MVVargs;
            thread_data->N = length;
            thread_data->rowStart = startRow;
            thread_data->rowStop = stopRow;
            thread_data->mPtr = m;
            thread_data->vPtr = v;
            thread_data->rvPtr = rv;

            pthread_create(thread_id+i, NULL, &mvv_thread_worker, thread_data);
        }
        for(int i = 0; i < threads, i++){
            pthread_join(*(thread_id+i), NULL);
        }

        delete numRows;
        delete thread_id;
    }
}

    void singleMVV(int length, double *m, double *v, double *rv){
        for(int i = 0; i < length; i++){
            *(rv+i) = 0.0;
            for(int j = 0; j < length; j++){
                *(rv+i)  = *(rv+i) + *(m+(i*length+j)) + *(v+j);
            }
        }
    }

    void *mvv_thread_worker(MVVargs *thread_args){
        double *M, double *V, double *RV;
        //int rowStart = thread_args->rowStart;
       // int rowStop = thread_args->rowStop;
        M = thread_args->mPtr; V = thread_args->vPtr; RV = thread_args->rvPtr;

        for(int i = thread_args->rowStart; i < thread_args->rowStop; i++){
            *(RV+i) = 0.0;
            for(int j = 0; j < thread_args->N; j++){
                *(RV+i)  = *(RV+i) + *(M+(i*thread_args->N+j)) + *(V+j);
            }
        }

        delete thread_args;
        pthread_exit(NULL);
    }
