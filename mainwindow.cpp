#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("计算器By ZJX");
    ui->label->setText(displayNum);
    pointStack=new SqStack<bool>;
    this->grabKeyboard();
    ui->textBrowser->setText("欢迎使用计算器程序(*^_^*)\n历史记录将在这里显示~");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clickNumber(char c)
{
    if(displayNum=="0")
        displayNum=c;
    else if(displayNum[displayNum.length()-1]==')'&&displayNum.length()-2>=0&&
            displayNum[displayNum.length()-2]!=')')
    {
        displayNum+="*";
        displayNum+=c;
        pointStack->push(isPointAppear);
        isPointAppear=false;
    }
    else
        displayNum+=c;
    ui->label->setText(displayNum);
}

void MainWindow::clickOperator(char c)
{
    if(displayNum[displayNum.length()-1]=='+'||displayNum[displayNum.length()-1]=='-'||
            displayNum[displayNum.length()-1]=='*'||displayNum[displayNum.length()-1]=='/')
       displayNum[displayNum.length()-1]=c;
    else if(displayNum[displayNum.length()-1]!='(')
        displayNum+=c;
    ui->label->setText(displayNum);
    pointStack->push(isPointAppear);
    isPointAppear=false;
}

void MainWindow::clickPoint()
{
    if(!isPointAppear)
    {
        if(displayNum[displayNum.length()-1]>='0'&&displayNum[displayNum.length()-1]<='9')
            displayNum+=".";
        else
            displayNum+="0.";
        isPointAppear=true;
        ui->label->setText(displayNum);
    }
}

void MainWindow::clickLeftParen()
{
    if(displayNum=="0")
        displayNum="(";
    else if((displayNum[displayNum.length()-1]>='0'&&displayNum[displayNum.length()-1]<='9')
            ||displayNum[displayNum.length()-1]=='.'||displayNum[displayNum.length()-1]==')')
    {
        displayNum+="*(";
        pointStack->push(isPointAppear);
        isPointAppear=false;
    }
    else
        displayNum+="(";
    ui->label->setText(displayNum);
}

void MainWindow::clickRightParen()
{
    if((displayNum[displayNum.length()-1]>='0'&&displayNum[displayNum.length()-1]<='9')
            ||displayNum[displayNum.length()-1]=='.'||displayNum[displayNum.length()-1]==')')
        displayNum+=")";//条件
    else
        displayNum+="0)";
    ui->label->setText(displayNum);
}

void MainWindow::clickEqual()
{
    delete pointStack;
    pointStack=new SqStack<bool>;
    calcul.setInfixExpression(displayNum.toStdString());
    if(QString::fromStdString(calcul.isExpressionLegal())=="无格式错误")
    {
        string traverseResult;
        QString temp=displayNum+"=";
        displayNum=QString::number(calcul.getResult(traverseResult),10,6);
        if(displayNum=="inf"||displayNum=="-inf")
            displayNum="除数不可以为0";
        historyRecord=temp+displayNum+"\n"+QString::fromStdString(traverseResult)
                +"\n————————————————————————\n"+historyRecord;
        ui->label->setText(displayNum);
        isPointAppear=true;//计算结果一定带小数点
        if(displayNum=="除数不可以为0")
            displayNum="0";
    }
    else
    {
        displayNum=QString::fromStdString(calcul.isExpressionLegal());
        historyRecord=QString::fromStdString(calcul.isExpressionLegal())
                +"\n————————————————————————\n"+historyRecord;
        ui->label->setText(displayNum);
        displayNum="0";
    }
     ui->textBrowser->setText(historyRecord);
}

void MainWindow::clickClear()
{
    displayNum="0";
    isPointAppear=false;//
    ui->label->setText(displayNum);
    delete pointStack;
    pointStack=new SqStack<bool>;
}

void MainWindow::clickBackspace()
{
    if(displayNum.length()==1)
        displayNum="0";
    else if(displayNum[displayNum.length()-1]=='.')
    {
        displayNum = displayNum.left(displayNum.length() - 1);//截取最后一个字符
        isPointAppear=false;
    }
    else if(displayNum[displayNum.length()-1]=='+'||displayNum[displayNum.length()-1]=='-'
            ||displayNum[displayNum.length()-1]=='+'||displayNum[displayNum.length()-1]=='+')
    {
        displayNum = displayNum.left(displayNum.length() - 1);//截取最后一个字符
        pointStack->pop(isPointAppear);
    }
    else
        displayNum = displayNum.left(displayNum.length() - 1);//截取最后一个字符
    ui->label->setText(displayNum);
}

void MainWindow::on_action_triggered()
{
    QFile historyFile("historyData.txt");
    historyFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outfile(&historyFile);
    outfile<<historyRecord;
    ui->textBrowser->setText("历史记录已保存到historyData.txt");
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() >= '0'&&ev->key() <= '9')
        clickNumber(ev->key());
    else if(ev->key()=='+'||ev->key()=='-'||ev->key()=='*'||ev->key()=='/')
        clickOperator(ev->key());
    else
    {
        switch(ev->key()){
        case '.':clickPoint();break;
        case '(':clickLeftParen();break;
        case ')':clickRightParen();break;
        case '=':
        case Qt::Key_Return:clickEqual();break;
        case Qt::Key_Backspace:clickBackspace();break;
        case Qt::Key_Escape:clickClear();break;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    historyRecord="";
    ui->textBrowser->setText("历史记录已清空！");
}

void MainWindow::on_pushButton_2_clicked()
{
    clickLeftParen();
}

void MainWindow::on_pushButton_15_clicked()
{
    clickPoint();
}


void MainWindow::on_pushButton_4_clicked()
{
    clickBackspace();
}

void MainWindow::on_pushButton_16_clicked()
{
    clickEqual();
}


void MainWindow::on_pushButton_3_clicked()
{
    clickRightParen();
}


void MainWindow::on_num0Button_clicked()
{
    clickNumber('0');
}


void MainWindow::on_num1Button_clicked()
{
    clickNumber('1');
}


void MainWindow::on_num2Button_clicked()
{
    clickNumber('2');
}


void MainWindow::on_num3Button_clicked()
{
    clickNumber('3');
}


void MainWindow::on_num4Button_clicked()
{
    clickNumber('4');
}


void MainWindow::on_num5Button_clicked()
{
    clickNumber('5');
}


void MainWindow::on_num6Button_clicked()
{
    clickNumber('6');
}


void MainWindow::on_num7Button_clicked()
{
    clickNumber('7');
}


void MainWindow::on_num8Button_clicked()
{
    clickNumber('8');
}


void MainWindow::on_num9Button_clicked()
{
    clickNumber('9');
}


void MainWindow::on_addButton_clicked()
{
    clickOperator('+');
}


void MainWindow::on_subButton_clicked()
{
    clickOperator('-');
}


void MainWindow::on_mulButton_clicked()
{
    clickOperator('*');
}


void MainWindow::on_divButton_clicked()
{
    clickOperator('/');
}

void MainWindow::on_clearButton_clicked()
{
    clickClear();
}

/*  按钮样式表
setStyleSheet(
                   //正常状态样式
                   "QPushButton{"
                   "background-color:rgba(100,225,100,30);"//背景色（也可以设置图片）
                   "border-style:outset;"                  //边框样式（inset/outset）
                   "border-width:4px;"                     //边框宽度像素
                   "border-radius:10px;"                   //边框圆角半径像素
                   "border-color:rgba(255,255,255,30);"    //边框颜色
                   "font:bold 10px;"                       //字体，字体大小
                   "color:rgba(0,0,0,100);"                //字体颜色
                   "padding:6px;"                          //填衬
                   "}"
                   //鼠标按下样式
                   "QPushButton:pressed{"
                   "background-color:rgba(100,255,100,200);"
                   "border-color:rgba(255,255,255,30);"
                   "border-style:inset;"
                   "color:rgba(0,0,0,100);"
                   "}"
                   //鼠标悬停样式
                   "QPushButton:hover{"
                   "background-color:rgba(100,255,100,100);"
                   "border-color:rgba(255,255,255,200);"
                   "color:rgba(0,0,0,200);"
                   "}");
*/

