//Iterative Linear Solver Serial, written by Dr. Andrew Pounds

#ifdef __cplusplus
extern "C" {
#endif
    void ils_(int *threads, int *length,  double *m, double *v, double *rv);
#ifdef __cplusplus
}
#endif

#include <math.h>  
#include <stdio.h>  
#include <stdlib.h>

/* Function Prototypes*/
void dls_(int *threads, int *length,  double *m, double *v, double *rv);
int zerosInDiag(int N, double *a);
int converged(int N, double *a, double *b);

void ils_(int *threads, int *length, double *m, double *v, double *rv){
    int ITERATION_MAX = 2000;
    int len = *length;

    //check if there are zeros along diagonal in matrix m
    //if there aren't continue with the iterative Jacobi
    if(!zerosInDiag(len, m)){
        //create a temporary vector x0 to hold initial values 
        double *x0 = malloc(len*sizeof(double));
        //COUNT THIS AS AN OPTIMIZATION???
        //fill the result vector rv with initial values of 0
        //fill x0 vector with values of vector v
        for(int i = 0; i < len; i++){
            *(rv+i) = 0.0;
            *(x0+i) = *(v+i);
        }
        //if more than len/3 iterations are done, direct solver is more efficient
        ITERATION_MAX = fmax(ITERATION_MAX, len/3);
        int iteration = 0;
        while(!converged(len, rv, x0) && iteration < ITERATION_MAX){
            for(int i = 0; i < len; i++){
                *(x0+i) = *(rv+i); //copy last result to initial values
                
            }
            //start reduction process
            for(int i = 0; i < len; i++){
                double sum1 = 0.0;
                for(int j = 0; j < i-1; j++){
                     sum1 = sum1+*(m+i*len+j)* *(x0+j);
                }
                double sum2 = 0.0;
                for(int j = i+1; j < len; j++){
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

//check for zeros along diagonal
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

//check for convergence (A.Pounds, 2018)
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