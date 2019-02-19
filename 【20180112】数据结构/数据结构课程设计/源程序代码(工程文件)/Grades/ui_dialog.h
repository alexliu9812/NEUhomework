/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_9;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1134, 701);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(10);
        font.setStyleStrategy(QFont::PreferAntialias);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        label_8 = new QLabel(Dialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 5, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);


        gridLayout_2->addLayout(verticalLayout_2, 4, 1, 1, 1);

        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_4, 3, 1, 1, 1);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_3, 2, 1, 1, 1);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_2, 1, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_9 = new QLabel(Dialog);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_3->addWidget(label_9);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 5);
        gridLayout_2->setRowStretch(1, 1);
        gridLayout_2->setRowStretch(2, 1);
        gridLayout_2->setRowStretch(3, 1);
        gridLayout_2->setRowStretch(4, 4);
        gridLayout_2->setRowStretch(5, 1);

        gridLayout->addLayout(gridLayout_2, 1, 3, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        gridLayout->addLayout(verticalLayout, 1, 0, 1, 3);

        gridLayout->setColumnStretch(0, 8);
        gridLayout->setColumnStretch(1, 1);

        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        label_7->setText(QApplication::translate("Dialog", "\345\271\263\345\235\207\345\200\274\357\274\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("Dialog", "\346\240\267\346\234\254\345\256\271\351\207\217\357\274\232", Q_NULLPTR));
        label_5->setText(QString());
        label->setText(QString());
        label_6->setText(QApplication::translate("Dialog", "\346\200\273\346\240\207\345\207\206\345\267\256\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("Dialog", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("Dialog", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog", "TextLabel", Q_NULLPTR));
        label_9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
