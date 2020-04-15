//Direct Linear Solver Serial, written by Dr. Andrew Pounds
#ifdef __cplusplus
extern "C" {
#endif
    void dls_(int *threads, int *length,  double *m, double *v, double*rv);
#ifdef __cplusplus
}
#endif

#include <math.h>  
#include <stdio.h>  
#include <stdlib.h>

/*Function Prototypes*/
int strictlyDiagonallyDominant(int N, double *a); 

void dls_(int *threads, int *length, double *m, double *v, double *rv){
    int len = *length;
    double ZERO = 0.0;
    int k;
    double tmp;
    //check matrix m for strict diagonal dominance to see if matrix
    //reduction is possible without doing row interchanges
    if(!strictlyDiagonallyDominant(len, m)){
        printf("NOT DIAGDOM\n");
        //Do Gaussian Elimination with Partial Pivoting

        //create array to hold pivot swaps
        int *p = malloc((len-1)*sizeof(int));
        for(k =0; k < len-1; k++){
            *(p+k) = k;
        }

        //search for largest value in column and swap entire row
        //containing that value with current pivot row
        for(int k = 0; k<len-1; k++){
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
                for (int j=k;j<len;j++) {
                    tmp = *(m+k*len+j);
                    *(m+k*len+j) = *(m+u*len+j);
                    *(m+u*len+j)=tmp;
                }
            }

            // Now do block reduction
            *(p+k) = iPivot;
            if(*(m+k*len+k) != ZERO){
                for (int rows=k+1;rows<len;rows++) { 
                    *(m+rows*len+k) = *(m+rows*len+k) / *(m+k*len+k);

                    for (int rows2=k+1;rows2<len;rows2++) { 
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

        //Now that the matrices have been reduced, 
        //start back substitution to solve for vector RV

        //Arrange vector v so that it has undergone same operations as matrix m
        //This will form vector y for the solution Ux = y where U is upper triangular matrix
        //formed in the elimination process above

        for(k=0; k<len-1; k++ ) {
            // Swap rows x with p(k) 
            tmp = *(v+k);
            *(v+k) = *(v+ *(p+k));
            *(v+ *(p+k)) = tmp;

            for(int j=k+1;j<len;j++){ 
                *(v+j)= *(v+j) - *(v+k) * *(m+len*j+k);  
            }
        }

        //Now do the backward substitution to get solution vector vr
        *(v+len-1) = *(v+len-1) / *(m+len*(len-1)+(len-1));
        for(int i=len-2;i>=0;i--){
            tmp = 0.0;
            for(int j=i+1;j<len;j++){
                tmp = tmp + *(m+i*len+j) * *(v+j);
            }
            *(v+i) = (*(v+i) - tmp ) / *(m+i*len+i); 
        }

        for(int i=0;i<len;i++){
            *(rv+i) = *(v+i);
        }
        free(p);
    }
    else{
        //Matrix is strictly diagonally dominant
        //verify none of pivot elements are zero
        int singular = 1;
        int i = 0;
        while (i<len && singular){
            singular = *(m+i*len+i) == ZERO;   
            i++;
        }

        if (singular) {
            printf( " *** MATRIX A IS SINGULAR *** \n");
            printf( "    -- EXECUTION HALTED -- \n");
            exit(1);
        }

        //Strictly diagonally dominant matrix that isn't singluar
        //do LU factorization
        for (k=0; k<len-1; k++){
            for(int rows=k+1;rows<len;rows++){
                *(m+rows*len+k) = *(m+rows*len+k) / *(m+k*len+k);
                for(int rows2=k+1;rows2<len;rows2++) { 
                    *(m+rows*len+rows2) = *(m+rows*len+rows2) - 
                        *(m+rows*len+k) * *(m+k*len+rows2) ;
                }
            }
        }

        //LU factorization done; do two triangular back substitutions. 
        // Solving lower-triangular (Ly=b) first, overwriting b with y

        for(k=0; k<len-1; k++){
            for(int j=k+1;j<len;j++){
                *(v+j)= *(v+j) - *(v+k) * *(m+len*j+k); 
            } 
        }

        // Now we can do the backward substitution to get the solution
        // vector x for the upper-triangular system (Ux=y) overwriting y (stored in b)
        // with x
        *(v+len-1) = *(v+len-1) / *(m+len*(len-1)+(len-1));
        for(int i=len-2;i>=0;i--){
            tmp = 0.0;
            for (int j=i+1;j<len;j++) {
                tmp = tmp + *(m+i*len+j) * *(v+j);
            }
            *(v+i) = (*(v+i) - tmp) / *(m+i*len+i); 
        }

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
   printf("TEST PASSED %d\n", testPassed);
    return testPassed;
}