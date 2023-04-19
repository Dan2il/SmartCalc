/*!
 * \file credit_calculator.h
 */
#ifndef CREDIT_CALCULATOR_CREDIT_CALCULATOR_H
#define CREDIT_CALCULATOR_CREDIT_CALCULATOR_H

#include <math.h>

#include "../processing_errors/processing_errors.h"

#define DAYS_IN_YEAR 365
#define DAYS_IN_MONTH 30

typedef enum { ANNUITY, DIFFERENTIATED } CreditType;

typedef enum {
  JANUARY,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
} Month;

struct DataCredit {
  double total_credit_amount;
  double term_in_months;
  double interest_rate;
  CreditType credit_type;
};

struct PaymentCredit {
  double *monthly_payment;
  double overpayment_on_credit;
  double total_payment;
};

/*!
 * \brief CreditCalculation Вычисляет ежемесячный платеж, переплату по кредиту и
 * общая выплату \param data_credit Структура, хранящая данные необходимые для
 * вычисления \param payment_data_credit Структура, хранящая результат
 * вычисления \return Возвращает тип ошибки
 */
ErrorsType CreditCalculation(struct DataCredit *data_credit,
                             struct PaymentCredit *payment_data_credit);
/*!
 * \brief RatioAnnuityCalculation Вычисляет аннуитивные платежи по кредиту
 * \return Возвращает сумму платежа
 */
double RatioAnnuityCalculation(struct DataCredit *data_credit);

/*!
 * \brief CheckDataCredit Проверяет корректность данных для вычисления в функции
 * CreditCalculation \return Возвращает тип ошибки
 */
ErrorsType CheckDataCredit(struct DataCredit *data_credit,
                           struct PaymentCredit *payment_data_credit);

double Round(double num);

Month GetNextMonth(Month month);
double GetDayMonth(Month month);

#endif  // CREDIT_CALCULATOR_CREDIT_CALCULATOR_H
