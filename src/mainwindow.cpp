#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // init
  this->setWindowTitle("Stopwatch");
  ms = s = m = 0;

  // buttons
  startButton = new QPushButton(this);
  startButton->setText("Start");
  startButton->setGeometry(10, 10, 75, 25);
  connect(startButton, SIGNAL(clicked()), this, SLOT(start()));

  resetButton = new QPushButton(this);
  resetButton->setText("Reset");
  resetButton->setGeometry(90, 10, 75, 25);
  connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
 
  checkButton = new QPushButton(this);
  checkButton->setText("check");
  checkButton->setGeometry(180, 10, 75, 25);
  connect(checkButton, SIGNAL(clicked()), this, SLOT(check()));

  // label
  label = new QLabel(this);
  label->setGeometry(0, 100, 550, 100);
  QFont font = label->font();
  font.setPointSize(40);
  font.setBold(true);
  label->setFont(font);
  label->setText(intToQString(m) + ":" + intToQString(s) + ":" +
                 intToQString(ms));

  // label
  label2 = new QLabel(this);
  label2->setGeometry(0, 250, 550, 250);
  QFont font2 = label2->font();
  font.setPointSize(40);
  font.setBold(true);
  label2->setFont(font);
  label2->setText(intToQString(m) + ":" + intToQString(s) + ":" +
                  intToQString(ms));

  // timer
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(changeTime()));
}

MainWindow::~MainWindow() { delete ui; }

QString MainWindow::intToQString(int num) {
  QString str = QString::number(num);

  if (str.length() == 1) {
    str = "0" + str;
  }

  return str;
}

void MainWindow::changeTime() {
  ms++;
  if (ms >= 100) {
    ms = 0;
    s++;
  }
  if (s >= 60) {
    s = 0;
    m++;
  }
  //...
  label->setText(intToQString(m) + ":" + intToQString(s) + ":" +
                 intToQString(ms));
}

void MainWindow::start() {
  timer->start(10);
  startButton->setText("Stop");
  connect(startButton, SIGNAL(clicked()), this, SLOT(stop()));
}

void MainWindow::stop() {
  timer->stop();
  startButton->setText("Start");
  connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
}

void MainWindow::check() {
  startButton->setText("check");
  label2->setText(intToQString(m) + ":" + intToQString(s) + ":" +
                  intToQString(ms));
}

void MainWindow::reset() {
  ms = s = m = 0;
  label->setText(intToQString(m) + ":" + intToQString(s) + ":" +
                 intToQString(ms));

  label2->setText(intToQString(m) + ":" + intToQString(s) + ":" +
                 intToQString(ms));
  stop();

}
