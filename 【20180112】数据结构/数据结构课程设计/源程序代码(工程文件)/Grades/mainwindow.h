#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void Output();
    void openfile();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actiond_triggered();

    void on_actionc_triggered();

    void on_actionb_triggered();

    void on_actiona_triggered();

signals:
    void AddChartView(QChartView *chartview);
    void sendNum(int numbers,double aver, double sd);

private:
    Ui::MainWindow *ui;
    Dialog newd;

};

#endif // MAINWINDOW_H
