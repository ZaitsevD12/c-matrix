#include "s21_matrix_test.h"

START_TEST(mult_number_1) {
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(s21_mult_number(&A, 5., NULL), ERROR_INIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_2) {
  matrix_t A = {0};
  s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(s21_mult_number(&A, 5., (void *)0), ERROR_INIT);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_3) {
  matrix_t A = {0}, result = {0};
  int rows = 5, columns = 5;
  double number = (double)(rand()) / RAND_MAX;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] * number, result.matrix[i][j],
                              1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_null) {
  double number = 10;
  matrix_t A = {0}, result = {0};
  ck_assert_int_eq(ERROR_INIT, s21_mult_number(&A, number, &result));
}

START_TEST(s21_mult_number_null2) {
  double number = 10;
  matrix_t result;
  ck_assert_int_eq(ERROR_INIT, s21_mult_number(NULL, number, &result));
}
END_TEST

START_TEST(s21_mult_number_null3) {
  double number = 10;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(ERROR_INIT, s21_mult_number(&A, number, &result));
}

START_TEST(s21_mult_number_null4) {
  double number = 10;
  matrix_t A = {0}, result = {0};
  A.rows = A.columns = 8;
  ck_assert_int_eq(ERROR_INIT,
                   s21_mult_number(&A, number, &result));  // ERROR_INIT
}

START_TEST(s21_mult_number_zero) {
  double number = 0;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(OK, s21_mult_number(&A, number, &result));
  ck_assert_ldouble_eq_tol(0, result.matrix[0][0], 1e-06);
  ck_assert_ldouble_eq_tol(0, result.matrix[0][1], 1e-06);
  ck_assert_ldouble_eq_tol(0, result.matrix[1][0], 1e-06);
  ck_assert_ldouble_eq_tol(0, result.matrix[1][1], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(s21_mult_number_test0) {
  double number = 8;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(OK, s21_mult_number(&A, number, &result));
  ck_assert_ldouble_eq_tol(0, result.matrix[0][0], 1e-06);
  ck_assert_ldouble_eq_tol(0, result.matrix[0][1], 1e-06);
  ck_assert_ldouble_eq_tol(0, result.matrix[1][0], 1e-06);
  ck_assert_ldouble_eq_tol(0, result.matrix[1][1], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test1) {
  double number = 46.75757000000000001;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.57576575;
  A.matrix[0][1] = 87626456.5;
  A.matrix[1][0] = -45698.765699876;
  A.matrix[1][1] = 5687647;
  ck_assert_int_eq(OK, s21_mult_number(&A, number, &result));
  ck_assert_ldouble_eq_tol(number * A.matrix[0][0], result.matrix[0][0], 1e-06);
  ck_assert_ldouble_eq_tol(number * A.matrix[0][1], result.matrix[0][1], 1e-06);
  ck_assert_ldouble_eq_tol(number * A.matrix[1][0], result.matrix[1][0], 1e-06);
  ck_assert_ldouble_eq_tol(number * A.matrix[1][1], result.matrix[1][1], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(s21_mult_number_test2) {
  double number = 0.1;
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 1, &A);
  A.matrix[0][0] = 0.0000000000000001;
  A.matrix[1][0] = 4564.66436563;
  A.matrix[2][0] = 1.000001;
  ck_assert_int_eq(OK, s21_mult_number(&A, number, &result));
  ck_assert_ldouble_eq_tol(number * A.matrix[0][0], result.matrix[0][0], 1e-06);
  ck_assert_ldouble_eq_tol(number * A.matrix[1][0], result.matrix[1][0], 1e-06);
  ck_assert_ldouble_eq_tol(number * A.matrix[2][0], result.matrix[2][0], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

Suite *suite_mult_number(void) {
  Suite *s = suite_create("suite_mult_number");
  TCase *tc = tcase_create("case_mult_number");

  tcase_add_test(tc, mult_number_1);
  tcase_add_test(tc, mult_number_2);
  tcase_add_test(tc, mult_number_3);
  tcase_add_test(tc, s21_mult_number_null);
  tcase_add_test(tc, s21_mult_number_null2);
  tcase_add_test(tc, s21_mult_number_null3);
  tcase_add_test(tc, s21_mult_number_null4);  ///
  tcase_add_test(tc, s21_mult_number_zero);
  tcase_add_test(tc, s21_mult_number_test0);
  tcase_add_test(tc, s21_mult_number_test1);
  tcase_add_test(tc, s21_mult_number_test2);

  suite_add_tcase(s, tc);
  return s;
}