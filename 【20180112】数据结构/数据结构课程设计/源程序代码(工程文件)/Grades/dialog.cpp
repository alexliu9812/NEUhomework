#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{

    ui->verticalLayout->removeWidget(nchartView);
    delete ui;
}

void Dialog::getWidget(QChartView *chartView)
{
    ui->verticalLayout->removeWidget(nchartView);
    nchartView = chartView;
    ui->verticalLayout->addWidget(nchartView);
}

void Dialog::getNum(int numbers, double aver, double sd)
{
    ui->label_2->setText(QString::number(numbers,10,2));
    ui->label_3->setText(QString::number(aver,10,2));
    ui->label_4->setText(QString::number(sd,10,2));
}
