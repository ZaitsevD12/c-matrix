#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>
#include <unistd.h>

#include "../s21_matrix.h"

#define OK 0
#define ERROR_INIT 1
#define ERROR_CALC 2
#define MAX_DOUBLE 1.79769e+308
#define MIN_DOUBLE 2.22507e-308

Suite *suite_create_matrix(void);
Suite *suite_remove_matrix(void);
Suite *suite_eq_matrix(void);
Suite *suite_sum_matrix(void);
Suite *suite_sub_matrix(void);
Suite *suite_mult_number(void);
Suite *suite_mult_matrix(void);
Suite *suite_transpose(void);
Suite *suite_determinant(void);
Suite *suite_calc_complements(void);
Suite *suite_inverse_matrix(void);

typedef struct {
  int fails;
} fail;

void run_tests(fail *fails);
void run_testcase(Suite *testcase, fail *fails);

#endif