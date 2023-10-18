#ifndef EXAMPLEMODEL_H
#define EXAMPLEMODEL_H

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace s21 {
constexpr const char* POW = "^";
constexpr const char* PLUS = "+";
constexpr const char* MINUS = "-";
constexpr const char* MULTIPLY = "*";
constexpr const char* DIVIDE = "/";
constexpr const char* MOD = "%";

constexpr int LVL_NONE = -1;

struct CreditResultField {
  double result_amount_per_month;
  double interest_payment;
  double the_balance_of_the_debt;
};

struct PolishValue {
  double value = 0.0;
  std::string operators = "\0";
};

class ModelCredit {
 private:
  double monthly_payment_;
  double total_payment_;
  double overpayment_;
  std::list<CreditResultField> deposit_result_data_;
  double sum_credit_;
  int month_;
  double interest_rate_;

 public:
  void CalculateAnnuit();
  void CalculateDifferent();
  void SetSumCredit(double amount, int months, double rate);
  double GetMonthlyPayment() const { return monthly_payment_; }
  double GetTotalPayment() const { return total_payment_; }
  double GetOverpayment() const { return overpayment_; }
  int GetRowsCount() const { return month_; }
  std::list<CreditResultField> GetMyList() const {
    return deposit_result_data_;
  }
};

class ModelCalc {
 private:
  std::vector<PolishValue> vector_double_, vector_operators_, polish_notation_;
  std::string expression_;
  bool errors_;
  double x_value_;
  double result_;
  int position_in_string_;
  void Bracket();
  int SignLvl(const std::string& sign);
  void Priority(const std::string& sign);
  void CreatePolishNotation();
  void BktCount();
  double ReadDouble();
  std::string ReadSign();
  void Parser();
  bool UnarySign();
  std::string ReplaceSignBeforeOpenBracket();
  bool Sign(int position);
  double MathematicsOneArg(double oneNum, std::string sign);
  double MathematicsTwoArg(double oneNum, double twoNum, std::string sign);

 public:
  void Start();
  void Calculation();
  bool CalculateTheExpression(std::string expr, double xValue);
  bool GetCalcEr() const { return errors_; };
  double GetCalcRes() const { return result_; };
};
}  // namespace s21
#endif
