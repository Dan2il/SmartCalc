#include "deposit_calculator.h"

ErrorsType
DepositCalculation(struct DataDeposit *data_deposit,
                   struct DepositProfitability *deposit_profitability) {
  ErrorsType errors = NO_ERRORS;
  errors =
      CheckDataDepositCalculationErrors(data_deposit, deposit_profitability);
  if (ERRORS_NOT_FOUND(errors)) {
    double deposit_amount = data_deposit->deposit_amount;
    double procent = 0;
    for (int counter_day = 0;
         counter_day < GetDay(data_deposit->deposit_term_in_month);
         counter_day++) {
      procent += (deposit_amount * data_deposit->interest_rate * 1 / 365) / 100;
      if (data_deposit->capitalization_of_interest == ENABLE) {
        CapitalizationInterest(data_deposit, &deposit_amount, &procent,
                               counter_day);
      }
      if (data_deposit->period_deposits_or_withdrawals != LATE) {
        DepositsAndWithdrawals(data_deposit, &deposit_amount, counter_day);
      }
    }
    deposit_amount += procent;
    deposit_profitability->accrued_interest = procent;
    deposit_profitability->deposit_amount =
        data_deposit->deposit_amount + deposit_profitability->accrued_interest;
  }
  return errors;
}

void CapitalizationInterest(struct DataDeposit *data_deposit,
                            double *deposit_amount, double *procent,
                            int counter_day) {
  if (data_deposit->periodicity_of_payments == MONTHLY) {
    if (counter_day == 30) {
      *deposit_amount += *procent;
      *procent = 0;
    }
  } else if (data_deposit->periodicity_of_payments == QUARTERLY) {
    if (counter_day == 120) {
      *deposit_amount += *procent;
      *procent = 0;
    }
  } else if (data_deposit->periodicity_of_payments == ANNUALLY) {
    if (counter_day == 365) {
      *deposit_amount += *procent;
      procent = 0;
    }
  }
}

void DepositsAndWithdrawals(struct DataDeposit *data_deposit,
                            double *deposit_amount, int counter_day) {
  if (data_deposit->period_deposits_or_withdrawals == MONTHLY) {
    if (counter_day == 30) {
      *deposit_amount += data_deposit->deposits;
      *deposit_amount -= data_deposit->withdrawals;
    }
  } else if (data_deposit->period_deposits_or_withdrawals == QUARTERLY) {
    if (counter_day == 120) {
      *deposit_amount += data_deposit->deposits;
      *deposit_amount -= data_deposit->withdrawals;
    }
  } else if (data_deposit->period_deposits_or_withdrawals == ANNUALLY) {
    if (counter_day == 365) {
      *deposit_amount += data_deposit->deposits;
      *deposit_amount -= data_deposit->withdrawals;
    }
  }
}

double SimpleProcent(struct DataDeposit *data_deposit) {
  double result = (data_deposit->deposit_amount * data_deposit->interest_rate *
                   GetDay(data_deposit->deposit_term_in_month) / 365.00) /
                  100;
  return result;
}

double GetDay(double number_of_month) {
  double number_of_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int result = 0;
  for (int counter = 0; number_of_month != 0;) {
    result += number_of_days[counter];
    counter++;
    if (counter == 12) {
      counter = 0;
    }
    number_of_month--;
  }
  return result;
}

ErrorsType CheckDataDepositCalculationErrors(
    struct DataDeposit *data_deposit,
    struct DepositProfitability *deposit_profitability) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(2, CHECK_POINTER(data_deposit),
                       CHECK_POINTER(deposit_profitability));
  return errors;
}
