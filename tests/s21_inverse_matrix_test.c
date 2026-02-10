#include "s21_matrix_test.h"

START_TEST(inverse_matrix_1) {
  ck_assert_int_eq(s21_inverse_matrix(NULL, NULL), ERROR_INIT);
}
END_TEST

START_TEST(inverse_matrix_2) {
  ck_assert_int_eq(s21_inverse_matrix((void *)0, (void *)0), ERROR_INIT);
}
END_TEST

START_TEST(inverse_matrix_3) {
  matrix_t A = {0}, result = {0}, result_true = {0};
  int rows = 3, columns = 3;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &result_true);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  result_true.matrix[0][0] = 1;
  result_true.matrix[0][1] = -1;
  result_true.matrix[0][2] = 1;
  result_true.matrix[1][0] = -38;
  result_true.matrix[1][1] = 41;
  result_true.matrix[1][2] = -34;
  result_true.matrix[2][0] = 27;
  result_true.matrix[2][1] = -29;
  result_true.matrix[2][2] = 24;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &result_true), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result_true);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(inverse_matrix_4) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 6;
  A.matrix[0][2] = 9;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 1;
  matrix_t res;
  int return_value = s21_inverse_matrix(&A, &res);
  ck_assert_int_eq(return_value, OK);
  matrix_t C;
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1;
  C.matrix[0][1] = -6;
  C.matrix[0][2] = 27;
  C.matrix[1][0] = 0.0;
  C.matrix[1][1] = 1;
  C.matrix[1][2] = -6;
  C.matrix[2][0] = 0;
  C.matrix[2][1] = 0.0;
  C.matrix[2][2] = 1;
  if (return_value == OK) return_value = s21_eq_matrix(&res, &C);
  ck_assert_int_eq(return_value, SUCCESS);
  s21_remove_matrix(&C);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(s21_inverse_matrix_null) {
  matrix_t A = {0}, result = {0};
  ck_assert_int_eq(ERROR_INIT, s21_inverse_matrix(&A, &result));
}

START_TEST(s21_inverse_matrix_null2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(ERROR_INIT, s21_inverse_matrix(&A, &result));
}

START_TEST(s21_inverse_matrix_det) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(ERROR_CALC, s21_inverse_matrix(&A, &result));
  s21_remove_matrix(&A);
}

START_TEST(s21_inverse_matrix_det2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 2, &A);
  ck_assert_int_eq(ERROR_CALC, s21_inverse_matrix(&A, &result));
  s21_remove_matrix(&A);
}

START_TEST(s21_inverse_matrix_rows) {
  matrix_t A = {0}, result = {0};
  A.rows = A.columns = 8;
  ck_assert_int_eq(ERROR_INIT, s21_inverse_matrix(&A, &result));
}

START_TEST(s21_inverse_matrix_test1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = -6575.456343;
  ck_assert_int_eq(OK, s21_inverse_matrix(&A, &result));

  ck_assert_ldouble_eq_tol(result.matrix[0][0], -0.000152080699473363, 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 0;
  A.matrix[1][0] = 6564.53;
  A.matrix[1][1] = -9.54;
  ck_assert_int_eq(OK, s21_inverse_matrix(&A, &result));

  ck_assert_ldouble_eq_tol(result.matrix[0][0], 0.200000000000000, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][1], 0, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][0], 137.621174004193, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][1], -0.104821802935010, 1e-06);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test3) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0.64454;
  A.matrix[0][1] = 65.4534356;
  A.matrix[0][2] = -6.666;
  A.matrix[1][0] = 0.1;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 17;
  A.matrix[2][0] = 0.88;
  A.matrix[2][1] = -0.0000001;
  A.matrix[2][2] = 88;
  ck_assert_int_eq(OK, s21_inverse_matrix(&A, &result));

  ck_assert_ldouble_eq_tol(result.matrix[0][0], 0.188930901137859, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][1], -12.3661763301536, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][2], 2.40323194317724, 1e-06);

  ck_assert_ldouble_eq_tol(result.matrix[1][0], 0.0132251628241640, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][1], 0.134367654293507, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][2], -0.0249555816773152, 1e-06);

  ck_assert_ldouble_eq_tol(result.matrix[2][0], -0.00188930899635000, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[2][1], 0.123661763454227, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[2][2], -0.0126686830964946, 1e-06);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_inverse_matrix(void) {
  Suite *s = suite_create("suite_inverse_matrix");
  TCase *tc = tcase_create("case_inverse_matrix");

  tcase_add_test(tc, inverse_matrix_1);
  tcase_add_test(tc, inverse_matrix_2);
  tcase_add_test(tc, inverse_matrix_3);
  tcase_add_test(tc, inverse_matrix_4);

  tcase_add_test(tc, s21_inverse_matrix_null);
  tcase_add_test(tc, s21_inverse_matrix_null2);
  tcase_add_test(tc, s21_inverse_matrix_det);
  tcase_add_test(tc, s21_inverse_matrix_det2);
  tcase_add_test(tc, s21_inverse_matrix_rows);
  tcase_add_test(tc, s21_inverse_matrix_test1);
  tcase_add_test(tc, s21_inverse_matrix_test2);
  tcase_add_test(tc, s21_inverse_matrix_test3);

  suite_add_tcase(s, tc);
  return s;
}