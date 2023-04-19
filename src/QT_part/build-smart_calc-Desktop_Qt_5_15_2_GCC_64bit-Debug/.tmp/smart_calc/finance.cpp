#include "finance.h"

#include "ui_finance.h"

Finance::Finance(QWidget *parent) : QDialog(parent), ui(new Ui::Finance) {
  ui->setupUi(this);
}

Finance::~Finance() { delete ui; }

void Finance::SetWindowCredit() {
  ui->textBrowser_total_payment->setText(
      QString::number(data_payment->total_payment, 'g', 14));
  ui->textBrowser_overpayment->setText(
      QString::number(data_payment->overpayment_on_credit, 'g', 14));
  QString buffer;
  for (int counter = 0; counter < term_credit; counter++) {
    buffer +=
        QString::number(data_payment->monthly_payment[counter], 'g', 14) + "\n";
  }
  ui->textBrowser_monthly_payments->setText(buffer);
}

void Finance::SetWindowDeposit() {
  ui->textBrowser_deposit_procent->setText(
      QString::number(deposit_profitability->accrued_interest, 'g', 14));
  ui->textBrowser_depost_all->setText(
      QString::number(deposit_profitability->deposit_amount, 'g', 14));
  ui->textBrowser_tax->setText(
      QString::number(deposit_profitability->tax_amount, 'g', 14));
}
