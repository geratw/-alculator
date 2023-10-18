#include "s21_controller.h"

double s21::ControllerCredit::GetMonthlyPayment() {
  return model_credit_.GetMonthlyPayment();
}

double s21::ControllerCredit::GetOverpayment() {
  return model_credit_.GetOverpayment();
}

double s21::ControllerCredit::GetTotalPayment() {
  return model_credit_.GetTotalPayment();
}

int s21::ControllerCredit::GetRowsCount() {
  return model_credit_.GetRowsCount();
}

void s21::ControllerCredit::SetLoanAmount(double amount, int months,
                                          double rate) {
  model_credit_.SetSumCredit(amount, months, rate);
}

void s21::ControllerCredit::CalculateAnnuity() {
  model_credit_.CalculateAnnuit();
}

void s21::ControllerCredit::CalculateDifferentiated() {
  model_credit_.CalculateDifferent();
}

bool s21::ControllerCalc::CalcExpression(const std::string& expr,
                                         double xValue) {
  return model_.CalculateTheExpression(expr, xValue);
}

double s21::ControllerCalc::GetCalcError() { return model_.GetCalcEr(); }

double s21::ControllerCalc::GetCalcResult() { return model_.GetCalcRes(); }
