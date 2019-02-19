#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BST.h"
#include <cmath>
#include<QMessageBox>
#include<QFile>
#include<QFileDialog>
#include<QDesktopServices>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(AddChartView(QChartView*)),&newd,SLOT(getWidget(QChartView*)));
    connect(this,SIGNAL(sendNum(int,double,double)),&newd,SLOT(getNum(int,double,double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//string向int转换函数
template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

void MainWindow::Output()
{
    QBarSeries *series = new QBarSeries();
    QChart *chart = new QChart();
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QChartView *chartView = new QChartView(chart);
    QBarSet *set0[300];
    QStringList categories;

    int i=0,j=0,m,n;
    double k,l,sum=0;
    double sum_Num=0,sd=0;

    //1.读文件,即收集数据阶段
    n = ui->lineEdit->text().toInt();
    n--;
    QString filename = "data.csv";
    if(filename == "")
    {
        QMessageBox::information(this,"警告","还没有导入文件或者文件不正确.");
    }
    else{
        ifstream inFile(filename.toStdString(), ios::in);
        string lineStr;
        std::vector<int>vec;
        // vector<vector<string>> strArray;
        //确定多少行
        getline(inFile, lineStr);
        // 存成二维表结构
        stringstream ss(lineStr);
        string str;
        // 按照逗号分隔
        while (getline(ss, str, ','))
        {
            j++;
        }
        if(n>j||n<0)
        {
            QMessageBox::information(this, "警告","您输入的科目数不正确，请检查导入的文件再重新输入.");
        }
        else{
            while (getline(inFile, lineStr))
            {
                // 打印整行字符串
                // 存成二维表结构
                stringstream ss(lineStr);
                string str;
                //vector<string> lineArray;
                // 按照逗号分隔
                j=0;
                while (getline(ss, str, ','))
                {
                    if(j==n)
                        vec.push_back(stringToNum<int>(str));
                    j++;
                }
                //i++;
            }
            ui->textBrowser->append("AllNum:"+QString::number(vec.size()));
            /*
    for (i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    */
            //将数据存入二叉排序树并计算频率
            BST BST(vec);
            std::vector<int>result;
            std::vector<int>Num;
            BST.InorderTraversal( result, Num );
            ui->textBrowser->append("Number:"+QString::number(result.size()));

            //2.计算极差确定组距
            k = 1 + 3.322*log(double(result.back()-result[0]));//分的组数
            l = (result.back()-result[0])/int(k);//每组含有的成绩范围大小
            ui->textBrowser->append("Size of k:"+QString::number(k));

            //3.分组
            //result[0]是横坐标第一个数,后面的数依次增加 l
            std::vector<double>result_sum;
            for(i=0;i<(int(k)+3);i++)
            {
                result_sum.push_back(result[0]+l*i);
                //cout<<result_sum[i]<<" ";

            }
            for(i=0;i<(int(k)+3)-1;i++)
                set0[i] = new QBarSet(QString::number(result_sum[i])+"-"+QString::number(result_sum[i+1]));
            set0[(int(k)+3)-1] = new QBarSet(QString::number(result_sum[(int(k)+3)-1])+"-"+QString::number(result_sum[(int(k)+3)-1]+l*((int(k)+3)-1)));

            //4.计算各组频率值
            std::vector<double>Num_sum;
            m=double(vec.size());
            for(i = 0,j=0; i < Num.size();i++)
            {
                if(result[i]>=result_sum[j+1])
                {
                    Num_sum.push_back(sum_Num/m);
                    sum_Num=0;
                    j++;
                }
                else if(i==(Num.size()-1))
                {
                    sum_Num += double(Num[i]);
                    Num_sum.push_back(sum_Num/m);
                    sum_Num=0;
                }
                sum_Num += double(Num[i]);
            }
            for (i = 0; i < Num_sum.size(); i++)
            {
                //   cout<<result_sum[i]<<endl<<"  "<<Num_sum[i];
                ui->textBrowser->append(QString::number(result_sum[i],10,4)+":"+QString::number(Num_sum[i],10,4));
                *set0[i] <<Num_sum[i];
                series->append(set0[i]);
                sum+=(result_sum[i]+l/2)*Num_sum[i];
            }
            for(i=0;i<Num_sum.size();i++)
            {
                sd+=(result_sum[i]+l/2-sum)*(result_sum[i]+l/2-sum)*Num_sum[i];
            }
            sd=sqrt(sd);
            /*
    cout<<"样本容量为"<<vec.size()<<endl;
    cout<<"平均数为"<<sum<<endl;
    cout<<"样本标准差"<<sd<<endl;
    */
            emit sendNum(vec.size(),sum,sd);
            chart->addSeries(series);
            chart->setTitle("学生成绩直方图");
            chart->setAnimationOptions(QChart::SeriesAnimations);
            categories<<"成绩统计";
            axis->append(categories);
            chart->createDefaultAxes();
            chart->setAxisX(axis, series);
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);
            chartView->setRenderHint(QPainter::Antialiasing);
            emit AddChartView(chartView);
            newd.show();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    Output();
}

void MainWindow::on_actiond_triggered()
{
    openfile();
}

void MainWindow::openfile()
{
    QString   filename = QFileDialog::getOpenFileName(this,
                                                      tr("选择导入的数据文件"),
                                                      "",
                                                      tr("CSV数据 (*.csv)")); //选择路径
    QFile::remove("data.csv");
    if(!QFile::copy(filename,"data.csv"))
    {
        QMessageBox::information(this,"警告","导入文件出错.");
    }
}

//帮助
void MainWindow::on_actionc_triggered()
{
    QMessageBox::information(this,"帮助","导入数据->输入科目->点击Go->完成.");
}

//反馈
void MainWindow::on_actionb_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://wj.qq.com/s/1779199/3182/")));
}

//关于
void MainWindow::on_actiona_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("http://60.205.215.163/")));
    QMessageBox::information(this,"关于...","此程序核心为二叉搜索树，QT开发。");
}
