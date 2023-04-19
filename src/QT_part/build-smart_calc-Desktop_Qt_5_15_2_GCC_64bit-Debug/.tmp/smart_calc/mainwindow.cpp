#include "mainwindow.h"

#include "finance.h"
#include "graph.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->HandlerButton();
}

MainWindow::~MainWindow() { delete ui; }
