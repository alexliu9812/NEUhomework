/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiond;
    QAction *actiond_2;
    QAction *actionc;
    QAction *actionb;
    QAction *actiona;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_h;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(551, 336);
        actiond = new QAction(MainWindow);
        actiond->setObjectName(QStringLiteral("actiond"));
        actiond_2 = new QAction(MainWindow);
        actiond_2->setObjectName(QStringLiteral("actiond_2"));
        actionc = new QAction(MainWindow);
        actionc->setObjectName(QStringLiteral("actionc"));
        actionb = new QAction(MainWindow);
        actionb->setObjectName(QStringLiteral("actionb"));
        actiona = new QAction(MainWindow);
        actiona->setObjectName(QStringLiteral("actiona"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 0, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(10);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font);

        gridLayout_2->addWidget(pushButton, 0, 2, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 2);
        gridLayout_2->setColumnStretch(2, 1);

        verticalLayout->addLayout(gridLayout_2);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);

        gridLayout->setColumnStretch(0, 1);

        verticalLayout->addLayout(gridLayout);

        verticalLayout->setStretch(2, 3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 551, 22));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_h = new QMenu(menuBar);
        menu_h->setObjectName(QStringLiteral("menu_h"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_h->menuAction());
        menu_F->addAction(actiond);
        menu_F->addAction(actiond_2);
        menu_h->addAction(actionc);
        menu_h->addAction(actionb);
        menu_h->addSeparator();
        menu_h->addAction(actiona);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actiond->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\346\225\260\346\215\256(&I)...", Q_NULLPTR));
        actiond->setShortcut(QApplication::translate("MainWindow", "Ctrl+I", Q_NULLPTR));
        actiond_2->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\346\225\260\346\215\256(&O)...", Q_NULLPTR));
        actiond_2->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
        actionc->setText(QApplication::translate("MainWindow", "\346\237\245\347\234\213\345\270\256\345\212\251(&C)...", Q_NULLPTR));
        actionb->setText(QApplication::translate("MainWindow", "\345\217\215\351\246\210(&B)...", Q_NULLPTR));
        actiona->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)...", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\350\276\223\345\205\245\347\247\221\347\233\256\345\272\217\345\217\267\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Go", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Logs:", Q_NULLPTR));
        menu_F->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", Q_NULLPTR));
        menu_h->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
