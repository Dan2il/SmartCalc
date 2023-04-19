#include "tests.h"

START_TEST(CreditCalculation_1) {
  struct DataCredit data_credit = {.credit_type = ANNUITY,
                                   .interest_rate = 0.10,
                                   .term_in_months = 60,
                                   .total_credit_amount = 1000000};
  struct PaymentCredit data_payment = {
      .monthly_payment = 0, .overpayment_on_credit = 0, .total_payment = 0};
  data_payment.monthly_payment =
      (double *)malloc(data_credit.term_in_months * sizeof(double));
  ErrorsType errors = CreditCalculation(&data_credit, &data_payment);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_double_eq_tol(data_payment.monthly_payment[0], 21247.04, 0.01);
  ck_assert_double_eq_tol(data_payment.overpayment_on_credit, 274822.40, 0.01);
  ck_assert_double_eq_tol(data_payment.total_payment, 1274822.40, 0.01);
  free(data_payment.monthly_payment);
}
END_TEST

START_TEST(CreditCalculation_2) {
  struct DataCredit data_credit = {.credit_type = ANNUITY,
                                   .interest_rate = 0.075,
                                   .term_in_months = 12,
                                   .total_credit_amount = 100000};
  struct PaymentCredit data_payment = {
      .monthly_payment = 0, .overpayment_on_credit = 0, .total_payment = 0};
  data_payment.monthly_payment =
      (double *)malloc(data_credit.term_in_months * sizeof(double));
  ErrorsType errors = CreditCalculation(&data_credit, &data_payment);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_double_eq_tol(data_payment.monthly_payment[0], 8675.74, 0.01);
  ck_assert_double_eq_tol(data_payment.overpayment_on_credit, 4108.88, 0.01);
  ck_assert_double_eq_tol(data_payment.total_payment, 104108.88, 0.01);
  free(data_payment.monthly_payment);
}
END_TEST

START_TEST(CreditCalculation_3) {
  struct DataCredit data_credit = {.credit_type = ANNUITY,
                                   .interest_rate = 0.02,
                                   .term_in_months = 125,
                                   .total_credit_amount = 1000000000};
  struct PaymentCredit data_payment = {
      .monthly_payment = 0, .overpayment_on_credit = 0, .total_payment = 0};
  data_payment.monthly_payment =
      (double *)malloc(data_credit.term_in_months * sizeof(double));
  ErrorsType errors = CreditCalculation(&data_credit, &data_payment);
  ck_assert_int_eq(errors, NO_ERRORS);
  ck_assert_double_eq_tol(data_payment.monthly_payment[0], 8868888.39, 0.01);
  ck_assert_double_eq_tol(data_payment.overpayment_on_credit, 108611048.75,
                          0.01);
  ck_assert_double_eq_tol(data_payment.total_payment, 1108611048.75, 0.01);
  free(data_payment.monthly_payment);
}
END_TEST

START_TEST(CreditCalculation_4) {
  struct DataCredit data_credit = {.credit_type = DIFFERENTIATED,
                                   .interest_rate = 0.10,
                                   .term_in_months = 6,
                                   .total_credit_amount = 100000};
  struct PaymentCredit data_payment = {
      .monthly_payment = 0, .overpayment_on_credit = 0, .total_payment = 0};
  data_payment.monthly_payment =
      (double *)malloc(data_credit.term_in_months * sizeof(double));
  ErrorsType errors = CreditCalculation(&data_credit, &data_payment);
  ck_assert_int_eq(errors, NO_ERRORS);

  ck_assert_double_eq_tol(data_payment.monthly_payment[0], 17515.99, 0.001);
  ck_assert_double_eq_tol(data_payment.monthly_payment[1], 17305.94, 0.001);
  ck_assert_double_eq_tol(data_payment.monthly_payment[2], 17232.88, 0.001);
  ck_assert_double_eq_tol(data_payment.monthly_payment[3], 17077.63, 0.001);
  ck_assert_double_eq_tol(data_payment.monthly_payment[4], 16949.77, 0.001);
  ck_assert_double_eq_tol(data_payment.monthly_payment[5], 16803.64, 0.001);

  ck_assert_double_eq_tol(data_payment.total_payment, 102885.85, 0.001);
  ck_assert_double_eq_tol(data_payment.overpayment_on_credit, 2885.85, 0.001);

  free(data_payment.monthly_payment);
}
END_TEST

START_TEST(CreditCalculation_5) {
  struct DataCredit data_credit = {.credit_type = DIFFERENTIATED,
                                   .interest_rate = 0.10,
                                   .term_in_months = 12,
                                   .total_credit_amount = 100000};
  struct PaymentCredit data_payment = {
      .monthly_payment = 0, .overpayment_on_credit = 0, .total_payment = 0};
  data_payment.monthly_payment =
      (double *)malloc(data_credit.term_in_months * sizeof(double));
  ErrorsType errors = CreditCalculation(&data_credit, &data_payment);
  ck_assert_int_eq(errors, NO_ERRORS);

  free(data_payment.monthly_payment);
}
END_TEST

void StartTestsCreditCalculator() {
  Suite *suite = suite_create("Tests_Credit_Calculator");
  TCase *getCase = tcase_create("Core");
  SRunner *runner = srunner_create(suite);

  suite_add_tcase(suite, getCase);

  tcase_add_test(getCase, CreditCalculation_1);
  tcase_add_test(getCase, CreditCalculation_2);
  tcase_add_test(getCase, CreditCalculation_3);
  tcase_add_test(getCase, CreditCalculation_4);
  tcase_add_test(getCase, CreditCalculation_5);

  srunner_run_all(runner, CK_ENV);
  srunner_free(runner);
}