#include "s21_matrix_test.h"

START_TEST(determinant_1) {
  matrix_t A = {0};
  double result = 0.;
  ck_assert_int_eq(s21_determinant(&A, &result), ERROR_INIT);
}
END_TEST

START_TEST(determinant_2) {
  //   matrix_t A = {0};
  double result = 0.;
  ck_assert_int_eq(s21_determinant(NULL, &result), ERROR_INIT);
}
END_TEST

START_TEST(determinant_3) {
  //   matrix_t A = {0};
  double result = 0.;
  ck_assert_int_eq(s21_determinant((void *)0, &result), ERROR_INIT);
}
END_TEST

START_TEST(determinant_4) {
  matrix_t A = {0};
  s21_create_matrix(4, 4, &A);
  double result = 0;
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 6;
  A.matrix[1][2] = 7;
  A.matrix[1][3] = 8;
  A.matrix[2][0] = 9;
  A.matrix[2][1] = 10;
  A.matrix[2][2] = 11;
  A.matrix[2][3] = 12;
  A.matrix[3][0] = 13;
  A.matrix[3][1] = 14;
  A.matrix[3][2] = 15;
  A.matrix[3][3] = 16;
  int answer = s21_determinant(&A, &result);
  ck_assert_int_eq(answer, 0);
  ck_assert_double_eq(result, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_5) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  double result = 0;
  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 3.;
  A.matrix[1][0] = 4.;
  A.matrix[1][1] = 5.;
  A.matrix[1][2] = 6.;
  A.matrix[2][0] = 7.;
  A.matrix[2][1] = 8.;
  A.matrix[2][2] = 9.;
  int answer = s21_determinant(&A, &result);
  ck_assert_int_eq(answer, 0);
  ck_assert_double_eq(result, 0.);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_null0) {
  matrix_t A = {0};
  double result;
  ck_assert_int_eq(ERROR_INIT, s21_determinant(&A, &result));
}

START_TEST(s21_determinant_null1) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(ERROR_INIT, s21_determinant(&A, &result));
}

START_TEST(s21_determinant_test1) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(OK, s21_determinant(&A, &result));
  ck_assert_int_eq(0, result);
  s21_remove_matrix(&A);
}

START_TEST(s21_determinant_notsquare) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(2, 1, &A);
  ck_assert_int_eq(ERROR_CALC, s21_determinant(&A, &result));
  s21_remove_matrix(&A);
}

START_TEST(s21_determinant_notsquare2) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(8, 7, &A);
  ck_assert_int_eq(ERROR_CALC, s21_determinant(&A, &result));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test2) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = -6575.456343;
  ck_assert_int_eq(OK, s21_determinant(&A, &result));
  ck_assert_double_eq_tol(result, A.matrix[0][0], 1e-06);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_nulls) {
  matrix_t A = {0};
  double result;
  A.rows = A.columns = 5;
  ck_assert_int_eq(ERROR_INIT, s21_determinant(&A, &result));
}

START_TEST(s21_determinant_test3) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(OK, s21_determinant(&A, &result));
  ck_assert_ldouble_eq_tol(
      A.matrix[0][0] * A.matrix[1][1] - (A.matrix[0][1] * A.matrix[1][0]),
      result, 1e-06);

  s21_remove_matrix(&A);
}

START_TEST(s21_determinant_test4) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = -76.576;
  A.matrix[0][1] = 6.45645;
  A.matrix[0][2] = 876.54567897655678;
  A.matrix[1][0] = 0.000000001;
  A.matrix[1][1] = -1.111111111;
  A.matrix[1][2] = 393.93;
  A.matrix[2][0] = 1.2345;
  A.matrix[2][1] = -1.11111111199;
  A.matrix[2][2] = 0.87645678765;
  double test_result = A.matrix[0][0] * A.matrix[1][1] * A.matrix[2][2] +
                       A.matrix[0][1] * A.matrix[1][2] * A.matrix[2][0] +
                       A.matrix[0][2] * A.matrix[1][0] * A.matrix[2][1] -
                       (A.matrix[0][2] * A.matrix[1][1] * A.matrix[2][0]) -
                       (A.matrix[0][0] * A.matrix[1][2] * A.matrix[2][1]) -
                       (A.matrix[0][1] * A.matrix[1][0] * A.matrix[2][2]);
  ck_assert_int_eq(OK, s21_determinant(&A, &result));
  ck_assert_ldouble_eq_tol(test_result, result, 1e-06);
  s21_remove_matrix(&A);
}

START_TEST(s21_determinant_test5) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 47545;
  A.matrix[0][1] = 3.66564577;
  A.matrix[0][2] = -10;
  A.matrix[0][3] = 0.643;
  A.matrix[1][0] = 765789.01;
  A.matrix[1][1] = -99.999999999;
  A.matrix[1][2] = 0.0000000005646;
  A.matrix[1][3] = 5.55757435;
  A.matrix[2][0] = 1.867546867;
  A.matrix[2][1] = -1.7657868;
  A.matrix[2][2] = 0.87988678;
  A.matrix[2][3] = 8.8687678877;
  A.matrix[3][0] = -1.867546867;
  A.matrix[3][1] = 1.7657868;
  A.matrix[3][2] = -0.87988678;
  A.matrix[3][3] = -8.8687678877;

  ck_assert_int_eq(OK, s21_determinant(&A, &result));
  ck_assert_ldouble_eq_tol(0, result, 1e-06);
  s21_remove_matrix(&A);
}

Suite *suite_determinant(void) {
  Suite *s = suite_create("suite_determinant");
  TCase *tc = tcase_create("case_determinant");
  tcase_add_test(tc, determinant_1);
  tcase_add_test(tc, determinant_2);
  tcase_add_test(tc, determinant_3);
  tcase_add_test(tc, determinant_4);
  tcase_add_test(tc, determinant_5);

  tcase_add_test(tc, s21_determinant_null0);
  tcase_add_test(tc, s21_determinant_null1);
  tcase_add_test(tc, s21_determinant_test1);
  tcase_add_test(tc, s21_determinant_notsquare);
  tcase_add_test(tc, s21_determinant_notsquare2);
  tcase_add_test(tc, s21_determinant_test2);
  tcase_add_test(tc, s21_determinant_nulls);
  tcase_add_test(tc, s21_determinant_test3);
  tcase_add_test(tc, s21_determinant_test4);
  tcase_add_test(tc, s21_determinant_test5);

  suite_add_tcase(s, tc);
  return s;
}