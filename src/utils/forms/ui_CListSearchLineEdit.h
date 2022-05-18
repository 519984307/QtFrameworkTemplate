/********************************************************************************
** Form generated from reading UI file 'CListSearchLineEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLISTSEARCHLINEEDIT_H
#define UI_CLISTSEARCHLINEEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CListSearchLineEdit
{
public:
    QGridLayout *gridLayout;
    QWidget *wid_main;
    QHBoxLayout *horizontalLayout;
    QLabel *lab_icon;
    QLineEdit *lineEdit;

    void setupUi(QWidget *CListSearchLineEdit)
    {
        if (CListSearchLineEdit->objectName().isEmpty())
            CListSearchLineEdit->setObjectName(QString::fromUtf8("CListSearchLineEdit"));
        CListSearchLineEdit->resize(261, 25);
        gridLayout = new QGridLayout(CListSearchLineEdit);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        wid_main = new QWidget(CListSearchLineEdit);
        wid_main->setObjectName(QString::fromUtf8("wid_main"));
        horizontalLayout = new QHBoxLayout(wid_main);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 0, 0);
        lab_icon = new QLabel(wid_main);
        lab_icon->setObjectName(QString::fromUtf8("lab_icon"));
        lab_icon->setMinimumSize(QSize(12, 12));
        lab_icon->setMaximumSize(QSize(12, 12));

        horizontalLayout->addWidget(lab_icon);

        lineEdit = new QLineEdit(wid_main);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 14));
        lineEdit->setMaximumSize(QSize(16777215, 14));

        horizontalLayout->addWidget(lineEdit);


        gridLayout->addWidget(wid_main, 0, 0, 1, 1);


        retranslateUi(CListSearchLineEdit);

        QMetaObject::connectSlotsByName(CListSearchLineEdit);
    } // setupUi

    void retranslateUi(QWidget *CListSearchLineEdit)
    {
        CListSearchLineEdit->setWindowTitle(QCoreApplication::translate("CListSearchLineEdit", "CListSearchLineEdit", nullptr));
        lab_icon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CListSearchLineEdit: public Ui_CListSearchLineEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLISTSEARCHLINEEDIT_H
