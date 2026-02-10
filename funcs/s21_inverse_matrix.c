#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = WRONG_MATRIX;
  if (A != NULL && A->matrix != NULL && A->rows > 0 && result != NULL) {
    if (A->rows != A->columns)
      status = CALCULATION_ERROR;
    else {
      double det = 0.0;
      if (s21_determinant(A, &det) == OK && fabs(det) > 1e-7) {
        matrix_t cofactors;
        if (s21_calc_complements(A, &cofactors) == OK) {
          s21_transpose(&cofactors, result);
          if (result->matrix != NULL) {
            for (int i = 0; i < result->rows; i++) {
              for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] /= det;
              }
            }
            status = OK;
          } else {
            status = CALCULATION_ERROR;
          }
          s21_remove_matrix(&cofactors);
        } else {
          status = CALCULATION_ERROR;
        }
      } else {
        status = (fabs(det) <= 1e-7) ? CALCULATION_ERROR : status;
      }
    }
  }
  return status;
}