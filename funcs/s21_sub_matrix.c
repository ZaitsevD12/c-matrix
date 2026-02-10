#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = 0;
  if (A->matrix == NULL || B->matrix == NULL || result == NULL ||
      is_nan_or_inf(A) || is_nan_or_inf(B))
    error_code = 1;
  else if ((A->rows != B->rows) || (A->columns != B->columns))
    error_code = 2;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error_code;
}
