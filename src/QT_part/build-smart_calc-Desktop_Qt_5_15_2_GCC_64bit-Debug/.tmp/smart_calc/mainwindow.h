#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QVector>
#include <QtMath>
#include <QtWidgets>
#include <string>
#include <vector>

#include "finance.h"

extern "C" {
#include "bin/allocate_memory/allocate_memory.h"
#include "bin/credit_calculator/credit_calculator.h"
#include "bin/deposit_calculator/deposit_calculator.h"
#include "bin/expression/calculation.h"
#include "bin/expression/expression.h"
#include "bin/list/list.h"
#include "bin/sort_station/sort_station.h"
}

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }  // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

  void HandlerButton();
 private slots:
  void HandlerCalculationButton();
  void HandlerClearButton();
  void HandlerCalculationButtonEqual();
  void HandlerGraphButton();
  void HandlerCreditButton();
  void HandlerDepositButton();
};
#endif  // MAINWINDOW_H
