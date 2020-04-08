void mmm(int threads, int length, double *ma, double *mb, double *mc);

void mmm(int threads, int length, double *ma, double *mb, double *mc){
    
/*Perform Regular Matrix Matrix Multiplication*/
    for(int i = 0; i < length; i++){
        for(int j = 0; j < length; j++){
            *(mc+(i*length+j)) = 0.0;
            for(int k = 0; k < length; k++){
                *(mc+(i*length+j)) = *(mc+(i*length+j)) + *(ma+(i*length+k)) * *(mb+(k*length+j));
            }
        }
    }
}