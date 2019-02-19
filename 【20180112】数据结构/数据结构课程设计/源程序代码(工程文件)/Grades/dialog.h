#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include<QtCharts/qpercentbarseries.h>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void getWidget(QChartView *chartView);
    void getNum(int  numbers,double aver, double sd);

private:
    Ui::Dialog *ui;
    QChartView *nchartView;

};

#endif // DIALOG_H
