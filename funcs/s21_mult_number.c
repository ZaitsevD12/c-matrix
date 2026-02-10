#include "../s21_matrix.h"

int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
  int error_code = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1 || A->matrix == NULL ||
      result == NULL || is_nan_or_inf(A))
    error_code = 1;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return error_code;
}
