#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

// https://stackoverflow.com/questions/46700702/how-to-change-the-intensity-of-curve-colour-in-qcustomplot-with-respect-to-x-axi
#include <QDebug>
extern "C" {
#include "s21_smartCalc.h"
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      inverseBut(false)
{
    ui->setupUi(this);
    ui->doubleX->hide();
    ui->nameX->hide();
    this->setFixedSize(QSize(460, 517));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; ++i){
        QString butName = "button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(clicked()), this, SLOT(pressed()));
    }
    connect(ui->buttonSum, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->buttonMult, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->buttonDiv, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->buttonDiff, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->buttonClBr, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->buttonOpBr, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->buttonCom, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->buttonPow, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->buttonEqual, SIGNAL(clicked()), this, SLOT(equalPressed()));
    connect(ui->buttonMod, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->case_2, SIGNAL(clicked()), this, SLOT(inverseButton()));
    connect(ui->buttonX, SIGNAL(clicked()), this, SLOT(pressed()));
    connect(ui->Display, SIGNAL(textChanged(QString)), this, SLOT(xInLine()));
}

void MainWindow::xInLine() {
    if (ui->Display->text().contains("x")) {
        ui->nameX->show();
        ui->doubleX->show();

    } else {
        ui->nameX->hide();
        ui->doubleX->hide();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString str = ui->Display->text();
    if (str == "0.0" || str == "Syntax error" || str == "Undefined" || str == "Too many signs") {
        ui->Display->setText(butVal);
    } else {
        ui->Display->insert(butVal);
    }
    if (butVal.endsWith("s") || butVal.endsWith("n") || butVal.endsWith("t") || butVal.endsWith("g")) {
        ui->Display->insert("(");
    }
}


void MainWindow::equalPressed() {
    QString str1 = ui->Display->text();
     QByteArray ba = str1.toLatin1();
      char *c_str2 = ba.data();
      if (strlen(c_str2) > MAXSTRLEN) {
          ui->Display->setText("Too many signs");
     } else { int x = 0;
     int syntax = SyntaxError(c_str2,&x);
     if (syntax) {
         ui->Display->setText("Syntax error");
     } else {
         double val = 0.0;
         if (x) {
             val = ui->doubleX->value();
         }
         char output[MAXSTRLEN * 2] = {' '};
         int length = ConvertToRPN(c_str2, output);
         double ans = Calculate(output, length, val);
         if (ans != ans) {
             ui->Display->setText("Undefined");
         } else {
             QString finalStr = QString::number(ans);
             ui->Display->setText(finalStr);
        }
     }
   }
}

void MainWindow::inverseButton() {
    if (inverseBut == false) {
        inverseBut = true;
        ui->case_2->setText("2nd");
        ui->case_2->setStyleSheet(BUTTON_PREF1);
        ui->buttonMult->setText("sin");
        ui->buttonMult->setStyleSheet(BUTTON_PREF2);
        ui->buttonOpBr->setText("asin");
        ui->buttonOpBr->setStyleSheet(BUTTON_PREF2);
        ui->buttonDiff->setText("cos");
        ui->buttonDiff->setStyleSheet(BUTTON_PREF2);
        ui->buttonClBr->setText("acos");
        ui->buttonClBr->setStyleSheet(BUTTON_PREF2);
        ui->buttonSum->setText("tan");
        ui->buttonSum->setStyleSheet(BUTTON_PREF2);
        ui->buttonPow->setText("atan");
        ui->buttonPow->setStyleSheet(BUTTON_PREF2);
        ui->buttonMod->setText("ln");
        ui->buttonMod->setStyleSheet(BUTTON_PREF2);
        ui->buttonX->setText("log");
        ui->buttonX->setStyleSheet(BUTTON_PREF2);
        ui->buttonDiv->setText("sqrt");
        ui->buttonDiv->setStyleSheet(BUTTON_PREF2);
        ui->buttonEqual->setStyleSheet(BUTTON_PREF1);
        ui->eraseButton->setStyleSheet(BUTTON_PREF1);
        ui->eraseButton->setText("<-");
    } else {
        inverseBut = false;
        ui->case_2->setText("1st");
        ui->case_2->setStyleSheet(BUTTON_PREF2);
        ui->buttonMult->setStyleSheet(BUTTON_PREF1);
        ui->buttonMult->setText("*");
        ui->buttonOpBr->setStyleSheet(BUTTON_PREF1);
        ui->buttonOpBr->setText("(");
        ui->buttonDiff->setStyleSheet(BUTTON_PREF1);
        ui->buttonDiff->setText("-");
        ui->buttonClBr->setStyleSheet(BUTTON_PREF1);
        ui->buttonClBr->setText(")");
        ui->buttonSum->setStyleSheet(BUTTON_PREF1);
        ui->buttonSum->setText("+");
        ui->buttonPow->setStyleSheet(BUTTON_PREF1);
        ui->buttonPow->setText("^");
        ui->buttonMod->setStyleSheet(BUTTON_PREF1);
        ui->buttonMod->setText("%");
        ui->buttonX->setStyleSheet(BUTTON_PREF1);
        ui->buttonX->setText("x");
        ui->buttonDiv->setStyleSheet(BUTTON_PREF1);
        ui->buttonDiv->setText("/");
        ui->eraseButton->setStyleSheet(BUTTON_PREF2);
        ui->eraseButton->setText("AC");
        ui->buttonEqual->setStyleSheet(BUTTON_PREF2);
    }
}



void MainWindow::on_eraseButton_clicked()
{
    QString text = ui->Display->text();
    if (inverseBut == false || text == "0.0" || text == "Syntax error" || text == "Undefined" ||  text == "Too many signs") {
    this->setFixedSize(QSize(460, 517));
    if(ui->widget->graphCount()) ui->widget->clearGraphs();
    ui->nameX->hide();
    ui->doubleX->hide();
    ui->Display->setText("0.0");
    } else {
        text.chop(1);
        if (text.isEmpty()) ui->Display->setText("0.0");
        else ui->Display->setText(text);
    }
}


void MainWindow::on_toolButton_clicked()
{
    if(ui->widget->graphCount()) ui->widget->clearGraphs();
    ui->widget->setBackground(QColor::fromRgb(199,225,168));
    this->setFixedSize(QSize(903, 517));
    xBegin = ui->xFrom->value();
    xEnd = ui->xTo->value();
    ui->widget->xAxis->setRange(ui->xFrom->value(), ui->xTo->value());
    ui->widget->yAxis->setRange(ui->xFrom->value(), ui->xTo->value());
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom,true);
    ui->widget->setInteraction(QCP::iRangeDrag,true);

    N = 10000;
    h = (xEnd - xBegin)/N ;

    QString str1 = ui->Display->text();
     QByteArray ba = str1.toLatin1();
    char *c_str2 = ba.data();
    int inX = 0;
    int syntax = SyntaxError(c_str2,&inX);

    if (syntax) {
        ui->Display->setText("Syntax error");
    } else {
        char output[MAXSTRLEN * 2] = {' '};
        int length = ConvertToRPN(c_str2, output);
        for(X = xBegin; X <= xEnd; X += h)
        {
           x.push_back(X);
           y.push_back(Calculate(output, length, X));
        }
    if(!ui->widget->graphCount()) {
        ui->widget->addGraph();
        ui->widget->xAxis->setBasePen(QPen(QColor::fromRgb(105, 133, 89)));
            ui->widget->xAxis->setLabelColor(QColor::fromRgb(105, 133, 89));
            ui->widget->xAxis->setTickLabelColor(QColor::fromRgb(105, 133, 89));
            ui->widget->xAxis->setTickPen(QPen(QColor::fromRgb(105, 133, 89)));
            ui->widget->xAxis->setSubTickPen(QPen(QColor::fromRgb(105, 133, 89)));
            ui->widget->yAxis->setBasePen(QPen(QColor::fromRgb(105, 133, 89)));
            ui->widget->yAxis->setLabelColor(QColor::fromRgb(105, 133, 89));
            ui->widget->yAxis->setTickLabelColor(QColor::fromRgb(105, 133, 89));
            ui->widget->yAxis->setTickPen(QPen(QColor::fromRgb(105, 133, 89)));
            ui->widget->yAxis->setSubTickPen(QPen(QColor::fromRgb(105, 133, 89)));
    }
    QLinearGradient gradient(ui->widget->rect().topLeft(), ui->widget->rect().topRight());
    gradient.setColorAt(0.0, QColor::fromRgb(105, 133, 89));
    gradient.setColorAt(1.0, QColor::fromRgb(199, 225, 168));
    QPen pen(gradient, 5);
    ui->widget->graph(0)->setPen(pen);
    ui->widget->graph(0)->addData(x,y);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);
    ui->widget->replot();
    x.clear();
    y.clear();
    }
}

