#include <iostream>

using namespace std;

void print_matrix(double *matrix, int n){
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << matrix[i * n + j] << " ";
        }
        cout << endl;
    }
}

void print_arr_value(double *arrValue, int NZ){
    
    cout << "\narr1.Value: \t";
    for(int i = 0; i < NZ; i++){
        cout << arrValue[i] << " ";
    }
    cout << endl;
}

void print_arr_col(int *arrCol, int NZ){
    
    cout << "arr2.Col: \t";
    for(int i = 0; i < NZ; i++){
        cout << arrCol[i] << " ";
    }
    cout << endl;
}

void print_arr_row_index(int *arrRowIndex, int n){
    
    cout << "arr3.RowIndex: \t";
    for(int i = 0; i < (n + 1); i++){
        cout << arrRowIndex[i] << " ";
    }
    cout << endl;
}

void print_vector(double *vec, int n){
    
    cout << "\nvec: \t\t";
    for(int i = 0; i < n; i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}

void print_res_matrix_vector_multiplication(double *res, int n){
    
    cout << "matrix * vec: \t";
    for(int i = 0; i < n; i++){
        cout << res[i] << " ";
    }
    cout << endl;
}

void print_permutation_vector(int *pvec, int n){
    
    cout << "perm vec: \t";
    for(int i = 0; i < n; i++){
        cout << pvec[i] << " ";
    }
    cout << endl;
}

void print_permutation_matrix(double *pmat, int n){
    
    cout << "perm matrix: " << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << pmat[i * n + j] << " ";
        }
        cout << endl;
    }
}

void print_res_permutation_matrix_multiplication(double *pres, int n){
    
    cout << "perm res:" << endl; 
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << pres[i * n + j] << " ";
        }
        cout << endl;
    }
}