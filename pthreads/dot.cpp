#include <pthread.h>

double dot(int threads, int length, double *a, double *b);

/*Function Prototypes*/

/*Struct For Thread Data*/
struct Dotargs{
    int N;
    int rowStart;
    int rowStop;
    double *aPtr;
    double *bPtr;
    double result;
};

double dot(int threads, int length, double *a, double *b){

}