#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int status = OK;
  if (A == NULL || result == NULL || A->matrix == NULL) {
    status = WRONG_MATRIX;
  } else if (A->rows != A->columns) {
    status = CALCULATION_ERROR;
  } else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    *result = 0;
    for (int i = 0; i < A->columns; i++) {
      matrix_t minor;
      if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) == OK) {
        s21_create_minor(A, &minor, 0, i);
        double minor_det = 0;
        if (s21_determinant(&minor, &minor_det) == OK) {
          *result += (i % 2 == 0 ? 1 : -1) * A->matrix[0][i] * minor_det;
        }
        s21_remove_matrix(&minor);
      } else {
        status = CALCULATION_ERROR;
        break;
      }
    }
  }
  return status;
}

void s21_create_minor(matrix_t *A, matrix_t *minor, int row, int col) {
  for (int i = 0, minor_i = 0; i < A->rows; i++) {
    if (i == row) continue;
    for (int j = 0, minor_j = 0; j < A->columns; j++) {
      if (j == col) continue;
      minor->matrix[minor_i][minor_j] = A->matrix[i][j];
      minor_j++;
    }
    minor_i++;
  }
}
