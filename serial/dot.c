
//double *a is same as double a []
// a and b are vectors
#ifdef __cplusplus
    extern "C"{
#endif
double dot_(int *threads, int *length, double *a, double *b);
#ifdef __cplusplus
    }
#endif
/*Perform Regular Dot Product--No Optimization*/
//Is pointers necessary?
double dot_(int *threads, int *length, double *a, double *b){
    int len = *length;
    double product = 0.0; //is there a way to eliminate keeping track of this variable?
    for(int i = 0; i < len; i++){
        product = product + *(a+i) * *(b+i);
    }
    return product;
}

