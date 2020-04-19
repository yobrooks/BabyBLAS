#ifdef __cplusplus
extern "C" {
#endif
    void dls_(int *threads, int *length, double *m, double *v, double *rv);
#ifdef __cplusplus
}
#endif

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

/*Function Prototypes*/
int strictlyDiagonallyDominant(int N, double *a); 

void dls_(int *threads, int *length, double *m, double *v, double *rv){
    int len = *length;
    int k, j, i;
    double ZERO = 0.0;
    double tmp;
    omp_set_num_threads(*threads);

    if(!strictlyDiagonallyDominant(len, m)){
        int *p = malloc((len-1)*sizeof(int));
        for(k =0; k < len-1; k++){
            *(p+k) = k;
        }

        for(k = 0; k<len-1; k++){
            double pivotMax = *(m+k*len+k);
            int iPivot = k;
            int u;
            for (u=k;u<len;u++) {
                if (fabs(*(m+u*len+k)) > fabs(pivotMax) ) {
                    pivotMax = *(m+u*len+k);
                    iPivot = u;
                }
            }
             // If a greater pivot value was found, swap the rows.
            if (iPivot != k) {
                u = iPivot;
                for (j=k;j<len;j++) {
                    tmp = *(m+k*len+j);
                    *(m+k*len+j) = *(m+u*len+j);
                    *(m+u*len+j)=tmp;
                }
            }

            *(p+k) = iPivot;
            int rows, rows2;
            //block reduction
            if(*(m+k*len+k) != ZERO){ 
            #pragma parallel omp for
                for (rows=k+1;rows<len;rows++) { 
                    *(m+rows*len+k) = *(m+rows*len+k) / *(m+k*len+k);    
                    for (rows2=k+1;rows2<len;rows2++) { 
                        *(m+rows*len+rows2) = *(m+rows*len+rows2) - 
                            *(m+rows*len+k) * *(m+k*len+rows2) ;
                    }
                }
            }
            else{
                /* Handle the case of a zero pivot element, singular matrix */
                printf( "Element a[%d][%d} = %f\n", k, k, *(m+k*len+k)); 
                printf( " *** MATRIX A IS SINGULAR *** \n");
                printf( "    -- EXECUTION HALTED --\n");
                exit(1);
            }
        }

       // #pragma omp parallel for private(k,j, tmp)
        for(k=0; k<len-1; k++ ) {
            // Swap rows x with p(k) 
            tmp = *(v+k);
            *(v+k) = *(v+ *(p+k));
            *(v+ *(p+k)) = tmp;

            for(j=k+1;j<len;j++){ 
                *(v+j)= *(v+j) - *(v+k) * *(m+len*j+k);  
            }
        }
        

        //backward substitution
        *(v+len-1) = *(v+len-1) / *(m+len*(len-1)+(len-1));
        //#pragma omp parallel for private(i, j) reduction(+:tmp)
            for(i=len-2;i>=0;i--){
                tmp = 0.0;
                for(j=i+1;j<len;j++){
                    tmp = tmp + *(m+i*len+j) * *(v+j);
                }
                *(v+i) = (*(v+i) - tmp ) / *(m+i*len+i);   
            }
        #pragma omp parallel private(i)
            for(i=0;i<len;i++){
                *(rv+i) = *(v+i);
            }
        free(p);
        
    }
    else{
        int singular = 1;
        i = 0;
        while (i<len && singular){
            singular = *(m+i*len+i) == ZERO;   
            i++;
        }

        if (singular) {
            printf( " *** MATRIX A IS SINGULAR *** \n");
            printf( "    -- EXECUTION HALTED -- \n");
            exit(1);
        }

        int rows, rows2;
        //LU factorization
        
        #pragma parallel omp for
            for (k=0; k<len-1; k++){
                for(rows=k+1;rows<len;rows++){
                    *(m+rows*len+k) = *(m+rows*len+k) / *(m+k*len+k);
                    for(rows2=k+1;rows2<len;rows2++) { 
                        *(m+rows*len+rows2) = *(m+rows*len+rows2) - 
                            *(m+rows*len+k) * *(m+k*len+rows2) ;
                    }
                }
            }

        //triangular back sub
       // #pragma omp parallel for private(k, j)
            for(k=0; k<len-1; k++){
                for(j=k+1;j<len;j++){
                    *(v+j)= *(v+j) - *(v+k) * *(m+len*j+k); 
                } 
            }

        *(v+len-1) = *(v+len-1) / *(m+len*(len-1)+(len-1));
   // #pragma omp parallel private(i, j)
    for(i=len-2;i>=0;i--){
            tmp = 0.0;
        for (j=i+1;j<len;j++) {
            tmp = tmp + *(m+i*len+j) * *(v+j);
        }
            
        *(v+i) = (*(v+i) - tmp) / *(m+i*len+i);
    }
    
    #pragma omp parallel private(i)
        for (int i=0;i<len;i++){
            *(rv+i) = *(v+i);
        } 
        
    }
}

int strictlyDiagonallyDominant(int N, double *a){
    int testPassed = 1;
    double sum = 0.0;
    for(int row=0;row<N;row++){ 
        if(testPassed) {
            sum = 0.0;
            for (int i=0;i<N;i++) sum+=*(a+row*N+i);
            sum-=fabs(*(a+row*N+row)); 
            testPassed = fabs(*(a+row*N+row)) > sum;
        }
    }
    return testPassed;
}
