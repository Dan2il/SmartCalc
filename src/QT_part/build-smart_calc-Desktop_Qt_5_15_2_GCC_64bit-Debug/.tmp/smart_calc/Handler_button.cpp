
#include "graph.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::HandlerButton() {
  QList check = findChildren<QPushButton *>();
  for (QPushButton *button : check) {
    if (button == ui->pushButton_clean ||
        button == ui->pushButton_clean_one_sym) {
      connect(button, SIGNAL(clicked()), this, SLOT(HandlerClearButton()));
    } else if (button == ui->pushButton_equal) {
      connect(button, SIGNAL(clicked()), this,
              SLOT(HandlerCalculationButtonEqual()));
    } else if (button == ui->pushButton_chart) {
      connect(button, SIGNAL(clicked()), this, SLOT(HandlerGraphButton()));
    } else if (button == ui->pushButton_credit) {
      connect(button, SIGNAL(clicked()), this, SLOT(HandlerCreditButton()));
    } else if (button == ui->pushButton_deposit) {
      connect(button, SIGNAL(clicked()), this, SLOT(HandlerDepositButton()));
    } else {
      connect(button, SIGNAL(clicked()), this,
              SLOT(HandlerCalculationButton()));
    }
  }
}

void MainWindow::HandlerDepositButton() {
  Finance deposit;
  struct DataDeposit data_deposit;

  data_deposit.deposit_amount = ui->lineEdit_deposit_amount->text().toDouble();
  data_deposit.deposit_term_in_month = ui->spinBox_deposit_term->value();
  data_deposit.interest_rate = ui->doubleSpinBox_deposit_rate->value();

  if (ui->comboBox_deposit_periodicity_of_payments->currentText() ==
      "В конце срока") {
    data_deposit.periodicity_of_payments = LATE;
    data_deposit.period_deposits_or_withdrawals = LATE;
  } else if (ui->comboBox_deposit_periodicity_of_payments->currentText() ==
             "Раз в месяц") {
    data_deposit.periodicity_of_payments = MONTHLY;
    data_deposit.period_deposits_or_withdrawals = MONTHLY;
  } else if (ui->comboBox_deposit_periodicity_of_payments->currentText() ==
             "Раз в квартал") {
    data_deposit.periodicity_of_payments = QUARTERLY;
    data_deposit.period_deposits_or_withdrawals = QUARTERLY;
  } else if (ui->comboBox_deposit_periodicity_of_payments->currentText() ==
             "Раз в год") {
    data_deposit.periodicity_of_payments = ANNUALLY;
    data_deposit.period_deposits_or_withdrawals = ANNUALLY;
  }

  if (ui->checkBox_capitalization->isChecked()) {
    data_deposit.capitalization_of_interest = ENABLE;
  } else {
    data_deposit.capitalization_of_interest = DISABLE;
  }
  data_deposit.deposits = ui->lineEdit_summ_deposits->text().toDouble();
  data_deposit.withdrawals = ui->lineEdit_sub_deposits->text().toDouble();

  struct DepositProfitability deposit_profitability = {
      .accrued_interest = 0, .deposit_amount = 0, .tax_amount = 0};

  ErrorsType errors = NO_ERRORS;
  errors = DepositCalculation(&data_deposit, &deposit_profitability);
  if (ERRORS_NOT_FOUND(errors)) {
    deposit.deposit_profitability = &deposit_profitability;
  }
  deposit.SetWindowDeposit();
  deposit.setModal(true);
  deposit.exec();
}

void MainWindow::HandlerCreditButton() {
  Finance credit;

  struct DataCredit data_credit;

  if (ui->radioButton_annuity->isChecked()) {
    data_credit.credit_type = ANNUITY;
  } else if (ui->radioButton_differentiated->isChecked()) {
    data_credit.credit_type = DIFFERENTIATED;
  }

  data_credit.total_credit_amount =
      ui->lineEdit_all_credit_amount->text().toDouble();
  data_credit.interest_rate =
      ui->lineEdit_interest_rate->text().toDouble() / 100;
  data_credit.term_in_months = ui->lineEdit_term_credit->text().toDouble();

  struct PaymentCredit data_payment = {
      .monthly_payment = 0, .overpayment_on_credit = 0, .total_payment = 0};
  data_payment.monthly_payment =
      (double *)malloc(data_credit.term_in_months * sizeof(double));
  if (data_payment.monthly_payment) {
    ErrorsType errors = CreditCalculation(&data_credit, &data_payment);
    if (ERRORS_NOT_FOUND(errors)) {
      credit.data_payment = &data_payment;
      credit.term_credit = data_credit.term_in_months;

      credit.SetWindowCredit();
      credit.setModal(true);
      credit.exec();
    }
  }

  if (data_payment.monthly_payment) {
    free(data_payment.monthly_payment);
  }
}

void MainWindow::HandlerGraphButton() {
  Graph graph;

  std::vector<double> dots_x;
  std::vector<double> dots_y;

  graph.begin_x = ui->spinBox_begin_x->value();
  graph.end_x = ui->spinBox_end_x->value();
  graph.begin_y = ui->spinBox_begin_y->value();
  graph.end_y = ui->spinBox_end_y->value();

  ErrorsType errors = NO_ERRORS;

  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  std::string expression_in_string = ui->input_expression->text().toStdString();
  expression_in_string.erase(remove_if(expression_in_string.begin(),
                                       expression_in_string.end(), isspace),
                             expression_in_string.end());

  char *test = expression_in_string.data();
  printf("test = %s\n", test);
  if (test) {
    TypeNotation type_notation = CLASSIC;
    errors = InitializationExpression(&expression, test, type_notation);
    if (ERRORS_NOT_FOUND(errors)) {
      errors = ReadStringExpression(&expression);
      if (ERRORS_NOT_FOUND(errors)) {
        errors = InitializationExpression(&result, "", EMPTY);
        if (ERRORS_NOT_FOUND(errors)) {
          errors = InitializationConverter(&converter, &expression, &result);
          if (ERRORS_NOT_FOUND(errors)) {
            errors = InfixToReversePolish(&converter);
          }
        }
      }
    }
    if (ERRORS_NOT_FOUND(errors)) {
      double check = 0;

      double x = ui->spinBox_begin_x->value();
      for (; x <= ui->spinBox_end_x->value(); x++) {
        errors = HandlerCalculationWhithX(result.lexems, &check, x);
        if (ERRORS_NOT_FOUND(errors)) {
          dots_y.push_back(check);
          dots_x.push_back(x);
        }
      }
    }
  }

  graph.Paint(dots_x, dots_y);

  graph.setModal(true);
  graph.exec();
}

void MainWindow::HandlerCalculationButtonEqual() {
  ErrorsType errors = NO_ERRORS;

  struct Expression expression;
  struct Expression result;
  struct ConvertStation converter;

  std::string expression_in_string = ui->input_expression->text().toStdString();

  expression_in_string.erase(remove_if(expression_in_string.begin(),
                                       expression_in_string.end(), isspace),
                             expression_in_string.end());

  char *test = expression_in_string.data();
  if (test) {
    TypeNotation type_notation = CLASSIC;
    errors = InitializationExpression(&expression, test, type_notation);
    if (ERRORS_NOT_FOUND(errors)) {
      errors = ReadStringExpression(&expression);
      if (ERRORS_NOT_FOUND(errors)) {
        errors = InitializationExpression(&result, "", EMPTY);
        if (ERRORS_NOT_FOUND(errors)) {
          errors = InitializationConverter(&converter, &expression, &result);
          if (ERRORS_NOT_FOUND(errors)) {
            errors = InfixToReversePolish(&converter);
          }
        }
      }
    }
    if (ERRORS_NOT_FOUND(errors)) {
      double check = 0;

      if (ui->input_x->text().isEmpty()) {
        errors = HandlerCalculation(result.lexems, &check);
      } else {
        double x = ui->input_x->text().toDouble();
        errors = HandlerCalculationWhithX(result.lexems, &check, x);
      }
      if (ERRORS_NOT_FOUND(errors)) {
        ui->result_calc_expression->setText(QString::number(check));
        ui->input_expression->setText("0");
      }
    }
    if (errors != NO_ERRORS) {
      ui->result_calc_expression->setText("Ошибка");
      ui->input_expression->setText("0");
    }
  }
}

void MainWindow::HandlerClearButton() {
  QPushButton *button = (QPushButton *)sender();
  if (button == ui->pushButton_clean) {
    ui->input_expression->setText("0");
    ui->result_calc_expression->setText("0");
    ui->input_x->clear();
  } else if (button == ui->pushButton_clean_one_sym) {
    std::string expression = ui->input_expression->text().toStdString();
    expression.pop_back();
    ui->input_expression->setText(QString::fromStdString(expression));
    if (ui->input_expression->text().isEmpty()) {
      ui->input_expression->setText("0");
    }
  }
}

void MainWindow::HandlerCalculationButton() {
  if (ui->input_expression->text() == "0") {
    ui->input_expression->clear();
  }
  QString buffer_expression =
      ui->input_expression->text() + ((QPushButton *)sender())->text();
  ui->input_expression->setText(buffer_expression);
}
