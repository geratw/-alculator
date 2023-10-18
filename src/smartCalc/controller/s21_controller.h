#ifndef EXAMPLECONTROLLER_H
#define EXAMPLECONTROLLER_H

#include <list>

#include "../model/s21_model.h"
namespace s21 {
class ControllerCredit {
 private:
  ModelCredit model_credit_;

 public:
  void CalculateAnnuity();
  void CalculateDifferentiated();
  void SetLoanAmount(double amount, int months, double rate);
  double GetMonthlyPayment();
  double GetOverpayment();
  double GetTotalPayment();
  int GetRowsCount();
  std::list<CreditResultField> GetMyList() const {
    return model_credit_.GetMyList();
  }
};

class ControllerCalc {
 private:
  ModelCalc model_;

 public:
  double GetCalcError();
  double GetCalcResult();
  bool CalcExpression(const std::string& expr, double xValue);
};
}  // namespace s21
#endif
