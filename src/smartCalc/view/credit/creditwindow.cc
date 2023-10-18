#include "creditwindow.h"

#include "ui_creditwindow.h"

s21::CreditWindow::CreditWindow(QWidget* parent)
    : QDialog(parent), ui_(new Ui::creditwindow) {
  CreditWindow::setFixedSize(651, 529);
  ui_->setupUi(this);
  locale_ = QLocale(QLocale::Russian);
  connect(ui_->button_back, &QPushButton::clicked, this,
          &CreditWindow::buttonBack);
  connect(ui_->result_credit, &QPushButton::clicked, this,
          &CreditWindow::Result);
}

s21::CreditWindow::~CreditWindow() { delete ui_; }

void s21::CreditWindow::buttonBack() {
  this->close();
  emit SecondWindow();
}

void s21::CreditWindow::Result() {
  controller_credit_.SetLoanAmount(ui_->sumcredit->value(), ui_->month->value(),
                                   ui_->procent->value());
  if (ui_->anuitetni->isChecked()) {
    controller_credit_.CalculateAnnuity();

    UpdateMonthlyPayment();
    CreditWindow::setFixedSize(651, 808);
  } else {
    ui_->tableWidget->setRowCount(controller_credit_.GetRowsCount());
    controller_credit_.CalculateDifferentiated();

    UpdateDiff();
    CreditWindow::setFixedSize(1482, 530);
  }
}

void s21::CreditWindow::UpdateDiff() {
  ui_->overpaymen_differentiated->setText(
      locale_.toString(controller_credit_.GetOverpayment(), 'f', 2));
  ui_->total_payout_differentiated->setText(
      locale_.toString(controller_credit_.GetTotalPayment(), 'f', 2));
  std::list<CreditResultField> myList = controller_credit_.GetMyList();
  int row = 0;
  for (const auto& s : myList) {
    ui_->tableWidget->setItem(row, 0,
                              new QTableWidgetItem(locale_.toString(
                                  s.result_amount_per_month, 'f', 2)));
    ui_->tableWidget->setItem(
        row, 1,
        new QTableWidgetItem(locale_.toString(s.interest_payment, 'f', 2)));
    ui_->tableWidget->setItem(row, 2,
                              new QTableWidgetItem(locale_.toString(
                                  s.the_balance_of_the_debt, 'f', 2)));
    row++;
  }
}

void s21::CreditWindow::UpdateMonthlyPayment() {
  ui_->monthly_payment->setText(
      locale_.toString(controller_credit_.GetMonthlyPayment(), 'f', 2));
  ui_->overpayment_annuities->setText(
      locale_.toString(controller_credit_.GetOverpayment(), 'f', 2));
  ui_->total_payout_annuities->setText(
      locale_.toString(controller_credit_.GetTotalPayment(), 'f', 2));
}
