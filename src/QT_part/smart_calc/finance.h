#ifndef FINANCE_H
#define FINANCE_H

#include <QDialog>

extern "C" {
#include "bin/credit_calculator/credit_calculator.h"
#include "bin/deposit_calculator/deposit_calculator.h"
}

namespace Ui {
class Finance;
}

class Finance : public QDialog {
  Q_OBJECT

 public:
  explicit Finance(QWidget *parent = nullptr);
  ~Finance();

  void SetWindowCredit();
  void SetWindowDeposit();

  struct PaymentCredit *data_payment;
  int term_credit;

  struct DepositProfitability *deposit_profitability;

 private:
  Ui::Finance *ui;
};

#endif  // FINANCE_H
