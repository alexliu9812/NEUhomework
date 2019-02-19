#include "supermarket.h"

Supermarket::Supermarket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Supermarket)
{
    //界面初始化
    ui->setupUi(this);
    QUIWidget::setFormInCenter(this);
    pmodel = this->initForm();

    //数据初始化
    number = 0;
    head = NULL;
    loginin_account = "";

    //时间初始化
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    connect(timer,SIGNAL(timeout()),this,SLOT(timerAdd()));
    timer->start(1000);
}

Supermarket::~Supermarket()
{
    delete ui;
    Good *p;
    for(p=head; p->next!=NULL; p=p->next)
    {
        delete p;
    }
    delete p;
}

void Supermarket::initUnAccount()
{
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);
    ui->label_14->setVisible(false);
    ui->label_15->setVisible(false);
    ui->label_16->setVisible(false);
    ui->label_17->setVisible(false);
    ui->label_18->setVisible(false);
    ui->pushButton_4->setVisible(false);
    // ui->tab_6->setVisible(false);

    ui->label_28->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_26->setVisible(true);
    ui->label_27->setVisible(true);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->pushButton->setVisible(true);
}

QStandardItemModel* Supermarket::initForm()
{
    initUnAccount();
    QUIWidget::setStyle(QUIWidget::Style_Silvery);
    QStandardItemModel *model = new QStandardItemModel();
    ui->tableView->setModel(model);
    return model;
}

//当前时间
void Supermarket::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->label_10->setText(str);
}

//计时器
void Supermarket::timerAdd()
{
    QString hour = QString::number(t.elapsed()/3600000);
    QString min = QString::number((t.elapsed()%3600000)/60000);
    QString sec = QString::number((t.elapsed()%60000)/1000);
    QString str = hour+"小时"+min+"分钟"+sec+"秒";
    ui->label_9->setText(str);
    Statistics();
}

//账户登录
void Supermarket::on_pushButton_clicked()
{
    string file_name = "user//account.csv",line_str,str;
    ifstream read_account(file_name,ios::in);
    string on_loginin_account = ui->lineEdit_3->text().toStdString();
    string on_loginin_account_password = ui->lineEdit_4->text().toStdString();
    string file_login_account, file_login_account_password;
    while(getline(read_account,line_str))
    {
        stringstream ss(line_str);
        getline(ss,str,',');
        file_login_account = str;
        getline(ss,str,',');
        file_login_account_password = str;
        if(on_loginin_account == file_login_account && on_loginin_account_password == file_login_account_password)
        {
            loginin_account = on_loginin_account;
            initAccount();
        }
    }
    if(loginin_account == "")
        QUIWidget::showMessageBoxError("账号或密码错误。请重新输入或者联系超市BOSS.",5);
}

//初始化账户
void Supermarket::initAccount()
{
    t.restart();
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->label_8->setVisible(true);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_11->setVisible(true);
    ui->label_12->setVisible(true);
    ui->label_13->setVisible(true);
    ui->label_14->setVisible(true);
    ui->label_15->setVisible(true);
    ui->label_16->setVisible(true);
    ui->label_17->setVisible(true);
    ui->label_18->setVisible(true);
    ui->pushButton_4->setVisible(true);

    ui->label_28->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_26->setVisible(false);
    ui->label_27->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->pushButton->setVisible(false);

    ui->label_7->setText(QString::fromStdString(loginin_account));
    if(loginin_account == "root")
    {
        ui->label_8->setText("超级管理员");
        //ui->tab_6->setVisible(true);
    }
    else ui->label_8->setText("普通管理员");

}

//账户权限检查(三级:超管,管理,游客;a =0 为超管)
bool Supermarket::CheckAccount(bool a)
{
    if(a == 0)
    {
        if(loginin_account == "root")
            return 1;
        else
        {
            QUIWidget::showMessageBoxInfo("此操作只有大BOSS可以执行.",5);
            return 0;
        }
    }
    else if(a == 1)
    {
        if(loginin_account == "")
        {
            QUIWidget::showMessageBoxInfo("此操作只有登陆后才可以执行.",5);
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        QUIWidget::showMessageBoxError("程序员写错代码了，快拿他祭天.(错误代码:0X00001)",5);
        return 0;
    }
}

//批量写入
void Supermarket::on_action_O_triggered()
{
    if(CheckAccount(0))
        BatchInput();
}

//导出CSV
void Supermarket::on_actionCSV_C_triggered()
{
    //string dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home",         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks).toStdString();
    if(CheckAccount(0))
    {
        string dir = QUIWidget::getFolderName().toStdString();
        BatchOutput(dir);
        QString sdir = QString::fromStdString(dir);
        QDesktopServices::openUrl(QUrl::fromLocalFile(sdir));
    }
}


void Supermarket::on_actiondda_triggered()
{
    if(CheckAccount(0))
    {
        BatchOutput("user");
        string dir = QUIWidget::getFolderName().toStdString();
        QProcess process(this);
        process.start("Des3.exe -l user\\Data.csv qwertyuiop user\\Locked_Data.qzq");
        process.terminate();
        process.waitForFinished();
        process.close();
        QString sdir = QString::fromStdString(dir);
        QString ssdir = sdir+"\\Locked_Data.qzq";
        QFile::remove(ssdir);
        QUIWidget::copyFile("user\\Locked_Data.qzq",ssdir);
        QDesktopServices::openUrl(QUrl::fromLocalFile(sdir));
        QFile::remove("user\\Data.csv");
        QFile::remove("user\\Locked_Data.qzq");
    }
    else
    {
        QUIWidget::showMessageBoxError("只有BOSS可以执行这个操作.");
    }
}

//清空数据库
void Supermarket::on_actiond_2_triggered()
{
    if(CheckAccount(0))
    {
        Good *p = head;
        if(p == NULL)
        {
            QUIWidget::showMessageBoxInfo("数据库已经是空的啦！",5);
        }
        else
        {
            int i = QUIWidget::showMessageBoxQuestion("您确认要清空嘛？");
            //ui->statusbar->showMessage(QString::number(i),20000);
            if(i == 16384)
            {
                ui->statusbar->showMessage("正在清空...",2000);
                p = p->next;
                for(;p!=NULL;p=p->next)
                {
                    delete p;
                }
                head = NULL;
                number = 0;

                ui->statusbar->clearMessage();
                ui->statusbar->showMessage("清理完毕.",3000);
            }
            else
            {
                QUIWidget::showMessageBoxInfo("我什么也没做.",5);
            }
        }
    }
}

void Supermarket::on_actiond_triggered()
{
    if(CheckAccount(0))
    {
        QString dir = QUIWidget::getFolderName();
        QFile::remove(dir+"//操作记录.csv");
        bool is_copy = QUIWidget::copyFile("user//Log.csv",dir+"//操作记录.csv");
        if(is_copy == true)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile(dir));
        }
        else
        {
            QUIWidget::showMessageBoxError("导出错误,请检查系统.");
        }
    }
}

void Supermarket::on_action_H_triggered()
{
    QProcess::execute("explorer help.txt");
}

void Supermarket::on_action_A_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("http://60.205.215.163/")));
    //QUrl url(QString("http://60.205.215.163/"));
    //QDesktopServices::openUrl(url);
    // QDesktopServices::openUrl("http://60.205.215.163/");
    QUIWidget::showMessageBoxInfo("此程序核心为链式表，QT开发；界面基于QSS，实现换肤、右键等；加密系统基于DES加密方式，由独立进程实现。",20);
}

void Supermarket::on_action_B_triggered()
{
    QDesktopServices::openUrl(QUrl(QString("https://wj.qq.com/s/1773296/9f9c/")));
    //QUrl url(QString("https://wj.qq.com/s/1773296/9f9c/"));
    //QDesktopServices::openUrl(url);
}

void Supermarket::on_pushButton_3_clicked()
{
    if(CheckAccount(1))
        ManInput();
}

void Supermarket::on_pushButton_2_clicked()
{
    if(CheckAccount(1))
        OutStorage();
}

void Supermarket::on_pushButton_6_clicked()
{
    if(CheckAccount(1))
        Search();
}

void Supermarket::on_pushButton_7_clicked()
{
    if(CheckAccount(1))
        SetDate();
}

//置空操作
void Supermarket::on_pushButton_8_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->doubleSpinBox->setValue(0.00);
    ui->doubleSpinBox_2->setValue(0.00);
    ui->doubleSpinBox_11->setValue(0.00);
    ui->comboBox->setCurrentText("请选择单位");
    ui->comboBox_2->setCurrentText("请选择分类");

}

void Supermarket::on_pushButton_9_clicked()
{
    ui->lineEdit_8->setText("");
    ui->lineEdit_7->setText("");
    ui->doubleSpinBox_7->setValue(0.00);
    ui->doubleSpinBox_8->setValue(0.00);
    ui->doubleSpinBox_13->setValue(0.00);
    ui->comboBox_10->setCurrentText("可选单位");
    ui->comboBox_9->setCurrentText("可选分类");
}

void Supermarket::on_pushButton_10_clicked()
{
    ui->lineEdit_10->setText("");
    ui->lineEdit_9->setText("");
    ui->doubleSpinBox_9->setValue(0.00);
    ui->doubleSpinBox_10->setValue(0.00);
    ui->doubleSpinBox_14->setValue(0.00);
    ui->comboBox_12->setCurrentText("可改单位");
    ui->comboBox_11->setCurrentText("可改分类");
}

void Supermarket::on_pushButton_4_clicked()
{
    loginin_account = "";
    initUnAccount();

}
Good* Supermarket::GetLastPointer()
{
    Good* p;
    if(head == NULL) return head;
    else
    {
        for(p=head; p->next!=NULL; p=p->next);
        return p;
    }
}

bool Supermarket::CheckID(string pid)
{
    Good*p=head;
    if(p==NULL)
    {
        return true;
    }
    else
    {
        while(p!=NULL)
        {
            if(pid == p->id)
                return false;
            else{p=p->next;}
        }
        return true;
    }
}

bool Supermarket::ManInput()
{
    Good *p,*q;
    p = (Good*)new(Good);

    if(ui->lineEdit->text().toStdString() == "")
        QUIWidget::showMessageBoxError("ID不能为空.",5);
    else
        p->id = ui->lineEdit->text().toStdString();

    if(CheckID(ui->lineEdit->text().toStdString()))
    {
        if(ui->lineEdit_2->text().toStdString() == "")
            QUIWidget::showMessageBoxError("商品名称不能为空.",5);
        else
            p->name = ui->lineEdit_2->text().toStdString();

        if(ui->doubleSpinBox->value()==0)
            QUIWidget::showMessageBoxError("进价不能为0.",5);
        else
            p->cost = ui->doubleSpinBox->value();

        if(ui->doubleSpinBox_2->value()==0)
            QUIWidget::showMessageBoxError("售价不能为0.",5);
        else
            p->price = ui->doubleSpinBox_2->value();

        if(ui->doubleSpinBox_11->value()==0)
            QUIWidget::showMessageBoxError("数量不能为0.",5);
        else
            p->number = ui->doubleSpinBox_11->value();

        if(ui->comboBox->currentText().toStdString() == "请选择单位")
            QUIWidget::showMessageBoxError("请选择计量单位.",5);
        else
            p->measure_unit = ui->comboBox->currentText().toStdString();

        if(ui->comboBox_2->currentText().toStdString() == "请选择分类")
            QUIWidget::showMessageBoxError("请选择分类以便更好的处理.",5);
        else
            p->category = ui->comboBox_2->currentText().toStdString();

        if((ui->lineEdit->text().toStdString() != "")&&(ui->lineEdit_2->text().toStdString() != "")&&(ui->doubleSpinBox->value()!=0)&&(ui->doubleSpinBox_2->value()!=0)&&(ui->doubleSpinBox_11->value()!=0)&&(ui->comboBox->currentText().toStdString() != "请选择单位")&&(ui->comboBox_2->currentText().toStdString() != "请选择分类"))
        {
            p->purchase_time =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ddd").toStdString();
            p->next = NULL;
            p->sell_time = "暂无记录";
            number++;
            if(head == NULL)
                head = p;
            else
            {
                q = GetLastPointer();
                q->next = p;
            }
            Log("入库",true,p);
        }
    }
    else
    {
        bool ok_change = 1;
        q = SearchChild(ui->lineEdit->text().toStdString());

        if((ui->lineEdit_2->text().toStdString() != "") && (ui->lineEdit_2->text().toStdString() != q->name))
        {QUIWidget::showMessageBoxError("与已存在的商品名称不一致，如需修改请移步“修改”页.",5);ok_change = 0;}
        if(ui->doubleSpinBox->value()==0)
        {QUIWidget::showMessageBoxError("进价不能为0.",5);ok_change=0;}
        if(ui->doubleSpinBox_2->value()==0)
        {  QUIWidget::showMessageBoxError("售价不能为0.",5);ok_change=0;}
        if(ui->doubleSpinBox_11->value()==0)
        {QUIWidget::showMessageBoxError("数量不能为0.",5); ok_change = 0;}
        if(ui->comboBox->currentText().toStdString() != "请选择单位" && ui->comboBox->currentText().toStdString() != q->measure_unit)
        {  QUIWidget::showMessageBoxError("与已存在的商品单位不一致，如需修改请移步“修改”页.",5); ok_change = 0;}
        if(ui->comboBox_2->currentText().toStdString() != "请选择分类" && ui->comboBox_2->currentText().toStdString()!=q->category)
        { QUIWidget::showMessageBoxError("与已存在的商品分类不一致，如需修改请移步“修改”页.",5); ok_change = 0;}


        if(ok_change == 1)
        {
            if((ui->doubleSpinBox->value() != q->cost)||(ui->doubleSpinBox_2->value() != q->price))
            {
                int is_change = QUIWidget::showMessageBoxQuestion("这批产品的进价/售价与已存在的这件商品的平均进价/售价不一样吗？");
                if(is_change == 16384)
                {
                    q->cost = (q->cost*q->number + ui->doubleSpinBox->value()*ui->doubleSpinBox_11->value())/(q->number + ui->doubleSpinBox_11->value());
                    q->price = (q->price*q->number + ui->doubleSpinBox_2->value()*ui->doubleSpinBox_11->value())/(q->number + ui->doubleSpinBox_11->value());
                    q->number = q->number + ui->doubleSpinBox_11->value();
                }
            }
            else
            {
                q->number = q->number + ui->doubleSpinBox_11->value();
            }
            Log("入库",true,q);
        }
    }
    return true;
}


bool Supermarket::BatchInput()
{
    string file_name = QUIWidget::getFileName("user","*.csv;;*.qzq").toStdString();
    QString qfile_name = QString::fromStdString(file_name);
    QFileInfo fileinfo;
    fileinfo = QFileInfo(qfile_name);
    if(fileinfo.suffix() == "qzq")
    {
        QFile::remove("cache\\CacheData.qzq");
        QUIWidget::copyFile(qfile_name,"cache\\CacheData.qzq");
        QProcess process;
        process.start("Des3.exe -u cache\\CacheData.qzq qwertyuiop cache\\CacheData.csv");
        process.terminate();
        process.waitForFinished();
        process.close();
        file_name = "cache\\CacheData.csv";
    }
    ifstream read_file(file_name,ios::in);
    int counts = 0;
    string line_str,str;
    bool all_read = 1;
    while(getline(read_file,line_str))
    {
        counts++;
        Good *p,*q;
        p = (Good*)new(Good);
        stringstream ss(line_str);
        getline(ss,str,',');
        p->name = str;
        getline(ss,str,',');
        p->id = str;
        getline(ss,str,',');
        p->cost = stod(str);
        getline(ss,str,',');
        p->price = stod(str);
        getline(ss,str,',');
        p->number = stod(str);
        getline(ss,str,',');
        p->measure_unit = str;
        getline(ss,str,',');
        p->category = str;
        getline(ss,str,',');
        p->purchase_time =str;
        getline(ss,str,',');
        p->sell_time = str;
        p->next = NULL;
        if(SearchChild(p->id) == NULL)
        {
            number++;
            if(head == NULL)
                head = p;
            else
            {
                q = GetLastPointer();
                q->next = p;
            }
        }
        else all_read = 0;
    }
    if(all_read == 0)QUIWidget::showMessageBoxInfo("部分数据的ID与现有数据重复，未导入此部分数据项。");
    read_file.close();
    QFile::remove("cache\\CacheData.csv");
    QFile::remove("cache\\CacheData.qzq");
    Log("批量导入",true,NULL);
    return true;
}


bool Supermarket::BatchOutput(string dir)
{
    QString sdir = QString::fromStdString(dir);
    dir = dir +"\\Data.csv";
    ofstream wfile(dir);
    Good* p = head;
    if(head == NULL)
    {
        QUIWidget::showMessageBoxError("无数据可导出.");
        return false;
    }
    else{
        while(p!= NULL)
        {
            wfile<<p->name<<","<<p->id<<","<<p->cost<<","<<p->price<<","<<p->number<<","<<p->measure_unit<<","<<p->category<<","<<p->purchase_time<<","<<p->sell_time<<endl;
            p = p->next;
        }
        wfile.close();
        Log("批量导出",true,NULL);
    }
    return true;
}


bool Supermarket::OutStorage()
{
    Good* p;
    string pid = ui->lineEdit_11->text().toStdString();
    double num = ui->doubleSpinBox_12->value();
    p = SearchChild(pid);
    if(p == NULL)
    {
        QUIWidget::showMessageBoxError("未找到您输入的ID，请重新输入或搜索一下。");
    }
    else if(p->number < num || num<=0)
    {
        QUIWidget::showMessageBoxError("您输入的数量不正确，请检查。");
    }
    else if(p->number == num)
    {
        p->number = p->number-num;
        number --;
        Good*phead = head;
        {
            for(;phead->next != p;phead=phead->next);
            phead->next = p->next;
        }
        //p->sell_time =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ddd").toStdString();
        Log("出库",true,p);
    }
    else
    {
        p->number = p->number-num;
        p->sell_time =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ddd").toStdString();
        Log("出库",true,p);
    }
    return true;
}


Good* Supermarket::SearchChild(string pid)
{
    Good* p = head, *q = NULL;
    if(p == NULL)
    {
        return NULL;
    }
    else
    {
        while(p!=NULL)
        {
            if(p->id == pid)
            {
                q = p;
                break;
            }
            else p = p->next;
        }
        return q;
    }
}


void Supermarket:: Search()
{
    string sid, sname, smeasure_unit, scategory;
    double scost=0, sprice = 0,snumber = 0;
    sid = ui->lineEdit_8->text().toStdString();
    sname = ui->lineEdit_7->text().toStdString();
    scost = ui->doubleSpinBox_7->value();
    sprice = ui->doubleSpinBox_8->value();
    snumber = ui->doubleSpinBox_13->value();
    smeasure_unit = ui->comboBox_10->currentText().toStdString();
    scategory = ui->comboBox_9->currentText().toStdString();

    Good* p = head;
    int counts = 0;

    QStandardItemModel *model = new QStandardItemModel();
    ui->tableView->setModel(model);
    model->setColumnCount(9);
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("ID")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("名称")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("进价")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("售价")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("数量")));
    model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("单位")));
    model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("类别")));
    model->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("入库时间")));
    model->setHorizontalHeaderItem(8,new QStandardItem(QObject::tr("出库时间")));
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//表头通过内容列宽自适应
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表头根据窗口自适应

    if(p==NULL)
    {
        QUIWidget::showMessageBoxError("没有找到任何匹配项。");
    }
    else
    {
        for(;p!=NULL;p=p->next)
        {
            if((sid==p->id||sid=="")&&(sname==p->name||sname=="")&&(smeasure_unit==p->measure_unit||smeasure_unit=="可选单位")&&(scategory==p->category||scategory=="可选分类")&&(scost==p->cost||scost==0)&&(sprice==p->price||sprice==0)&&(snumber==p->number||snumber==0))
            {
                model->setItem(counts,0,new QStandardItem(QString::fromStdString(p->id)));
                model->setItem(counts,1,new QStandardItem(QString::fromStdString(p->name)));
                model->setItem(counts,2,new QStandardItem(QString::number(p->cost,10,2)));
                model->setItem(counts,3,new QStandardItem(QString::number(p->price,10,2)));
                model->setItem(counts,4,new QStandardItem(QString::number(p->number,10,2)));
                model->setItem(counts,5,new QStandardItem(QString::fromStdString(p->measure_unit)));
                model->setItem(counts,6,new QStandardItem(QString::fromStdString(p->category)));
                model->setItem(counts,7,new QStandardItem(QString::fromStdString(p->purchase_time)));
                model->setItem(counts,8,new QStandardItem(QString::fromStdString(p->sell_time)));
                counts++;
            }
            ui->statusbar->showMessage("正在搜索...",500);
        }
    }
    ui->statusbar->clearMessage();
    ui->statusbar->showMessage("搜索完毕.",3000);
}


bool Supermarket::SetDate()
{
    string sid, sname, smeasure_unit, scategory;
    double scost=0, sprice = 0,snumber = 0;
    sid = ui->lineEdit_10->text().toStdString();
    sname = ui->lineEdit_9->text().toStdString();
    scost = ui->doubleSpinBox_9->value();
    sprice = ui->doubleSpinBox_10->value();
    snumber = ui->doubleSpinBox_14->value();
    smeasure_unit = ui->comboBox_12->currentText().toStdString();
    scategory = ui->comboBox_11->currentText().toStdString();

    if(sid == "")
        QUIWidget::showMessageBoxInfo("ID是必须要输入的项",5);
    else
    {
        Good *p = SearchChild(sid);
        if(p == NULL)
        {
            QUIWidget::showMessageBoxError("未找到您输入的ID，请重新输入或查询一下。");
            return false;
        }
        else
        {
            if(sid != "")p->id = sid;
            if(sname != "")p->name = sname;
            if(scost != 0)p->cost = scost;
            if(sprice != 0)p->price = sprice;
            if(snumber != 0)p->number = snumber;
            if(smeasure_unit != "可改单位")p->measure_unit = smeasure_unit;
            if(scategory != "可改分类")p->category = scategory;
            Log("修改",true,p);
            return true;
        }
    }
    return false;
}


long Supermarket::GetNumber()
{
    return number;
}

//统计
void Supermarket::Statistics()
{
    ui->label_17->setText("商品种数：");
    ui->label_15->setText("员工总数：");
    ui->label_13->setText("总支出：");
    ui->label_11->setText("总价值：");
    ui->label_18->setText(QString::number(number));
    string file_name = "user//account.csv",line_str;
    int account_num = 0;
    ifstream read_account(file_name,ios::in);
    while(getline(read_account,line_str))
    {account_num++;}
    ui->label_16->setText(QString::number(account_num));
    double out = 0, in = 0;
    Good *p = head;
    if(p == NULL)
    {
        ui->label_14->setText("0");
        ui->label_12->setText("0");
    }
    else
    {
        while(p!=NULL)
        {
            out = out + p->cost * p->number;
            in = in +p->price * p->number;
            p=p->next;
        }
        ui->label_14->setText(QString::number(out,10,6));
        ui->label_12->setText(QString::number(in,10,6));
        out = 0;
        in = 0;
    }

}

//写日志
void Supermarket::Log(string operators, bool end_out, Good *p)
{
    static long long order = 1000000000000000000;
    //序号 + 人 + 时间 + 操作 + 结果
    int rc = pmodel->rowCount();
    int cc = pmodel->columnCount();
    string sstr;
    char strc[25];
    itoa(cc,strc,10);
    sstr = strc;
    //QUIWidget::showMessageBoxInfo(QString::fromStdString(sstr),3000);
    if(cc != 5)
    {
        delete pmodel;
        QStandardItemModel *model = new QStandardItemModel();
        model->setColumnCount(5);
        model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("操作结果")));
        model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("操作序号")));
        model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("执行账户")));
        model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("操作时间")));
        model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("操作内容")));
        pmodel = model;
        rc = 0;
    }
    ui->tableView->setModel(pmodel);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//表头根据窗口自适应
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//表头通过内容列宽自适应
    ui->tableView->horizontalHeader()->setStretchLastSection(true);//不留空，但最后一列会很宽
    //ui->tableView->setColumnWidth(0,100);
    //ui->tableView->setColumnWidth(1,300);

    //写入文件，最近操作在文件后方
    string dir = "user\\Log.csv";
    ofstream wfile(dir,ios::app);
    order = order + 1;
    string this_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ddd").toStdString();
    wfile<<end_out<<","<<order<<","<<loginin_account<<","<<this_time<<","<<operators<<endl;
    wfile.close();
    if(order >= 9000000000000000000)
        order = 1000000000000000000;

    //显示到TableView
    string snumber,send_out;
    char str[22];
    if(p!=NULL)
    {
        sprintf(str,"%.2f",p->number);
        snumber = str;
    }
    if(end_out == true)send_out = "成功";
    else send_out = "失败";
    pmodel->setItem(rc,0,new QStandardItem(QString::fromStdString(send_out)));
    pmodel->setItem(rc,1,new QStandardItem(QString::number(order)));
    pmodel->setItem(rc,2,new QStandardItem(QString::fromStdString(loginin_account)));
    pmodel->setItem(rc,3,new QStandardItem(QString::fromStdString(this_time)));
    if(operators == "出库")
    {
        pmodel->setItem(rc,4,new QStandardItem(QString::fromStdString("已"+operators+"ID为"+p->id+"的商品,仓库剩余"+snumber+p->measure_unit)));
    }
    else if(operators == "入库")
    {
        pmodel->setItem(rc,4,new QStandardItem(QString::fromStdString("已"+operators+"ID为"+p->id+"的商品,仓库剩余"+snumber+p->measure_unit)));
    }
    else if(p!=NULL)
    {
        pmodel->setItem(rc,4,new QStandardItem(QString::fromStdString(operators+"ID为"+p->id+"的商品"+snumber+p->measure_unit)));
    }
    else
    {
        pmodel->setItem(rc,4,new QStandardItem(QString::fromStdString(operators)));
    }
    pmodel->sort(1, Qt::DescendingOrder);
}










/*
bool Supermarket::Upload()
{
    QString path="http://192.168.252.2:8000/disk/"; //服务器的url
    QMap<QString,QString> params_send; //上传的普通参数 在本程序中 需要上传一个普通参数为"username"
    params_send.insert("username","10005");
    QString fileFormName="upload_file"; //上传文件表单中的名字

    QFile *file=new QFile(":/Untitled.png");

    QString newFileName="1A.png";
    UpLoadForm(path,params_send,fileFormName,file,newFileName);
    return true;
}

//上传备份

void UpLoadForm(QString Path,QMap<QString,QString> params,QString fileFormName,QFile *uploadFile,QString newFileName){
    QString BOUNDARY=QUuid::createUuid().toString();
    QByteArray sb=QByteArray();

    //先上传普通的表单数据
    for(QMap<QString,QString>::Iterator t=params.begin();t!=params.end();t++){
        sb.append("--"+BOUNDARY+"\r\n");
        sb.append(QString("Content-Disposition: form-data; name=\"")+t.key()+QString("\"")+QString("\r\n"));
        sb.append("\r\n");
        sb.append(t.value()+"\r\n");
    }
    //上传文件的头部
    sb.append("--"+BOUNDARY+"\r\n");
    sb.append(QString("Content-Disposition: form-data; name=\"")+fileFormName+QString("\"; filename=\"")+newFileName+QString("\"")+QString("\r\n"));
    sb.append("\r\n");
    //上传文件内容
    if(!uploadFile->open(QIODevice::ReadOnly)){
        return;
    }
    sb.append(uploadFile->readAll());
    sb.append("\r\n");
    sb.append("--"+BOUNDARY+"\r\n");
    //编辑HTTP头部
    QNetworkAccessManager *_uploadManager=new QNetworkAccessManager();
    QNetworkRequest request=QNetworkRequest(QUrl(Path));
    request.setRawHeader(QString("Content-Type").toLatin1(),QString("multipart/form-data; boundary="+BOUNDARY).toLatin1());
    request.setRawHeader(QString("Content-Length").toLatin1(),QString::number(sb.length()).toLatin1());
    //执行post请求
    _uploadManager->post(request,sb);
}

*/



