#include "s21_matrix_test.h"

START_TEST(sub_matrix) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), ERROR_INIT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 2, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, (void *)0), ERROR_INIT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 2, &B);
  int answer = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(answer, ERROR_CALC);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

//  проверка рандомными числами в матрицах 5 на 5
START_TEST(sub_matrix_3) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = INFINITY;
  B.matrix[0][0] = INFINITY;
  int answer = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(answer, ERROR_INIT);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_test_empty) {
  matrix_t A = {0}, B = {0}, result = {0};
  ck_assert_int_eq(ERROR_INIT, s21_sub_matrix(&A, &B, &result));
}

START_TEST(s21_sub_test_empty2) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);
  ck_assert_int_eq(ERROR_INIT, s21_sub_matrix(&A, &B, &result));
}

START_TEST(s21_sub_test_columns) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 2, &B);
  ck_assert_int_eq(ERROR_CALC, s21_sub_matrix(&A, &B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_sub_test_rows) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(1, 2, &B);
  ck_assert_int_eq(ERROR_CALC, s21_sub_matrix(&A, &B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}

START_TEST(s21_sub_test_nulls) {
  matrix_t A = {0}, B = {0}, result = {0};
  A.rows = A.columns = B.rows = B.columns = 8;
  ck_assert_int_eq(ERROR_INIT, s21_sub_matrix(&A, &B, &result));
}

START_TEST(s21_sub_test_Anull) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;
  ck_assert_int_eq(ERROR_INIT, s21_sub_matrix(&A, &B, &result));
  s21_remove_matrix(&B);
}

START_TEST(s21_sub_test_Bnull) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(ERROR_INIT, s21_sub_matrix(&A, &B, &result));
  s21_remove_matrix(&A);
}

START_TEST(s21_sub_test1) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  A.matrix[0][0] = 9668.9786796878867;
  B.matrix[0][0] = 97.689698767;
  ck_assert_int_eq(OK, s21_sub_matrix(&A, &B, &result));
  ck_assert_ldouble_eq_tol(A.matrix[0][0] - B.matrix[0][0], result.matrix[0][0],
                           1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_test2) {
  matrix_t A = {0}, B = {0}, result = {0}, test_result = {0};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &result);

  result.matrix[0][0] = A.matrix[0][0] = B.matrix[0][0] = 0.1;
  B.matrix[0][0] += result.matrix[0][0];
  result.matrix[0][1] = A.matrix[0][1] = B.matrix[0][1] = 8.8;
  B.matrix[0][1] += result.matrix[0][1];
  result.matrix[1][0] = A.matrix[1][0] = B.matrix[1][0] = 534.454356;
  B.matrix[1][0] += result.matrix[1][0];
  result.matrix[1][1] = A.matrix[1][1] = B.matrix[1][1] = 5.3;
  B.matrix[1][1] += result.matrix[1][1];
  result.matrix[2][0] = A.matrix[2][0] = B.matrix[2][0] = 87677.956785644;
  B.matrix[2][0] += result.matrix[2][0];
  result.matrix[2][1] = A.matrix[2][1] = B.matrix[2][1] = 567347.345774555;
  B.matrix[2][1] += result.matrix[2][1];

  ck_assert_int_eq(OK, s21_sub_matrix(&B, &A, &test_result));
  ck_assert_int_eq(SUCCESS, s21_eq_matrix(&result, &test_result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}
END_TEST

START_TEST(s21_sub_test3) {
  matrix_t A = {0}, B = {0}, result = {0}, test_result = {0};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &result);

  A.matrix[0][0] = 0;
  B.matrix[0][0] = 0.1;
  result.matrix[0][0] = A.matrix[0][0] - B.matrix[0][0];

  A.matrix[0][1] = 0.00000000032324;
  B.matrix[0][1] = 0.1;
  result.matrix[0][1] = A.matrix[0][1] - B.matrix[0][1];

  A.matrix[1][0] = 0.00000000032324;
  B.matrix[1][0] = 0.00000000012324;
  result.matrix[1][0] = A.matrix[1][0] - B.matrix[1][0];

  A.matrix[1][1] = -75647.453236;
  B.matrix[1][1] = 45.45;
  result.matrix[1][1] = A.matrix[1][1] - B.matrix[1][1];

  A.matrix[2][0] = -0.7876786;
  B.matrix[2][0] = -7687.65786567;
  result.matrix[2][0] = A.matrix[2][0] - B.matrix[2][0];

  A.matrix[2][1] = 74.55445;
  B.matrix[2][1] = 567.8909876545678908765;
  result.matrix[2][1] = A.matrix[2][1] - B.matrix[2][1];

  ck_assert_int_eq(OK, s21_sub_matrix(&A, &B, &test_result));
  ck_assert_int_eq(SUCCESS, s21_eq_matrix(&result, &test_result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}
END_TEST

Suite *suite_sub_matrix(void) {
  Suite *s = suite_create("suite_sub_matrix");
  TCase *tc = tcase_create("case_sub_matrix");

  tcase_add_test(tc, sub_matrix);
  tcase_add_test(tc, sub_matrix_1);
  tcase_add_test(tc, sub_matrix_2);
  tcase_add_test(tc, sub_matrix_3);
  tcase_add_test(tc, sub_matrix_4);
  tcase_add_test(tc, s21_sub_test_empty);
  tcase_add_test(tc, s21_sub_test_empty2);
  tcase_add_test(tc, s21_sub_test_columns);
  tcase_add_test(tc, s21_sub_test_rows);
  tcase_add_test(tc, s21_sub_test_nulls);  //
  tcase_add_test(tc, s21_sub_test_Anull);
  tcase_add_test(tc, s21_sub_test_Bnull);
  tcase_add_test(tc, s21_sub_test1);
  tcase_add_test(tc, s21_sub_test2);
  tcase_add_test(tc, s21_sub_test3);

  suite_add_tcase(s, tc);
  return s;
}