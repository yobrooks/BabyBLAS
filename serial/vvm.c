#ifdef __cplusplus
    extern "C"{
#endif
void vvm_(int *threads, int *length, double *a, double *b, double *m);
#ifdef __cplusplus
    }
#endif
/* Perform Regular Tensor Product of 2 Vectors*/
void vvm_(int *threads, int *length, double *a, double *b, double *m){
    int len = *length;
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            *(m+(len*i+j)) = *(a+i) * *(b+j);
        }
    }
}