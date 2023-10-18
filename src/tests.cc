#include <gtest/gtest.h>

#include "smartCalc/model/s21_model.h"

class ModelCalcTest : public ::testing::Test {
 protected:
  s21::ModelCalc calculator_test;
};

class ModelCreditTest : public ::testing::Test {
 protected:
  s21::ModelCredit credit_test;
};

TEST_F(ModelCreditTest, AnnuitCalculation) {
  credit_test.SetSumCredit(1000.0, 12, 5.0);
  credit_test.CalculateAnnuit();
  EXPECT_NEAR(credit_test.GetMonthlyPayment(), 85.61, 1e-2);
  EXPECT_NEAR(credit_test.GetTotalPayment(), 1027.29, 1e-1);
  EXPECT_NEAR(credit_test.GetOverpayment(), 27.29, 1e-2);
}

TEST_F(ModelCreditTest, DifferentCalculation) {
  credit_test.SetSumCredit(1000.0, 12, 5.0);
  credit_test.CalculateDifferent();
  std::list<s21::CreditResultField> resultList = credit_test.GetMyList();
  ASSERT_EQ(resultList.size(), 12);
  auto it = resultList.begin();
  EXPECT_NEAR(it->result_amount_per_month, 87.50, 1e-2);
  EXPECT_NEAR(it->interest_payment, 4.17, 1e-2);
  EXPECT_NEAR(it->the_balance_of_the_debt, 916.67, 1e-2);
}

TEST_F(ModelCalcTest, Calculation1) {
  std::string expression = "2+3*4";
  double x_value = 0.0;
  bool result = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(result);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), 14.0);
}

TEST_F(ModelCalcTest, Calculation2) {
  std::string expression = "2+*3";
  double x_value = 0.0;
  bool result = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_TRUE(result);
}

TEST_F(ModelCalcTest, Calculation3) {
  std::string expression = "2*x";
  double x_value = 5.0;
  bool result = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(result);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), 10.0);
}

TEST_F(ModelCalcTest, Calculation4) {
  std::string expression = "-3+5";
  double x_value = 0.0;
  bool result = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(result);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), 2.0);
}

TEST_F(ModelCalcTest, Calculation5) {
  std::string expression = "(2+3)*4";
  double x_value = 0.0;
  bool result = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(result);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), 20.0);
}

TEST_F(ModelCalcTest, Calculation6) {
  std::string expression = "2+3)*4";
  double x_value = 0.0;
  bool result = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_TRUE(result);
}

TEST_F(ModelCalcTest, Calculation7) {
  std::string expression = "sin(0.5*3.14)";
  double x_value = 0.0;
  bool result = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(result);
  EXPECT_NEAR(calculator_test.GetCalcRes(), 1.0, 1e-6);
}

TEST_F(ModelCalcTest, Calculation8) {
  std::string expression = "sin(0.5+-)";
  double x_value = 0.0;
  bool result = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_TRUE(result);
}

TEST_F(ModelCalcTest, Calculation9) {
  std::string expression("(2+3)*4/7*(25+35*3^2)");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_NEAR(calculator_test.GetCalcRes(), 971.429, 1e-3);
}

TEST_F(ModelCalcTest, Calculation10) {
  std::string expression("(-2+3)*4/25+x");
  double x_value = 215.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_NEAR(calculator_test.GetCalcRes(), 215.16, 1e-2);
}

TEST_F(ModelCalcTest, Calculation11) {
  std::string expression("-5");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), -5.0);
}

TEST_F(ModelCalcTest, Calculation12) {
  std::string expression("-4+6");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), 2.0);
}

TEST_F(ModelCalcTest, Calculation13) {
  std::string expression("124*2436^2");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), 735827904);
}

TEST_F(ModelCalcTest, Calculation14) {
  std::string expression("sin(cos(1))");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_NEAR(calculator_test.GetCalcRes(), 0.514395, 1e-6);
}

TEST_F(ModelCalcTest, Calculation15) {
  std::string expression("cos(1)");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_NEAR(calculator_test.GetCalcRes(), 0.540302, 1e-6);
}

TEST_F(ModelCalcTest, Calculation16) {
  std::string expression(
      "312543674585664542132425364758693125436745856645421324253647586931254367"
      "458566454213242536475869312543674585664542132425364758693125436745856645"
      "421324253647586931254367458566454213242536475869312543674512856645421324"
      "253647586931254367458566454213242536475869");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_TRUE(error);
}

TEST_F(ModelCalcTest, Calculation17) {
  std::string expression("error");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_TRUE(error);
}

TEST_F(ModelCalcTest, Calculation18) {
  std::string expression("tan(0.6)");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_NEAR(calculator_test.GetCalcRes(), 0.684136, 1e-6);
}

TEST_F(ModelCalcTest, Calculation19) {
  std::string expression("(-4)+6");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), 2.0);
}

TEST_F(ModelCalcTest, Calculation20) {
  std::string expression("+1*(4)");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), 4.0);
}

TEST_F(ModelCalcTest, Calculation21) {
  std::string expression("123/123^3+1*(cos(sin(4))+135^2*(4))");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_NEAR(calculator_test.GetCalcRes(), 72900.727101, 1e-6);
}

TEST_F(ModelCalcTest, Calculation22) {
  std::string expression("-(4)");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), -4.0);
}

TEST_F(ModelCalcTest, Calculation23) {
  std::string expression("log(100)+ln((1/7)^2)");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_NEAR(calculator_test.GetCalcRes(), -1.891820, 1e-6);
}

TEST_F(ModelCalcTest, Calculation24) {
  std::string expression("log(-1000)");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_TRUE(error);
}

TEST_F(ModelCalcTest, Calculation25) {
  std::string expression("asin(5)");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_TRUE(error);
}

TEST_F(ModelCalcTest, Calculation26) {
  std::string expression("3%0");
  double x_value = 0.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_TRUE(error);
}

TEST_F(ModelCalcTest, Calculation27) {
  std::string expression("(2*x)");
  double x_value = 5.0;
  bool error = calculator_test.CalculateTheExpression(expression, x_value);
  ASSERT_FALSE(error);
  EXPECT_DOUBLE_EQ(calculator_test.GetCalcRes(), 10.0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
