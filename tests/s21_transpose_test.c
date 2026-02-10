#include "s21_matrix_test.h"

START_TEST(transpose) {
  ck_assert_int_eq(s21_transpose(NULL, NULL), ERROR_INIT);
}
END_TEST

START_TEST(transpose_1) {
  ck_assert_int_eq(s21_transpose((void *)0, NULL), ERROR_INIT);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A = {0}, result = {0};
  int rows = 3, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t A = {0}, result = {0}, result_tmp = {0};
  int rows = 3, columns = 2;
  int sum = 0;
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  s21_create_matrix(columns, rows, &result_tmp);
  result_tmp.matrix[0][0] = 1;
  result_tmp.matrix[0][1] = 2;
  result_tmp.matrix[0][2] = 3;
  result_tmp.matrix[1][0] = 4;
  result_tmp.matrix[1][1] = 5;
  result_tmp.matrix[1][2] = 6;
  s21_transpose(&A, &result);
  ck_assert_int_eq(sum, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_tmp);
}
END_TEST

START_TEST(s21_transpose_test_empty) {
  matrix_t A = {0}, result = {0};
  ck_assert_int_eq(ERROR_INIT, s21_transpose(&A, &result));
}

START_TEST(s21_transpose_test_empty2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(ERROR_INIT, s21_transpose(&A, &result));
}

START_TEST(s21_transpose_test_columns) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 8.765;
  ck_assert_int_eq(OK, s21_transpose(&A, &result));
  ck_assert_ldouble_eq_tol(A.matrix[0][0], result.matrix[0][0], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(s21_transpose_test_rows) {
  matrix_t A = {0}, result = {0}, test_result = {0};
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(1, 2, &test_result);
  A.matrix[0][0] = test_result.matrix[0][0] = 8.765;
  A.matrix[1][0] = test_result.matrix[0][1] = -58765.4;
  ck_assert_int_eq(OK, s21_transpose(&A, &result));
  ck_assert_ldouble_eq_tol(test_result.matrix[0][0], result.matrix[0][0],
                           1e-06);
  ck_assert_ldouble_eq_tol(test_result.matrix[0][1], result.matrix[0][1],
                           1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&test_result);
  s21_remove_matrix(&result);
}

START_TEST(s21_transpose_test_nulls) {
  matrix_t A = {0}, result = {0};
  A.rows = A.columns = 5;
  ck_assert_int_eq(ERROR_INIT, s21_transpose(&A, &result));
}

START_TEST(s21_transpose_test1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(OK, s21_transpose(&A, &result));
  ck_assert_ldouble_eq_tol(1, result.matrix[0][0], 1e-06);
  ck_assert_ldouble_eq_tol(3, result.matrix[0][1], 1e-06);
  ck_assert_ldouble_eq_tol(2, result.matrix[1][0], 1e-06);
  ck_assert_ldouble_eq_tol(4, result.matrix[1][1], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_test2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = -0.0000000001;
  A.matrix[0][1] = 3.453415;
  A.matrix[1][0] = 9534983493.4349;
  A.matrix[1][1] = 5648765.21876578678;
  A.matrix[2][0] = 1.1111111;
  A.matrix[2][1] = 0;
  ck_assert_int_eq(OK, s21_transpose(&A, &result));
  ck_assert_ldouble_eq_tol(A.matrix[0][0], result.matrix[0][0], 1e-06);
  ck_assert_ldouble_eq_tol(A.matrix[1][0], result.matrix[0][1], 1e-06);
  ck_assert_ldouble_eq_tol(A.matrix[2][0], result.matrix[0][2], 1e-06);
  ck_assert_ldouble_eq_tol(A.matrix[0][1], result.matrix[1][0], 1e-06);
  ck_assert_ldouble_eq_tol(A.matrix[1][1], result.matrix[1][1], 1e-06);
  ck_assert_ldouble_eq_tol(A.matrix[2][1], result.matrix[1][2], 1e-06);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_transpose(void) {
  Suite *s = suite_create("suite_transpose");
  TCase *tc = tcase_create("case_transpose");

  tcase_add_test(tc, transpose);
  tcase_add_test(tc, transpose_1);
  tcase_add_test(tc, transpose_2);
  tcase_add_test(tc, transpose_3);

  tcase_add_test(tc, s21_transpose_test_empty);
  tcase_add_test(tc, s21_transpose_test_empty2);
  tcase_add_test(tc, s21_transpose_test_columns);
  tcase_add_test(tc, s21_transpose_test_rows);
  tcase_add_test(tc, s21_transpose_test_nulls);
  tcase_add_test(tc, s21_transpose_test1);
  tcase_add_test(tc, s21_transpose_test2);

  suite_add_tcase(s, tc);
  return s;
}