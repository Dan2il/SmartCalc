#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent) : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

void Graph::Paint(std::vector<double> dots_x, std::vector<double> dots_y) {
  ui->widget->xAxis->setRange(begin_x, end_x);
  ui->widget->yAxis->setRange(begin_y, end_y);

  for (auto it = dots_x.begin(); it != dots_x.end(); it++) {
    x_line.push_back(*it);
  }

  for (auto it = dots_y.begin(); it != dots_y.end(); it++) {
    y_line.push_back(*it);
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x_line, y_line);
  ui->widget->replot();
}
