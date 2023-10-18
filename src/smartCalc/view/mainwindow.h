#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "credit/creditwindow.h"
#include "defoltwindow.h"

namespace Ui {
class MainWindow;
}

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void CreditCalculator();
  void Calculator();

 private:
  Ui::MainWindow *ui_;
  DefoltWindow *defolt_window_;
  CreditWindow *credit_window_;
};
}  // namespace s21

#endif  // MAINWINDOW_H
