#include <iostream>

using namespace std;

void CSR_arr_value(double *arrValue, double *mat, int n, int N){

    int t = 0;
    for(int i = 0; i < (n * n); i++){  
       
        if(mat[i] == 0){
            i++;
        }

        arrValue[t] = mat[i];
        if(arrValue[t] != 0){
            t++;
        }
    }
}

void CSR_arr_col(int *arrCol, double *mat, int n, int N){

    for(int k = 0; k < N; ){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(mat[i * n +j] != 0){
                    arrCol[k] = j;
                    k++;
                }
            }
        }
    }
}

void CSR_arr_row_index(int *arrRowIndex, double *mat, int n){
    
    arrRowIndex[0] = 0;
    int counter = 0;
    for(int k = 1; k < n; ){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(mat[i *n + j] != 0){
                    counter++;
                }
                arrRowIndex[k] = counter;
            }
            k++;
        }
    }
}
