#include <iostream>

using namespace std;

void permutation_matrix_multiplication(double *matrixA, double *matrixB, double *pres, int n){
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            pres[i * n + j] = 0;
            for(int k = 0; k < n; k++){
                pres[i * n + j] += matrixA[i * n + k] * matrixB[k * n + j];
            }
        }
    }
}
