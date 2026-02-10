#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = WRONG_MATRIX;
  int should_continue = 1;

  if (A != NULL && A->matrix != NULL && A->rows == A->columns && A->rows > 0) {
    status = OK;
    if (s21_create_matrix(A->rows, A->columns, result) == OK) {
      if (A->rows == 1) {
        result->matrix[0][0] = 1.0;
      } else {
        for (int i = 0; i < A->rows && should_continue; i++) {
          for (int j = 0; j < A->columns && should_continue; j++) {
            matrix_t minor;
            if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) == OK) {
              s21_create_minor(A, &minor, i, j);
              double minor_det = 0.0;
              if (s21_determinant(&minor, &minor_det) == OK) {
                result->matrix[i][j] =
                    ((i + j) % 2 == 0 ? minor_det : -minor_det);
              } else {
                status = CALCULATION_ERROR;
                should_continue = 0;
              }
              s21_remove_matrix(&minor);
            } else {
              status = CALCULATION_ERROR;
              should_continue = 0;
            }
          }
        }
      }
    } else {
      status = CALCULATION_ERROR;
    }
  } else if (A != NULL && A->matrix != NULL &&
             (A->rows != A->columns || A->rows <= 0)) {
    status = CALCULATION_ERROR;
  }
  return status;
}
