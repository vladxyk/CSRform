#include <iostream>

using namespace std;

void CSR_matrix_vector_multiplication(double *res, double *vec, double *arrValue, int *arrCol, int *arrRowIndex, int n){

    for(int i = 0; i < n; i++){
        res[i] = 0;
        for(int j = arrRowIndex[i]; j < arrRowIndex[i + 1]; j++){
            res[i] += arrValue[j] * vec[arrCol[j]];
        }
    }
/*
    cout << "matrix * vec: \t";
    for(int i = 0; i < n; i++){
        cout << res[i] << " ";
    }

    cout << endl;
*/
}
