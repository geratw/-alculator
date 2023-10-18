#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QLocale>
#include <list>

#include "../controller/s21_controller.h"
namespace Ui {
class creditwindow;

}
namespace s21 {
class CreditWindow : public QDialog {
  Q_OBJECT

 public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

 signals:
  void SecondWindow();
  void TableParam(int rows, int current_cols, QStringList array);

 private slots:
  void buttonBack();
  void Result();

 private:
  Ui::creditwindow *ui_;
  ControllerCredit controller_credit_;
  QLocale locale_;

  void UpdateMonthlyPayment();
  void UpdateDiff();
};
}  // namespace s21

#endif  // CREDITWINDOW_H
