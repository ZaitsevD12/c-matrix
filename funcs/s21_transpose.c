#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = WRONG_MATRIX;

  if (A != NULL && result != NULL && A->matrix != NULL && A->rows > 0 &&
      A->columns > 0) {
    if (s21_create_matrix(A->columns, A->rows, result) == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
      status = OK;
    } else {
      status = CALCULATION_ERROR;
    }
  }
  return status;
}