#include <iostream>

using namespace std;

void init_matrix(double *matrix, int n){
    
    srand(time(NULL));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i * n + j] = rand()%4;
        }
    }  
}

void init_vector(double *vec, int n){

    srand(time(NULL));
    
    for(int i = 0; i < n; i++){
        vec[i] = rand()%10;
    }
}

void init_permutation_vector(int *pvec, int n){
    
    srand(time(NULL));
    
    for(int i = 0; i < n; i++){
        pvec[i] = i;
    }
    for(int k = n; k > 0; k--){
        int j = rand()%n;
        int tmp = pvec[k - 1];
        pvec[k - 1] = pvec[j];
        pvec[j] = tmp;
    }
}

void init_permutation_matrix(double *pmat, int *pvec, int n){

    for(int i = 0; i < n; i++){
        pmat[i * n + pvec[i]] = 1;
    }
}
