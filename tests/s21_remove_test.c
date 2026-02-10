#include "s21_matrix_test.h"

START_TEST(s21_remove_1) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_2) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(1, 1, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_3) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_4) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 4, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

START_TEST(s21_remove_5) {
  int res = 0;
  matrix_t A = {0};

  res = s21_create_matrix(3, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    res = ERROR_INIT;
  }
  ck_assert_int_eq(res, OK);
}
END_TEST

Suite *suite_remove_matrix(void) {
  Suite *s = suite_create("suite_remove_matrix");
  TCase *tc = tcase_create("case_remove_matrix");

  tcase_add_test(tc, s21_remove_1);
  tcase_add_test(tc, s21_remove_2);
  tcase_add_test(tc, s21_remove_3);
  tcase_add_test(tc, s21_remove_4);
  tcase_add_test(tc, s21_remove_5);

  suite_add_tcase(s, tc);
  return s;
}