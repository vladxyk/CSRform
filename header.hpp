#ifndef CSR_H
#define CSR_H


void init_matrix(double *matrix, int n);
void init_vector(double *vec, int n);
void init_permutation_vector(int *pvec, int n);
void init_permutation_matrix(double *pmat, int *pvec, int n);

void CSR_arr_value(double *arrValue, double *mat, int n, int N);
void CSR_arr_col(int *arrCol, double *mat, int n, int N);
void CSR_arr_row_index(int *arrRowIndex, double *mat, int n);

void CSR_matrix_vector_multiplication(double *res, double *vec, double *arrValue, int *arrCol, int *arrRowIndex, int n);
void permutation_matrix_multiplication(double *matrixA, double *matrixB, double *pres, int n);

void print_matrix(double *matrix, int n);
void print_arr_value(double *arrValue, int NZ);
void print_arr_col(int *arrCol, int NZ);
void print_arr_row_index(int *arrRowIndex, int n);
void print_vector(double *vec, int n);
void print_res_matrix_vector_multiplication(double *res, int n);
void print_permutation_vector(int *pvec, int n);
void print_permutation_matrix(double *pmat, int n);
void print_res_permutation_matrix_multiplication(double *pres, int n);
#endif