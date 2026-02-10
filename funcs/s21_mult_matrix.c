#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1 || A->matrix == NULL ||
      B == NULL || B->rows < 1 || B->columns < 1 || B->matrix == NULL ||
      result == NULL || is_nan_or_inf(A) || is_nan_or_inf(B))
    error_code = 1;
  else if (A->columns != B->rows)
    error_code = 2;
  else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++)
          result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
      }
    }
  }

  return error_code;
}
