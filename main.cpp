#include <iostream>
#include <fstream>
#include <algorithm>
#include "mkl.h"
#include "mkl_spblas.h"
#include <time.h>
#include "header.hpp"

#define BILLION 1000000000;

using namespace std;

int main(int argc, char *argv[]){

    int n;
    cout << "fuu" << endl;
    //cout << "Enter size of matrix: ";
    //cin >> n;

    int NZ = 0;
   
    //double *mat = new double[n * n];
    //init_matrix(mat, n);
    
    ifstream fin(argv[1]);

    int M, N, L;

    while (fin.peek() == '%'){
        fin.ignore(2048, '\n');
    }

    fin >> M >> N >> L;


    double* mat = new double[M*N];	    

    for (int l = 0; l < L; l++){
	    int m, n;
	    double data;
	    fin >> m >> n >> data;
	    mat[(m-1) + (n-1)*M] = data;
    }

    fin.close();

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(mat[i * N + j] != 0){
                NZ++;
            }
        }
    }
    cout << "NZ = " << NZ << endl;

    double *arrValue = new double[NZ];
    int *arrCol = new int[NZ];
    int *arrRowIndex = new int[NZ];
    CSR_arr_value(arrValue, mat, N, NZ);
    CSR_arr_col(arrCol, mat, N, NZ);
    CSR_arr_row_index(arrRowIndex, mat, N);
  
    double *vec = new double[N];
    init_vector(vec, N);
    double *res = new double[N];

    cout << endl;

    struct timespec startMyTimeMul, endMyTimeMul, startMKLTimeMul, endMKLTimeMul;

    clock_gettime(CLOCK_REALTIME, &startMyTimeMul);
    CSR_matrix_vector_multiplication(res, vec, arrValue, arrCol, arrRowIndex, N);
    clock_gettime(CLOCK_REALTIME, &endMyTimeMul);


    //print_matrix(mat, N);
    //print_arr_value(arrValue, NZ);
    //print_arr_col(arrCol, NZ);
    //print_arr_row_index(arrRowIndex, N);
    //print_vector(vec, N);
    //print_res_matrix_vector_multiplication(res, N);

    double resMyTime = (endMyTimeMul.tv_sec - startMyTimeMul.tv_sec) + (double)(endMyTimeMul.tv_nsec - startMyTimeMul.tv_nsec) / BILLION;
    cout << "my Time matrix-vector multiplication: \t" << resMyTime << " sec" << endl;

    double *resMKL = new double[N];
    char transa = 'n';
    
    clock_gettime(CLOCK_REALTIME, &startMKLTimeMul);
    mkl_dcsrgemv(&transa, &N, arrValue, arrRowIndex, arrCol, vec, resMKL);
    clock_gettime(CLOCK_REALTIME, &endMKLTimeMul);

    double resMKLTime = (endMKLTimeMul.tv_sec - startMKLTimeMul.tv_sec) + (double)(endMKLTimeMul.tv_nsec - startMKLTimeMul.tv_nsec) / BILLION;

    cout << "MKL Time matrix-vector multiplication: \t" << resMKLTime << " sec" << endl;
    cout << endl;

    int *pvec = new int[N];
    double *pmat = new double[M * N];

    init_permutation_vector(pvec, N);
    init_permutation_matrix(pmat, pvec, N);
    //print_permutation_vector(pvec, n);
    //print_permutation_matrix(pmat, n);

    double *permResCol = new double[M * N];
    double *permResRow = new double[M * N];
    
    struct timespec startMyTimePermCol, endMyTimePermCol, startMyTimePermRow, endMyTimePermRow;
    
    clock_gettime(CLOCK_REALTIME, &startMyTimePermCol);
    permutation_matrix_multiplication(mat, pmat, permResCol, N); //col
    clock_gettime(CLOCK_REALTIME, &endMyTimePermCol);
    double resMyTimePermCol = (endMyTimePermCol.tv_sec - startMyTimePermCol.tv_sec) + (double)(endMyTimePermCol.tv_nsec - startMyTimePermCol.tv_nsec) / BILLION;
    
    clock_gettime(CLOCK_REALTIME, &startMyTimePermRow);
    permutation_matrix_multiplication(pmat, mat, permResRow, N); //row
    clock_gettime(CLOCK_REALTIME, &endMyTimePermRow);
    double resMyTimePermRow = (endMyTimePermRow.tv_sec - startMyTimePermRow.tv_sec) + (double)(endMyTimePermRow.tv_nsec - startMyTimePermRow.tv_nsec) / BILLION;

    cout << "my Time permutation by columns: \t" << resMyTimePermCol << " sec" << endl;
    cout << "my Time permutation by rows: \t\t" << resMyTimePermRow << " sec" << endl;
    //print_res_permutation_matrix_multiplication(permResCol, n);
    //print_res_permutation_matrix_multiplication(permResRow, n);

    int NZperm = 0;

    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(pmat[i * N + j] != 0){
                NZperm++;
            }
        }
    }

    double *arrValueP = new double[NZperm];
    //int *arrColP = new int[nz]; pvec
    int *arrRowIndexP = new int[N + 1];
    CSR_arr_value(arrValueP, pmat, N, NZperm);
    CSR_arr_row_index(arrRowIndexP, pmat, N);

/*
    char matdescra[6];
    matdescra[0] = 'g';
    matdescra[3] = 'c';
*/
    int pointerBrow[N];
    int pointerErow[N];
    int pointerBcol[N];
    int pointerEcol[N];
    
    double *pres = new double[M * N];

    for(int i = 0; i < N; i++){
        pointerBrow[i] = arrRowIndexP[i];
        pointerErow[i] = arrRowIndexP[i + 1];
        pointerBcol[i] = arrRowIndex[i];
        pointerEcol[i] = arrRowIndex[i + 1];
    }

/*
    double al = 1.0;
    double beta = 0.0;

    mkl_dcsrmm (&transa, &n, &n, &n, &al, matdescra, arrValue, arrCol, pointerBcol, pointerEcol, arrP, &n, &beta, pres, &n);
    mkl_dcsrmm (&transa, &n, &n, &n, &al, matdescra, arrValueP, pvec, pointerBrow, pointerErow, arr, &n, &beta, pres, &n); //row
    
    for(int i = 0; i < n*n; i++){
        cout << pres[i] << " ";
    }
*/
    cout << endl;

    sparse_matrix_t A, B, C;

    mkl_sparse_d_create_csr(&A, SPARSE_INDEX_BASE_ZERO, M, N, pointerBcol, pointerEcol, arrCol, arrValue);
    mkl_sparse_d_create_csr(&B, SPARSE_INDEX_BASE_ZERO, M, N, pointerBrow, pointerErow, pvec, arrValueP);
    
    struct timespec startMKLTimePermCol, endMKLTimePermCol, startMKLTimePermRow, endMKLTimePermRow;
    
    clock_gettime(CLOCK_REALTIME, &startMKLTimePermCol);
    mkl_sparse_spmm(SPARSE_OPERATION_NON_TRANSPOSE, A, B, &C);
    clock_gettime(CLOCK_REALTIME, &endMKLTimePermCol);
    double resMKLTimePermCol = (endMKLTimePermCol.tv_sec - startMKLTimePermCol.tv_sec) + (double)(endMKLTimePermCol.tv_nsec - startMKLTimePermCol.tv_nsec) / BILLION;

    clock_gettime(CLOCK_REALTIME, &startMKLTimePermRow);
    mkl_sparse_spmm(SPARSE_OPERATION_NON_TRANSPOSE, B, A, &C);
    clock_gettime(CLOCK_REALTIME, &endMKLTimePermRow);
    double resMKLTimePermRow = (endMKLTimePermRow.tv_sec - startMKLTimePermRow.tv_sec) + (double)(endMKLTimePermRow.tv_nsec - startMKLTimePermRow.tv_nsec) / BILLION;

    cout << "MKL Time permutation by columns: \t" << resMKLTimePermCol << " sec" << endl;
    cout << "MKL Time permutation by rows: \t\t" << resMKLTimePermRow << " sec" << endl;

    cout << endl;



    delete []mat;
    delete []arrValue;
    delete []arrCol;
    delete []arrRowIndex;
    delete []vec;
    delete []res;
    delete []resMKL;
    delete []pvec;
    delete []pmat;
    delete []permResCol;
    delete []permResRow;
    delete []arrValueP;
    delete []arrRowIndexP;
    return 0;
}