void mvv(int threads, int length, double *m, double *v, double *rv);

//NEED TO CHECK
void mvv(int threads, int length, double *m, double *v, double *rv){
   /* Perform Regular Matrix Vector Multiplication*/
    for(int i = 0; i < length; i++){
        *(rv+i) = 0.0;
        for(int j = 0; j < length; j++){
            *(rv+i)  = *(rv+i) + *(m+(i*length+j)) + *(v+j);
        }
    }
}