#include "s21_model.h"

void s21::ModelCredit::SetSumCredit(double amount, int month_s, double rate) {
  sum_credit_ = amount;
  month_ = month_s;
  interest_rate_ = rate;
}

void s21::ModelCredit::CalculateAnnuit() {
  double procent = interest_rate_ / 100.0 / 12.0;
  monthly_payment_ =
      sum_credit_ *
      (procent * (pow(1 + procent, month_) / (pow(1 + procent, month_) - 1)));
  total_payment_ = monthly_payment_ * month_;
  overpayment_ = total_payment_ - sum_credit_;
}

void s21::ModelCredit::CalculateDifferent() {
  overpayment_ = 0;
  total_payment_ = 0;
  double procent = interest_rate_ / 100.0 / 12.0;
  deposit_result_data_.clear();
  double d = sum_credit_ / month_;
  int n = month_;
  double the_balance_of_the_debt = 0;

  for (int i = 0; i < n; i++) {
    month_--;
    double result_amount_per_month_ =
        (d) + ((sum_credit_) - (d) * (month_)) * (procent);
    double interest_payment = result_amount_per_month_ - d;

    CreditResultField tmp = {result_amount_per_month_, interest_payment,
                             the_balance_of_the_debt};
    deposit_result_data_.push_front(tmp);
    overpayment_ += result_amount_per_month_ - d;
    the_balance_of_the_debt += d;
  }
  total_payment_ = sum_credit_ + overpayment_;
}

bool s21::ModelCalc::CalculateTheExpression(std::string expr,
                                            double value_x_in_view) {
  expression_ = expr;
  errors_ = false;
  x_value_ = value_x_in_view;
  Start();
  return errors_;
}

void s21::ModelCalc::Start() {
  Parser();
  if (!errors_) Calculation();
  polish_notation_.clear();
  vector_double_.clear();
  vector_operators_.clear();
}

void s21::ModelCalc::Parser() {
  BktCount();
  expression_ = ReplaceSignBeforeOpenBracket();
  int lenString = expression_.length();
  if (errors_) return;
  for (position_in_string_ = 0; position_in_string_ < lenString && !errors_;
       position_in_string_++) {
    char sym = expression_[position_in_string_];
    PolishValue element;
    if (isdigit(sym) || sym == '.' || UnarySign()) {
      element.value = ReadDouble();
      vector_double_.push_back(element);
    } else if (sym == 'x') {
      element.value = x_value_;
      vector_double_.push_back(element);
    } else if (isalpha(sym)) {
      Priority(ReadSign());
    } else if (Sign(position_in_string_)) {
      if (position_in_string_ != 0 && Sign(position_in_string_ - 1)) {
        errors_ = true;
        return;
      }
      element.operators = std::string(1, sym);
      Priority(element.operators);
    } else if (sym == '(') {
      element.operators = std::string(1, sym);
      vector_operators_.push_back(element);
    } else if (sym == ')') {
      Bracket();
    } else {
      errors_ = true;
      return;
    }
  }
  CreatePolishNotation();
}

void s21::ModelCalc::CreatePolishNotation() {
  polish_notation_.insert(polish_notation_.end(), vector_double_.begin(),
                          vector_double_.end());
  polish_notation_.insert(polish_notation_.end(), vector_operators_.rbegin(),
                          vector_operators_.rend());
}

void s21::ModelCalc::Calculation() {
  std::vector<double> vectorOfValues;
  double oneNum = 0.0;
  double twoNum = 0.0;
  for (auto& val : polish_notation_) {
    if (val.operators.empty()) {
      vectorOfValues.push_back(val.value);
    } else if (val.operators.length() > 1) {
      oneNum = vectorOfValues.back();
      vectorOfValues.pop_back();
      vectorOfValues.push_back(MathematicsOneArg(oneNum, val.operators));
    } else if (val.operators.length() == 1) {
      if (vectorOfValues.size() < 2) {
        errors_ = true;
        return;
      }
      twoNum = vectorOfValues.back();
      vectorOfValues.pop_back();
      oneNum = vectorOfValues.back();
      vectorOfValues.pop_back();
      vectorOfValues.push_back(
          MathematicsTwoArg(oneNum, twoNum, val.operators));
    }
  }
  if (vectorOfValues.size() != 1) {
    errors_ = true;
    return;
  }
  result_ = vectorOfValues[0];
}

void s21::ModelCalc::Priority(const std::string& sign) {
  PolishValue last_element;
  if (!vector_operators_.empty()) {
    last_element = vector_operators_.back();
    if (SignLvl(last_element.operators) >= SignLvl(sign)) {
      while (SignLvl(last_element.operators) >= SignLvl(sign) &&
             !vector_operators_.empty()) {
        vector_operators_.pop_back();
        vector_double_.push_back(last_element);
        if (!vector_operators_.empty()) last_element = vector_operators_.back();
      }
      last_element.operators = sign;
      vector_operators_.push_back(last_element);
    } else if (SignLvl(last_element.operators) < SignLvl(sign)) {
      last_element.operators = sign;
      vector_operators_.push_back(last_element);
    }
  } else {
    if (sign != "\0") {
      last_element.operators = sign;
      vector_operators_.push_back(last_element);
    }
  }
}

int s21::ModelCalc::SignLvl(const std::string& sign) {
  std::unordered_map<std::string, int> sign_levels = {
      {"sin", 4},    {"cos", 4},  {"tg", 4}, {"acos", 4}, {"asin", 4},
      {"atan", 4},   {"sqrt", 4}, {"ln", 4}, {"log", 4},  {POW, 3},
      {MULTIPLY, 1}, {DIVIDE, 1}, {MOD, 1},  {PLUS, 0},   {MINUS, 0}};
  auto it = sign_levels.find(sign);
  if (it != sign_levels.end()) {
    return it->second;
  } else {
    return LVL_NONE;
  }
}

bool s21::ModelCalc::UnarySign() {
  char current_char = expression_[position_in_string_];
  char next_char = expression_[position_in_string_ + 1];
  char last_char = expression_[position_in_string_ - 1];
  return (current_char == '-' || current_char == '+') &&
         (isdigit(next_char) || next_char == 'x') &&
         (position_in_string_ == 0 || !isdigit(last_char)) && last_char != ')';
}

bool s21::ModelCalc::Sign(int position) {
  const std::string mathSigns = "+-*/^%";
  return (mathSigns.find_first_of(expression_[position]) != std::string::npos);
}

double s21::ModelCalc::MathematicsOneArg(double oneNum, std::string sign) {
  double result = 0.0;
  using MathFunction = double (*)(double);
  std::unordered_map<std::string, MathFunction> functionMap = {
      {"sin", sin},
      {"cos", cos},
      {"tan", tan},
      {"acos", std::acos},
      {"asin", std::asin},
      {"atan", atan},
      {"sqrt", [](double x) { return (x < 0) ? NAN : std::sqrt(x); }},
      {"ln", [](double x) { return (x <= 0) ? NAN : std::log(x); }},
      {"log", [](double x) { return (x <= 0) ? NAN : std::log10(x); }}};
  auto it = functionMap.find(sign);
  if (it != functionMap.end()) {
    result = it->second(oneNum);
    if (std::isnan(result)) errors_ = true;
  } else {
    errors_ = true;
  }

  return result;
}

double s21::ModelCalc::MathematicsTwoArg(double oneNum, double twoNum,
                                         std::string sign) {
  double result = 0.0;
  if (sign.empty()) return result;
  using op_func = std::function<double(double, double)>;
  const static std::unordered_map<int, op_func> op_func_map_{
      {'+', std::plus<double>()},
      {'-', std::minus<double>()},
      {'*', std::multiplies<double>()},
      {'/', std::divides<double>()},
      {'%', fmodl},
      {'^', powl},
  };
  auto it = op_func_map_.find(sign[0]);
  if (it != op_func_map_.end()) {
    result = op_func_map_.at(sign[0])(oneNum, twoNum);
    if (std::isnan(result)) errors_ = true;
  } else {
    errors_ = true;
  }
  return result;
}

double s21::ModelCalc::ReadDouble() {
  std::string tmp;
  int countPoint = 0;
  for (; (isdigit(expression_[position_in_string_]) ||
          expression_[position_in_string_] == '.' ||
          expression_[position_in_string_] == 'e') ||
         (UnarySign());
       position_in_string_++) {
    if (expression_[position_in_string_] == '.') {
      countPoint++;
      if (countPoint > 1) {
        errors_ = true;
        return 0.0;
      }
    }
    tmp += expression_[position_in_string_];
  }
  position_in_string_--;
  try {
    return std::stod(tmp);
  } catch (const std::invalid_argument& error_convertation) {
    errors_ = true;
    return 0.0;
  }
}

std::string s21::ModelCalc::ReadSign() {
  std::string tmp;
  while (isalpha(expression_[position_in_string_])) {
    tmp += expression_[position_in_string_++];
  }

  const static std::unordered_set<std::string> current_sign = {
      "sin", "cos", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};
  position_in_string_--;
  if (current_sign.find(tmp) != current_sign.end()) {
    return tmp;
  } else {
    errors_ = true;
    return "\0";
  }
}

void s21::ModelCalc::Bracket() {
  while (vector_operators_.back().operators != "(" &&
         !vector_operators_.empty()) {
    vector_double_.push_back(vector_operators_.back());
    vector_operators_.pop_back();
  }
  if (!vector_operators_.empty()) vector_operators_.pop_back();
}

void s21::ModelCalc::BktCount() {
  int countBkt = 0;
  char last_symbol;
  for (char ch : expression_) {
    if (ch == '(') {
      countBkt++;
    } else if (ch == ')') {
      countBkt--;
      if (countBkt < 0 || last_symbol == '(') {
        errors_ = true;
        return;
      }
    }
    last_symbol = ch;
  }
  if (countBkt != 0 || expression_.length() > 255) {
    errors_ = true;
  }
}

std::string s21::ModelCalc::ReplaceSignBeforeOpenBracket() {
  std::string result;
  bool shouldReplaceSign = false;
  for (std::size_t i = 0; i < expression_.length(); ++i) {
    char currentChar = expression_[i];
    if (currentChar == '-' || currentChar == '+') {
      if (i + 1 < expression_.length() && expression_[i + 1] == '(') {
        shouldReplaceSign = true;
      }
    }
    if (shouldReplaceSign) {
      if (currentChar == '-') {
        result += "-1*";
      } else if (currentChar == '+') {
        result += "+1*";
      }
      shouldReplaceSign = false;
    } else {
      result += currentChar;
    }
  }
  return result;
}
