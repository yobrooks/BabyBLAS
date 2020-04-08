void vvm(int threads, int length, double *a, double *b, double *m);

/* Perform Regular Tensor Product of 2 Vectors*/
void vvm(int threads, int length, double *a, double *b, double *m){
    
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length; j++){
            *(m+(length*i+j)) = *(a+i) * *(b+j);
        }
    }
}