#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#define BUTTON_PREF1 "QPushButton {background-color: #C7E1A8;border: 5px double  #F9FBE7;color: #769357;border-right: 4px solid #C6C8B5;border-bottom: 5px solid #C6C8B5 ;}QPushButton:pressed {background-color: #f9fbe7;border: 5px double  #C6C8B5;padding: 5px;color: #769357;}"
#define BUTTON_PREF2 "QPushButton {background-color: #f9fbe7;border: 5px double  #DCEDC8;color: #769357;border-right: 4px solid #C6C8B5;border-bottom: 5px solid #C6C8B5 ;}QPushButton:pressed {background-color: #C7E1A8;border: 5px double  #F9FBE7;padding: 5px;color: #769357;}"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool inverseBut;
    bool buttonX;
    double xBegin, xEnd, h, X;
    double N;
    QVector<double> x,y;


private slots:
    void pressed();
    void equalPressed();
    void inverseButton();
    void xInLine();
    void on_eraseButton_clicked();
    void on_toolButton_clicked();
};

#endif // MAINWINDOW_H
