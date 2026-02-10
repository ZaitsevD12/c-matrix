#include "s21_matrix_test.h"

START_TEST(calc_complements_1) {
  matrix_t A = {0}, result = {0};
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = i + j / 3.3;
    }
  }
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_2) {
  matrix_t result = {0};
  ck_assert_int_eq(s21_calc_complements(NULL, &result), ERROR_INIT);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_3) {
  matrix_t result = {0};
  ck_assert_int_eq(s21_calc_complements((void *)0, &result), ERROR_INIT);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_4) {
  matrix_t A = {0}, result = {0}, result_true = {0};
  int rows = 3, columns = 3;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &result_true);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  result_true.matrix[0][0] = 0;
  result_true.matrix[0][1] = 10;
  result_true.matrix[0][2] = -20;
  result_true.matrix[1][0] = 4;
  result_true.matrix[1][1] = -14;
  result_true.matrix[1][2] = 8;
  result_true.matrix[2][0] = -8;
  result_true.matrix[2][1] = -2;
  result_true.matrix[2][2] = 4;
  s21_calc_complements(&A, &result);
  ck_assert_int_eq(s21_eq_matrix(&result, &result_true), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result_true);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_null) {
  matrix_t A = {0}, result = {0};
  ck_assert_int_eq(ERROR_INIT, s21_calc_complements(&A, &result));
}

START_TEST(s21_calc_complements_null2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(ERROR_INIT, s21_calc_complements(&A, &result));
}

START_TEST(s21_calc_complements_test1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(OK, s21_calc_complements(&A, &result));
  ck_assert_ldouble_eq_tol(1, result.matrix[0][0], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(s21_calc_complements_test_rows) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 2, &A);
  ck_assert_int_eq(ERROR_CALC, s21_calc_complements(&A, &result));
  s21_remove_matrix(&A);
}

START_TEST(s21_calc_complements_nulls) {
  matrix_t A = {0}, result = {0};
  A.rows = A.columns = 8;
  ck_assert_int_eq(ERROR_INIT, s21_calc_complements(&A, &result));
}

START_TEST(s21_calc_complements_test2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = -6575.456343;
  ck_assert_int_eq(OK, s21_calc_complements(&A, &result));

  ck_assert_ldouble_eq_tol(1, result.matrix[0][0], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test3) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  ck_assert_int_eq(OK, s21_calc_complements(&A, &result));
  ck_assert_ldouble_eq_tol(result.matrix[0][0], A.matrix[1][1], 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][1], -A.matrix[1][0], 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][0], -A.matrix[0][1], 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][1], A.matrix[0][0], 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(s21_calc_complements_test4) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  ck_assert_int_eq(OK, s21_calc_complements(&A, &result));
  ck_assert_ldouble_eq_tol(result.matrix[0][0], 0, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][1], 0, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][0], 0, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][1], 0, 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(s21_calc_complements_test5) {
  matrix_t A = {0}, result = {0};
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
  ck_assert_int_eq(OK, s21_calc_complements(&A, &result));
  ck_assert_ldouble_eq_tol(result.matrix[0][0], 436.726159471151, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][1], 486.306584999124, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][2], 1.37166666541839, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][0], -979.59844350429432, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][1], -1149.2111956676457, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][2], -77.1139569867462, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[2][0], 3517.3289917098917, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[2][1], 30165.583680876545, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[2][2], 85.0844444294795, 1e-06);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(s21_calc_complements_test6) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 3.66564577;
  A.matrix[0][2] = -10;
  A.matrix[0][3] = 0.643;
  A.matrix[1][0] = 0.01;
  A.matrix[1][1] = -0.9;
  A.matrix[1][2] = 0.0000000005646;
  A.matrix[1][3] = 5.55757435;
  A.matrix[2][0] = 1.867;
  A.matrix[2][1] = -1.7;
  A.matrix[2][2] = 0.87988678;
  A.matrix[2][3] = 8.8687678877;
  A.matrix[3][0] = -1.867546867;
  A.matrix[3][1] = 1.7657868;
  A.matrix[3][2] = -0.87988678;
  A.matrix[3][3] = -8.8687678877;
  ck_assert_int_eq(OK, s21_calc_complements(&A, &result));
  ck_assert_ldouble_eq_tol(result.matrix[0][0], -0.321699833115385, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][1], -0.00267419942353712, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][2], 0.675967087634449, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[0][3], 0.000145786348016985, 1e-06);

  ck_assert_ldouble_eq_tol(result.matrix[1][0], 5.87169860634816, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][1], 0.0488097642955267, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][2], 2.27319192970328, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[1][3], -1.45224639873153, 1e-06);

  ck_assert_ldouble_eq_tol(result.matrix[2][0], 0.118327686999265, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[2][1], -122.457915972232, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[2][2], -46.1165485501433, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[2][3], -19.8311890556789, 1e-06);

  ck_assert_ldouble_eq_tol(result.matrix[3][0], 3.77447800950895, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[3][1], -122.427523432112, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[3][2], -44.6430541297268, 1e-06);
  ck_assert_ldouble_eq_tol(result.matrix[3][3], -19.8328459328286, 1e-06);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

Suite *suite_calc_complements(void) {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc = tcase_create("case_calc_complements");
  tcase_add_test(tc, calc_complements_1);
  tcase_add_test(tc, calc_complements_2);
  tcase_add_test(tc, calc_complements_3);
  tcase_add_test(tc, calc_complements_4);

  tcase_add_test(tc, s21_calc_complements_null);
  tcase_add_test(tc, s21_calc_complements_null2);
  tcase_add_test(tc, s21_calc_complements_test1);
  tcase_add_test(tc, s21_calc_complements_test_rows);
  tcase_add_test(tc, s21_calc_complements_nulls);
  tcase_add_test(tc, s21_calc_complements_test2);
  tcase_add_test(tc, s21_calc_complements_test3);
  tcase_add_test(tc, s21_calc_complements_test4);
  tcase_add_test(tc, s21_calc_complements_test5);
  tcase_add_test(tc, s21_calc_complements_test6);

  suite_add_tcase(s, tc);

  return s;
}
