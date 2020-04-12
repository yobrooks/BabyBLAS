void ils(int threads, int length, double *m, double *v, double *rv);

int zerosInDiag(int num, double *m);
int converge(int num, double *a, doble *b);

void ils(int threads, int length, double *m, double *v, double *rv){
    
    double *tempV;
   
    if(!zerosInDiag(length, m)){
        tempV = malloc(length * sizeof(double));
        for(int i = 0; i < length; i++){
            *(rv+i) = 0.0;
        }
        for(int i = 0; i < length)
    }
}

int zerosInDiag(int num, double *m){
 
}

int converge(int num, double *a, double *b){

}