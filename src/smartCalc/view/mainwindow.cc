#include "mainwindow.h"

#include <QPixmap>

#include "ui_mainwindow.h"

s21::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  QPixmap kavai_1(":/new/img/kavai_3.png");
  int w1 = ui_->kavai_1->width();
  int h1 = ui_->kavai_1->height();
  ui_->kavai_1->setPixmap(kavai_1.scaled(w1, h1, Qt::KeepAspectRatio));

  QPixmap kavai_2(":/new/img/kavai_1.jpeg");
  int w2 = ui_->kavai_2->width();
  int h2 = ui_->kavai_2->height();
  ui_->kavai_2->setPixmap(kavai_2.scaled(w2, h2, Qt::KeepAspectRatio));

  defolt_window_ = new DefoltWindow();
  connect(defolt_window_, &DefoltWindow::firstWindow, this, &MainWindow::show);

  credit_window_ = new CreditWindow();
  connect(credit_window_, &CreditWindow::SecondWindow, this, &MainWindow::show);

  connect(ui_->calculator, &QPushButton::clicked, this,
          &MainWindow::Calculator);
  connect(ui_->credit_calculator, &QPushButton::clicked, this,
          &MainWindow::CreditCalculator);
}

s21::MainWindow::~MainWindow() {
  delete ui_;
  delete credit_window_;
  delete defolt_window_;
}

void s21::MainWindow::CreditCalculator() {
  credit_window_->show();
  this->close();
}

void s21::MainWindow::Calculator() {
  defolt_window_->show();
  this->close();
}
