#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <vector>

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

  double begin_x;
  double end_x;
  double begin_y;
  double end_y;

  void Paint(std::vector<double> dots_x, std::vector<double> dots_y);

 private:
  Ui::Graph *ui;

  QVector<double> x_line;
  QVector<double> y_line;
};

#endif  // GRAPH_H
