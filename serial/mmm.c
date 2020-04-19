#ifdef __cplusplus
    extern "C"{
#endif
void mmm_(int *threads, int *length, double *ma, double *mb, double *mc);
#ifdef __cplusplus
    }
#endif

void mmm_(int *threads, int *length, double *ma, double *mb, double *mc){
    int len = *length;
/*Perform Regular Matrix Matrix Multiplication*/
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            *(mc+(i*len+j)) = 0.0;
            for(int k = 0; k < len; k++){
                *(mc+(i*len+j)) = *(mc+(i*len+j)) + *(ma+(i*len+k)) * *(mb+(k*len+j));
            }
        }
    }
}