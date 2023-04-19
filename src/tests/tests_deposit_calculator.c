#include "tests.h"

START_TEST(DepositCalculation_1) {
  struct DataDeposit data_deposit;

  data_deposit.deposit_amount = 100000;
  data_deposit.deposit_term_in_month = 24;
  data_deposit.interest_rate = 10;
  data_deposit.periodicity_of_payments = LATE;
  data_deposit.capitalization_of_interest = DISABLE;
  data_deposit.period_deposits_or_withdrawals = LATE;
  data_deposit.deposits = 0;
  data_deposit.withdrawals = 0;

  struct DepositProfitability deposit_profitability = {
      .accrued_interest = 0, .deposit_amount = 0, .tax_amount = 0};

  ErrorsType errors = NO_ERRORS;
  errors = DepositCalculation(&data_deposit, &deposit_profitability);
  ck_assert_int_eq(errors, NO_ERRORS);
}

START_TEST(DepositCalculation_2) {
  struct DataDeposit data_deposit;

  data_deposit.deposit_amount = 100000;
  data_deposit.deposit_term_in_month = 24;
  data_deposit.interest_rate = 10;
  data_deposit.periodicity_of_payments = MONTHLY;
  data_deposit.capitalization_of_interest = ENABLE;
  data_deposit.period_deposits_or_withdrawals = LATE;
  data_deposit.deposits = 0;
  data_deposit.withdrawals = 0;

  struct DepositProfitability deposit_profitability = {
      .accrued_interest = 0, .deposit_amount = 0, .tax_amount = 0};

  ErrorsType errors = NO_ERRORS;
  errors = DepositCalculation(&data_deposit, &deposit_profitability);
  ck_assert_int_eq(errors, NO_ERRORS);
}

START_TEST(DepositCalculation_3) {
  struct DataDeposit data_deposit;

  data_deposit.deposit_amount = 100000;
  data_deposit.deposit_term_in_month = 24;
  data_deposit.interest_rate = 10;
  data_deposit.periodicity_of_payments = QUARTERLY;
  data_deposit.capitalization_of_interest = ENABLE;
  data_deposit.period_deposits_or_withdrawals = LATE;
  data_deposit.deposits = 0;
  data_deposit.withdrawals = 0;

  struct DepositProfitability deposit_profitability = {
      .accrued_interest = 0, .deposit_amount = 0, .tax_amount = 0};

  ErrorsType errors = NO_ERRORS;
  errors = DepositCalculation(&data_deposit, &deposit_profitability);
  ck_assert_int_eq(errors, NO_ERRORS);
}

START_TEST(DepositCalculation_4) {
  struct DataDeposit data_deposit;

  data_deposit.deposit_amount = 100000;
  data_deposit.deposit_term_in_month = 24;
  data_deposit.interest_rate = 10;
  data_deposit.periodicity_of_payments = ANNUALLY;
  data_deposit.capitalization_of_interest = ENABLE;
  data_deposit.period_deposits_or_withdrawals = LATE;
  data_deposit.deposits = 0;
  data_deposit.withdrawals = 0;

  struct DepositProfitability deposit_profitability = {
      .accrued_interest = 0, .deposit_amount = 0, .tax_amount = 0};

  ErrorsType errors = NO_ERRORS;
  errors = DepositCalculation(&data_deposit, &deposit_profitability);
  ck_assert_int_eq(errors, NO_ERRORS);
}

START_TEST(DepositCalculation_5) {
  struct DataDeposit data_deposit;

  data_deposit.deposit_amount = 100000;
  data_deposit.deposit_term_in_month = 24;
  data_deposit.interest_rate = 10;
  data_deposit.periodicity_of_payments = ANNUALLY;
  data_deposit.capitalization_of_interest = ENABLE;
  data_deposit.period_deposits_or_withdrawals = QUARTERLY;
  data_deposit.deposits = 0;
  data_deposit.withdrawals = 0;

  struct DepositProfitability deposit_profitability = {
      .accrued_interest = 0, .deposit_amount = 0, .tax_amount = 0};

  ErrorsType errors = NO_ERRORS;
  errors = DepositCalculation(&data_deposit, &deposit_profitability);
  ck_assert_int_eq(errors, NO_ERRORS);
}

START_TEST(DepositCalculation_6) {
  struct DataDeposit data_deposit;

  data_deposit.deposit_amount = 100000;
  data_deposit.deposit_term_in_month = 24;
  data_deposit.interest_rate = 10;
  data_deposit.periodicity_of_payments = MONTHLY;
  data_deposit.capitalization_of_interest = ENABLE;
  data_deposit.period_deposits_or_withdrawals = MONTHLY;
  data_deposit.deposits = 0;
  data_deposit.withdrawals = 0;

  struct DepositProfitability deposit_profitability = {
      .accrued_interest = 0, .deposit_amount = 0, .tax_amount = 0};

  ErrorsType errors = NO_ERRORS;
  errors = DepositCalculation(&data_deposit, &deposit_profitability);
  ck_assert_int_eq(errors, NO_ERRORS);
}

START_TEST(DepositCalculation_7) {
  struct DataDeposit data_deposit;

  data_deposit.deposit_amount = 100000;
  data_deposit.deposit_term_in_month = 24;
  data_deposit.interest_rate = 10;
  data_deposit.periodicity_of_payments = ANNUALLY;
  data_deposit.capitalization_of_interest = ENABLE;
  data_deposit.period_deposits_or_withdrawals = ANNUALLY;
  data_deposit.deposits = 0;
  data_deposit.withdrawals = 0;

  struct DepositProfitability deposit_profitability = {
      .accrued_interest = 0, .deposit_amount = 0, .tax_amount = 0};

  ErrorsType errors = NO_ERRORS;
  errors = DepositCalculation(&data_deposit, &deposit_profitability);
  ck_assert_int_eq(errors, NO_ERRORS);
}

void StartTestsDepositCalculator() {
  Suite *suite = suite_create("Tests_Deposit_Calculator");
  TCase *getCase = tcase_create("Core");
  SRunner *runner = srunner_create(suite);

  suite_add_tcase(suite, getCase);

  tcase_add_test(getCase, DepositCalculation_1);
  tcase_add_test(getCase, DepositCalculation_2);
  tcase_add_test(getCase, DepositCalculation_3);
  tcase_add_test(getCase, DepositCalculation_4);
  tcase_add_test(getCase, DepositCalculation_5);
  tcase_add_test(getCase, DepositCalculation_6);
  tcase_add_test(getCase, DepositCalculation_7);

  srunner_run_all(runner, CK_ENV);
  srunner_free(runner);
}