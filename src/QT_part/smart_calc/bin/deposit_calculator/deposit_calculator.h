/*!
 * \file deposit_calculator.h
 */
#ifndef DEPOSIT_CALCULATOR_DEPOSIT_CALCULATOR_H
#define DEPOSIT_CALCULATOR_DEPOSIT_CALCULATOR_H

#include <math.h>

#include "../processing_errors/processing_errors.h"

typedef enum { MONTHLY, QUARTERLY, ANNUALLY, LATE } Periodicity;

typedef enum { ENABLE, DISABLE } CapitalizationOfInterest;

struct DataDeposit {
  double deposit_amount;
  double deposit_term_in_month;
  double interest_rate;
  Periodicity periodicity_of_payments;
  CapitalizationOfInterest capitalization_of_interest;
  Periodicity period_deposits_or_withdrawals;
  double deposits;
  double withdrawals;
};

struct DepositProfitability {
  double accrued_interest;
  double tax_amount;
  double deposit_amount;
};

/*!
 * \brief DepositCalculation Вычисляет начисленные проценты по вкладу, сумму на
 * вкладе к концу срока \param data_deposit Данные для вычисления \param
 * deposit_profitability Хранит результат вычисления \return Возвращает тип
 * ошибки
 */
ErrorsType
DepositCalculation(struct DataDeposit *data_deposit,
                   struct DepositProfitability *deposit_profitability);
/*!
 * \brief SimpleProcent Вычисляет простой случае (без капитализации и пополнений
 * / снятий) для DepositCalculation \return Возвращает сумму начисленных
 * процентов по депозиту
 */
double SimpleProcent(struct DataDeposit *data_deposit);

/*!
 * \brief CapitalizationInterest Проверяет наступление даты капитализации.
 * Начисляет проценты в случае ее наступления.
 */
void CapitalizationInterest(struct DataDeposit *data_deposit,
                            double *deposit_amount, double *procent,
                            int counter_day);
/*!
 * \brief DepositsAndWithdrawals Проверяет наступление даты снятия определенной
 * суммы или пополнения депозита. Изменяет сумму депозита (deposit_amount), в
 * случае ее наступления
 */
void DepositsAndWithdrawals(struct DataDeposit *data_deposit,
                            double *deposit_amount, int counter_day);

double GetDay(double number_of_month);
ErrorsType CheckDataDepositCalculationErrors(
    struct DataDeposit *data_deposit,
    struct DepositProfitability *deposit_profitability);

#endif
