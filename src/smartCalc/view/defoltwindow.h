#ifndef DEFOLTWINDOW_H
#define DEFOLTWINDOW_H

#include <QDialog>
#include <QVector>
#include <cmath>
#include <iostream>

#include "../controller/s21_controller.h"

namespace Ui {
class defoltwindow;
}

namespace s21 {
class DefoltWindow : public QDialog {
  Q_OBJECT

 public:
  explicit DefoltWindow(QWidget* parent = nullptr);
  ~DefoltWindow();

 signals:
  void firstWindow();

 private slots:
  void DeleteClicked();
  void GrafOpen();
  void GrafClose();
  void BackClicked();

 private:
  void MathOperations();
  void Functions();
  void ConnectButtons();
  void PushString();
  void DigitNumbers();
  bool is_graf_open_ = false;
  Ui::defoltwindow* ui_;
  ControllerCalc controller_;

  void GeneratePlotData(const std::string& expression, double x_min,
                        double x_max, double y_min, double y_max,
                        QVector<double>& x, QVector<double>& y);

  void UpdateGraph(const QVector<double>& x, const QVector<double>& y,
                   double x_min, double x_max, double y_min, double y_max);
};
}  // namespace s21

#endif  // DEFOLTWINDOW_H
