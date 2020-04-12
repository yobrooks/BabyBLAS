/* Matrix Multiplication Function using PThreads */

#ifdef __cplusplus
extern "C" {
#endif
void mmm(int *threads, int *length, double *ma, double *mb, double *mc);
#ifdef __cplusplus
}
#endif
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Function Prototypes */
void *mmm_thread_worker();
void singleMMM(int *length, double *ma, double *mb, double *mc);

/* Struct For Passing Data to Threads */
struct MMMargs{
    int N;
    int rowStart;
    int rowStop;
    double *maPtr;
    double *mbPtr;
    double *mcPtr;
};

void mmm(int *threads, int *length, double *ma, double *mb, double *mc){
    int startRow, stopRow;
    int *numRows; //pointer to array or variable?
    pthread_t *thread_id; //arrays
    struct MMMargs *thread_data; //array of MMMargs structs

    //if fewer dimensions than threads, do single processor matrix mult
    if(*length < *threads){
        singleMMM(length, ma, mb, mc);
    }
    else{
        //allocate dynamic memory for arrays holding thread ids and number of rows for each thread
        thread_id = (pthread_t *) malloc (*(threads)*sizeof(pthread_t));
        numRows = (int *) malloc (*(threads) * sizeof(int));

        /*determine how many rows each thread will work on
        in case number of threads doesn't divide matrix dimensions evenly,
         then add to whatever is left over*/

        for(int i=0; i<*(threads); i++){
            *(numRows+i) = *(length)/(*threads);
        }

        for(int i=0; i<(*(length)% *(threads)); i++){
            *(numRows+i) = *(numRows+i)+1;
        }

        stopRow = 0;
        //allocate memory for the struct data and fill it with thread data
        //including which row to start and stop at and then create the thread
        for(int i=0; i < *(threads); i++){
            startRow=stopRow;
            stopRow=startRow+*(numRows+i);
            thread_data = (struct MMMargs *)  malloc(sizeof(struct MMMargs));
            thread_data->N = *length;
            thread_data->rowStart = startRow;
            thread_data->rowStop = stopRow;
            thread_data->maPtr = ma;
            thread_data->mbPtr = mb;
            thread_data->mcPtr = mc;

            pthread_create(thread_id+i, NULL, &mmm_thread_worker, thread_data);
        }
        for(int i = 0; i<*(threads); i++){
            pthread_join(*(thread_id+i), NULL);
        }

        free(numRows);
        free(thread_id);
    }

}

//Single Processor MMM
void singleMMM(int *length, double *ma, double *mb, double *mc){
    for(int i = 0; i < *(length); i++){
        for(int j = 0; j < *(length); j++){
            *(mc+(i* *(length)+j)) = 0.0;
            for(int k = 0; k < *(length); k++){
                *(mc+(i* *(length)+j)) = *(mc+(i* *(length)+j)) + *(ma+(i* *(length)+k)) * *(mb+(k* *(length)+j));
            }
        }
    }
}

void *mmm_thread_worker(MMMargs *thread_args){

    //Unpack the thread data from struct
    double *MA, *MB, *MC;
    int N = thread_args->N;
    int rowStart = thread_args->rowStart;
    int rowStop = thread_args->rowStop;
    MA = thread_args->maPtr;
    MB = thread_args->mbPtr;
    MC = thread_args->mcPtr;

    //do the actual matrix multiplication for responsible rows
    for(int i = rowStart; i < rowStop; i++){
        for(int j = 0; j < N; j++){
            *(MC+(i*N+j)) = 0.0;
            for(int k = 0; k < N; k++){
                *(MC+(i*N+j)) = *(MC+(i*N+j)) + **(MA+(i*N+k)) * *(MB+(k*N+j));
            }
        }
    }

    free(thread_args);
    pthread_exit(NULL);
}