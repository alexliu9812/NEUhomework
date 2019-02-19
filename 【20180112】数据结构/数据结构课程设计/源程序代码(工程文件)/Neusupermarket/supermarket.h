#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include <QMainWindow>
#include<fstream>
#include<sstream>
#include<iostream>
#include<QString>
#include <string>
#include <QTimer>
#include <QFile>
#include <QtNetwork>
#include <QDebug>
#include <qdatetime.h>
#include "ui_supermarket.h"
#include "quiwidget.h"
using namespace std;

namespace Ui {
class Supermarket;
}

struct Good
{
    string name;
    string id;
    double cost, price; //分别是进价和售价
    double number;
    string measure_unit, category; //计量单位和类别
    string purchase_time, sell_time; //入库、出库时间和保质期
    Good* next;
};


class Supermarket : public QMainWindow
{
    Q_OBJECT

public:
    explicit Supermarket(QWidget *parent = 0);
    ~Supermarket();
    bool ManInput(); //人工输入并创建、入库商品,成功返回1,否则0,下同
    bool BatchInput(); //批量导入
    bool BatchOutput(string dir); //导出数据
    bool OutStorage(); //出库操作
    bool SetDate(); //修改数据
    Good* SearchChild(string pid); //搜索查询部件
    void Search();
    long GetNumber(); //个数
    Good* GetLastPointer();
    bool CheckAccount(bool a = 1);//用户权限检查
    bool CheckID(string pid);
    void Statistics();//统计
    void Log(string operators, bool end_out,Good *p); //操作记录日志
    //bool Upload();
     QTime t;

private:
    Ui::Supermarket *ui;
    Good *head;
    long number;
    QStandardItemModel *pmodel;
    string loginin_account;

private slots:
    QStandardItemModel* initForm();
    void initAccount();
    void initUnAccount();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_action_O_triggered();
    void on_actionCSV_C_triggered();
    void on_action_H_triggered();
    void on_action_A_triggered();
    void on_action_B_triggered();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_4_clicked();
    void on_actiond_2_triggered();
    void on_actiond_triggered();
    void on_actiondda_triggered();

public slots:
    void timerUpdate(void);
    void timerAdd();
};

//void UpLoadForm(QString Path,QMap<QString,QString> params,QString fileFormName,QFile *uploadFile,QString newFileName);
#endif // SUPERMARKET_H
