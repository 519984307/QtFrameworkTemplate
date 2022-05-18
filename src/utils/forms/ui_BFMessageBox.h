/********************************************************************************
** Form generated from reading UI file 'BFMessageBox.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BFMESSAGEBOX_H
#define UI_BFMESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BFMessageBox
{
public:
    QGridLayout *gridLayout;
    QWidget *main_wid;
    QPushButton *cancel_btn;
    QPushButton *confirm_btn;
    QPushButton *ok_btn;
    QLabel *tips_lab;
    QLabel *lab_context;
    QPushButton *btn_close;

    void setupUi(QDialog *BFMessageBox)
    {
        if (BFMessageBox->objectName().isEmpty())
            BFMessageBox->setObjectName(QString::fromUtf8("BFMessageBox"));
        BFMessageBox->resize(420, 220);
        BFMessageBox->setMinimumSize(QSize(420, 220));
        BFMessageBox->setMaximumSize(QSize(420, 220));
        gridLayout = new QGridLayout(BFMessageBox);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        main_wid = new QWidget(BFMessageBox);
        main_wid->setObjectName(QString::fromUtf8("main_wid"));
        main_wid->setStyleSheet(QString::fromUtf8("#main_wid\n"
"{\n"
"background-color:#ff1c1d31;\n"
"border-radius:10px;\n"
"border:1px solid;\n"
"border-color:#ff303642;\n"
"}\n"
"\n"
""));
        cancel_btn = new QPushButton(main_wid);
        cancel_btn->setObjectName(QString::fromUtf8("cancel_btn"));
        cancel_btn->setGeometry(QRect(190, 180, 75, 23));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cancel_btn->sizePolicy().hasHeightForWidth());
        cancel_btn->setSizePolicy(sizePolicy);
        cancel_btn->setMinimumSize(QSize(75, 23));
        cancel_btn->setMaximumSize(QSize(75, 23));
        cancel_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(225, 225, 225);"));
        confirm_btn = new QPushButton(main_wid);
        confirm_btn->setObjectName(QString::fromUtf8("confirm_btn"));
        confirm_btn->setGeometry(QRect(60, 180, 75, 23));
        sizePolicy.setHeightForWidth(confirm_btn->sizePolicy().hasHeightForWidth());
        confirm_btn->setSizePolicy(sizePolicy);
        confirm_btn->setMinimumSize(QSize(75, 23));
        confirm_btn->setMaximumSize(QSize(75, 23));
        confirm_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(225, 225, 225);\n"
""));
        ok_btn = new QPushButton(main_wid);
        ok_btn->setObjectName(QString::fromUtf8("ok_btn"));
        ok_btn->setGeometry(QRect(320, 180, 75, 23));
        sizePolicy.setHeightForWidth(ok_btn->sizePolicy().hasHeightForWidth());
        ok_btn->setSizePolicy(sizePolicy);
        ok_btn->setMinimumSize(QSize(75, 23));
        ok_btn->setMaximumSize(QSize(75, 23));
        ok_btn->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(225, 225, 225);"));
        tips_lab = new QLabel(main_wid);
        tips_lab->setObjectName(QString::fromUtf8("tips_lab"));
        tips_lab->setGeometry(QRect(50, 10, 187, 26));
        sizePolicy.setHeightForWidth(tips_lab->sizePolicy().hasHeightForWidth());
        tips_lab->setSizePolicy(sizePolicy);
        tips_lab->setMinimumSize(QSize(1, 1));
        tips_lab->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);"));
        lab_context = new QLabel(main_wid);
        lab_context->setObjectName(QString::fromUtf8("lab_context"));
        lab_context->setGeometry(QRect(50, 50, 321, 111));
        lab_context->setWordWrap(true);
        btn_close = new QPushButton(main_wid);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(390, 20, 15, 15));
        btn_close->setMinimumSize(QSize(15, 15));
        btn_close->setMaximumSize(QSize(15, 15));
        btn_close->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(main_wid, 0, 0, 1, 1);


        retranslateUi(BFMessageBox);

        QMetaObject::connectSlotsByName(BFMessageBox);
    } // setupUi

    void retranslateUi(QDialog *BFMessageBox)
    {
        BFMessageBox->setWindowTitle(QCoreApplication::translate("BFMessageBox", "BFMessageBox", nullptr));
        cancel_btn->setText(QCoreApplication::translate("BFMessageBox", "\345\220\246", nullptr));
        confirm_btn->setText(QCoreApplication::translate("BFMessageBox", "\346\230\257", nullptr));
        ok_btn->setText(QCoreApplication::translate("BFMessageBox", "\347\241\256\345\256\232", nullptr));
        tips_lab->setText(QCoreApplication::translate("BFMessageBox", "\346\217\220\347\244\272", nullptr));
        lab_context->setText(QCoreApplication::translate("BFMessageBox", "TextLabel", nullptr));
        btn_close->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class BFMessageBox: public Ui_BFMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BFMESSAGEBOX_H
