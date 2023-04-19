#include "credit_calculator.h"

// A = K * S
// A — ежемесячный аннуитетный платеж,
// K — коэффициент аннуитета,
// S — сумма кредита.

// K = i * (1 + i) pown / (( 1 + i ) pown - 1)
// i — месячная процентная ставка по кредиту (= годовая ставка/12 месяцев)
// n — количество периодов, в течение которых выплачивается кредит.

ErrorsType CreditCalculation(struct DataCredit *data_credit,
                             struct PaymentCredit *payment_data_credit) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckDataCredit(data_credit, payment_data_credit);
  if (ERRORS_NOT_FOUND(errors)) {
    if (data_credit->credit_type == ANNUITY) {
      double ratio_annuity = RatioAnnuityCalculation(data_credit);
      double pay_in_month = ratio_annuity * data_credit->total_credit_amount;
      pay_in_month = Round(pay_in_month);

      payment_data_credit->total_payment =
          pay_in_month * data_credit->term_in_months;
      payment_data_credit->overpayment_on_credit =
          payment_data_credit->total_payment - data_credit->total_credit_amount;

      for (int counter = 0; counter < data_credit->term_in_months; counter++) {
        payment_data_credit->monthly_payment[counter] = pay_in_month;
      }
    } else if (data_credit->credit_type == DIFFERENTIATED) {
      double principal_debt =
          data_credit->total_credit_amount / data_credit->term_in_months;
      principal_debt = Round(principal_debt);
      double remaining_debt = data_credit->total_credit_amount;
      Month month = JANUARY;
      for (int counter = 0; counter < data_credit->term_in_months; counter++) {
        double debt_interest =
            (remaining_debt * data_credit->interest_rate * GetDayMonth(month)) /
            DAYS_IN_YEAR;
        debt_interest = Round(debt_interest);
        payment_data_credit->overpayment_on_credit += debt_interest;
        payment_data_credit->monthly_payment[counter] =
            principal_debt + debt_interest;
        remaining_debt -= principal_debt;
        month = GetNextMonth(month);
        if (remaining_debt < 0) {
          payment_data_credit->monthly_payment[counter] += remaining_debt;
        }
      }
      payment_data_credit->total_payment =
          data_credit->total_credit_amount +
          payment_data_credit->overpayment_on_credit;
    }
  }
  return errors;
}

Month GetNextMonth(Month month) {
  Month result = month;
  if (month == JANUARY) {
    result = FEBRUARY;
  } else if (month == FEBRUARY) {
    result = MARCH;
  } else if (month == MARCH) {
    result = APRIL;
  } else if (month == APRIL) {
    result = MAY;
  } else if (month == MAY) {
    result = JUNE;
  } else if (month == JUNE) {
    result = JULY;
  } else if (month == JULY) {
    result = AUGUST;
  } else if (month == AUGUST) {
    result = SEPTEMBER;
  } else if (month == SEPTEMBER) {
    result = OCTOBER;
  } else if (month == OCTOBER) {
    result = NOVEMBER;
  } else if (month == NOVEMBER) {
    result = DECEMBER;
  } else if (month == DECEMBER) {
    result = JANUARY;
  }
  return result;
}

double GetDayMonth(Month month) {
  int days = 0;
  if (month == JANUARY) {
    days = 31;
  } else if (month == FEBRUARY) {
    days = 28;
  } else if (month == MARCH) {
    days = 31;
  } else if (month == APRIL) {
    days = 30;
  } else if (month == MAY) {
    days = 31;
  } else if (month == JUNE) {
    days = 30;
  } else if (month == JULY) {
    days = 31;
  } else if (month == AUGUST) {
    days = 31;
  } else if (month == SEPTEMBER) {
    days = 30;
  } else if (month == OCTOBER) {
    days = 31;
  } else if (month == NOVEMBER) {
    days = 30;
  } else if (month == DECEMBER) {
    days = 31;
  }
  return days;
}

ErrorsType CheckDataCredit(struct DataCredit *data_credit,
                           struct PaymentCredit *payment_data_credit) {
  ErrorsType errors = NO_ERRORS;
  errors = CheckErrors(8, CHECK_POINTER(data_credit),
                       CHECK_POINTER(payment_data_credit),
                       CHECK_NEGATIVE(data_credit->total_credit_amount),
                       CHECK_NULL_NUMBER(data_credit->total_credit_amount),
                       CHECK_NEGATIVE(data_credit->term_in_months),
                       CHECK_NULL_NUMBER(data_credit->term_in_months),
                       CHECK_NEGATIVE(data_credit->interest_rate),
                       CHECK_NULL_NUMBER(data_credit->interest_rate));
  return errors;
}

double RatioAnnuityCalculation(struct DataCredit *data_credit) {
  double result = 0;
  double interest_rate_in_months = data_credit->interest_rate / 12.00;
  result = (interest_rate_in_months * pow((1.00 + interest_rate_in_months),
                                          data_credit->term_in_months)) /
           (pow((1.00 + interest_rate_in_months), data_credit->term_in_months) -
            1.00);
  return result;
}

double Round(double num) {
  num *= 100.00;
  num = round(num);
  num /= 100.00;
  return num;
}