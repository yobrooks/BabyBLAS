
//double *a is same as double a []
// a and b are vectors
double dot(int threads, int length, double *a, double *b);

/*Perform Regular Dot Product--No Optimization*/
//Is pointers necessary?
double dot(int threads, int length, double *a, double *b){
    double product = 0.0; //is there a way to eliminate keeping track of this variable?
    for(int i = 0; i < length; i++){
        product = product + *(a+i) * *(b+i);
    }
}

