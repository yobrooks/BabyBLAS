#ifdef __cplusplus
    extern "C"{
#endif
void mvv_(int *threads, int *length, double *m, double *v, double *rv);
#ifdef __cplusplus
    }
#endif
//NEED TO CHECK
//M = matrix; V = vector, RV = result vector
void mvv_(int *threads, int *length, double *m, double *v, double *rv){

    int len = *length;
   /* Perform Regular Matrix Vector Multiplication*/
    for(int i = 0; i < len; i++){
        *(rv+i) = 0.0;
        for(int j = 0; j < len; j++){
            *(rv+i) = *(m +(len*i)+j) * *(v+j);
        }
    }
}