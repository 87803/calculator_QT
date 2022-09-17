#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "SqStack.cpp"
#include"calculator.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString displayNum="0";
    QString historyRecord;
    bool isPointAppear=false;//标识当前数字中是否出现过小数点
    SqStack<bool>* pointStack;
    calculator calcul;
    virtual void keyPressEvent(QKeyEvent *ev);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_15_clicked();


    void on_pushButton_4_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_3_clicked();



    void on_num0Button_clicked();

    void on_num1Button_clicked();

    void on_num2Button_clicked();

    void on_num3Button_clicked();

    void on_num4Button_clicked();

    void on_num5Button_clicked();

    void on_num6Button_clicked();

    void on_num7Button_clicked();

    void on_num8Button_clicked();

    void on_num9Button_clicked();

    void on_addButton_clicked();

    void on_subButton_clicked();

    void on_mulButton_clicked();

    void on_divButton_clicked();

    void on_clearButton_clicked();

    void on_action_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void clickNumber(char c);
    void clickOperator(char c);
    void clickPoint();
    void clickLeftParen();
    void clickRightParen();
    void clickEqual();
    void clickClear();
    void clickBackspace();
};
#endif // MAINWINDOW_H
