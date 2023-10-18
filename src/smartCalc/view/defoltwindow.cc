#include "defoltwindow.h"

#include "ui_defoltwindow.h"

s21::DefoltWindow::DefoltWindow(QWidget* parent)
    : QDialog(parent), ui_(new Ui::defoltwindow) {
  DefoltWindow::setFixedSize(539, 590);
  ui_->setupUi(this);
  ui_->result_number->setFocus();
  ConnectButtons();
}

s21::DefoltWindow::~DefoltWindow() { delete ui_; }

void s21::DefoltWindow::ConnectButtons() {
  for (auto button : ui_->digits->buttons()) {
    connect(button, &QPushButton::clicked, this, &DefoltWindow::DigitNumbers);
  }

  for (auto button : ui_->operation_buttons->buttons()) {
    connect(button, &QPushButton::clicked, this, &DefoltWindow::MathOperations);
  }

  for (auto button : ui_->function_buttons->buttons()) {
    connect(button, &QPushButton::clicked, this, &DefoltWindow::Functions);
  }

  connect(ui_->result, &QPushButton::clicked, this, &DefoltWindow::PushString);
  connect(ui_->back, &QPushButton::clicked, this, &DefoltWindow::BackClicked);
  connect(ui_->delete_btn, &QPushButton::clicked, this,
          &DefoltWindow::DeleteClicked);
  connect(ui_->graf_open, &QPushButton::clicked, this, &DefoltWindow::GrafOpen);
  connect(ui_->graf_close, &QPushButton::clicked, this,
          &DefoltWindow::GrafClose);
}

void s21::DefoltWindow::BackClicked() {
  this->close();
  emit firstWindow();
}

void s21::DefoltWindow::DigitNumbers() {
  QPushButton* button = (QPushButton*)sender();
  QString new_label = ui_->result_number->text() + button->text();
  ui_->result_number->setText(new_label);
}

void s21::DefoltWindow::MathOperations() {
  QPushButton* button = static_cast<QPushButton*>(sender());
  QString buttonText = button->text();
  QString new_label;
  if (!(ui_->result_number->text().endsWith(buttonText))) {
    new_label = ui_->result_number->text() + button->text();
    ui_->result_number->setText(new_label);
  }
}

void s21::DefoltWindow::Functions() {
  QPushButton* button = (QPushButton*)sender();
  ui_->result_number->setText(ui_->result_number->text() + button->text() +
                              "(");
}

void s21::DefoltWindow::DeleteClicked() { ui_->result_number->setText(""); }

void s21::DefoltWindow::PushString() {
  std::string str = ui_->result_number->text().toStdString();
  double x_value = ui_->result_x->value();
  bool error = controller_.CalcExpression(str, x_value);
  double result = controller_.GetCalcResult();
  QString num1 = QString::number(result, 'f', 6);
  if (error) {
    ui_->result_number->setText("error");
  } else {
    ui_->result_number->setText(num1);
  }
}

void s21::DefoltWindow::GrafClose() {
  if (is_graf_open_) {
    DefoltWindow::setFixedSize(539, 590);
    is_graf_open_ = false;
  }
}

void s21::DefoltWindow::GrafOpen() {
  if (!is_graf_open_) {
    DefoltWindow::setFixedSize(1275, 590);
    is_graf_open_ = true;
  }
  std::string expression = ui_->result_number->text().toStdString();
  double x_min = ui_->result_x_min->value();
  double x_max = ui_->result_x_max->value();
  double y_min = ui_->result_y_min->value();
  double y_max = ui_->result_y_max->value();
  if (x_min >= x_max || y_min >= y_max) {
    return;
  }
  QVector<double> x, y;
  GeneratePlotData(expression, x_min, x_max, y_min, y_max, x, y);
  UpdateGraph(x, y, x_min, x_max, y_min, y_max);
}

void s21::DefoltWindow::GeneratePlotData(const std::string& expression,
                                         double x_min, double x_max,
                                         double y_min, double y_max,
                                         QVector<double>& x,
                                         QVector<double>& y) {
  double h = (x_max - x_min) / 1500;
  x.clear();
  y.clear();
  for (double X = x_min; X <= x_max; X += h) {
    bool error = controller_.CalcExpression(expression, X);
    double Y = controller_.GetCalcResult();
    if (!error && Y <= y_max && Y >= y_min) {
      x.push_back(X);
      y.push_back(Y);
    }
  }
}

void s21::DefoltWindow::UpdateGraph(const QVector<double>& x,
                                    const QVector<double>& y, double x_min,
                                    double x_max, double y_min, double y_max) {
  ui_->graf->clearGraphs();
  ui_->graf->addGraph();
  ui_->graf->graph(0)->setData(x, y);
  ui_->graf->xAxis->setLabel("x");
  ui_->graf->yAxis->setLabel("y");
  ui_->graf->xAxis->setRange(x_min, x_max);
  ui_->graf->yAxis->setRange(y_min, y_max);
  ui_->graf->replot();
}
