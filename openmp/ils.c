#ifdef __cplusplus
extern "C" {
#endif
    void ils_(int *threads, int *length, double *m, double *v, double *rv);
#ifdef __cplusplus
}
#endif

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 


/* Prototypes */
int zerosInDiag(int N, double *a);
int converged(int N, double *a, double *b);
void dls_(int *threads, int *length, double *m, double *v, double *rv);


void ils_(int *threads, int *length, double *m, double *v, double *rv){
    printf("Using OpenMP\n");
    int len = *length;
    int numThreads = *threads;
    int ITERATION_MAX = 2000;
    int i, j;

    omp_set_num_threads(numThreads);
    //CHECK IF ZEROS IN DIAG
    if(!zerosInDiag(len, m)){
        double *x0 = malloc(len*sizeof(double));
        int iteration = 0;
        double sum1, sum2;
        ITERATION_MAX = fmax(ITERATION_MAX, len/3);
            //set up variables
        #pragma omp parallel for private(i)
            for(i = 0; i < len; i++){
                *(rv+i) = 0.0;
                *(x0+i) = *(v+i);
            }
            
        ITERATION_MAX = fmax(ITERATION_MAX, len/3);
        while(!converged(len, rv, x0) && iteration < ITERATION_MAX){
            #pragma omp parallel for private(i)
                for(i = 0; i < len; i++){
                    *(x0+i) = *(rv+i); //copy last result to initial values  
                }

            //reduction process
            #pragma omp parallel for private(i, j) reduction(+:sum1, sum2)
                for(i = 0; i < len; i++){
                    sum1 = 0.0;
                    for(j = 0; j < i-1; j++){
                        sum1 = sum1+*(m+i*len+j)* *(x0+j);
                    }
                    sum2 = 0.0;
                    for(j = i+1; j < len; j++){
                        sum2 = sum2+ *(m+i*len+j)* *(x0+j); 
                    }
                        
                    *(rv+i) = (*(v+i) - sum1 - sum2) / *(m+i*len+i);
                }
            iteration++;
        }
        free(x0); //initial value array can be deleted
        if(iteration == ITERATION_MAX){ //switch to DLS if max iterations reached
            printf(" *** ITERATIVE SOLVER FAILED TO REACH CONVERGENCE AFTER  ***\n");
            printf(" *** %d ITERATIONS, SWITCHING TO DIRECT SOLVER ***\n", iteration);
            dls_(threads, length, m, v, rv);
        }      
    }
     //if there are zeros along diag, switch to DLS
    else{
        printf(" *** FOUND A ZERO ELEMENT ALONG MATRIX DIAGONAL ***\n");
        printf(" ***  SWITCHING TO DIRECT SOLVER FOR PIVOTING   ***\n");
        dls_(threads, length, m, v, rv);
    }
}

int zerosInDiag(int N, double *a){
    double ZERO = 0.0;
    int foundZero = 0;
    for(int i = 0; i < N; i++){
        if(!foundZero){
            foundZero = fabs(*(a+i*N+i)) == ZERO;
        }
    }
    return foundZero;
}

int converged(int N, double *a, double *b){
    //Compute distance between vectors and check if 2-Norm is within tolerance
    double const TOL = 5.0e-15;
    double maxb = *(b+0);
    double sum = 0.0;
        for(int i = 0; i < N; i++){
            maxb = fmax(maxb,fabs(*(b+i)));
            sum += (*(a+i)-*(b+i))*(*(a+i)-*(b+i));
        }
    
    sum = sqrt(sum);

    return (sum/maxb < TOL);  
}