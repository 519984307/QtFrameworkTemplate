/********************************************************************************
** Form generated from reading UI file 'PngArrayPlayWid.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PNGARRAYPLAYWID_H
#define UI_PNGARRAYPLAYWID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "PngArrayPlayWid.h"

QT_BEGIN_NAMESPACE

class Ui_PngArrayPlayWid
{
public:
    QGridLayout *gridLayout;
    PngArrayLabel *lab_png_play;

    void setupUi(QWidget *PngArrayPlayWid)
    {
        if (PngArrayPlayWid->objectName().isEmpty())
            PngArrayPlayWid->setObjectName(QString::fromUtf8("PngArrayPlayWid"));
        PngArrayPlayWid->resize(300, 300);
        PngArrayPlayWid->setMinimumSize(QSize(10, 10));
        PngArrayPlayWid->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(PngArrayPlayWid);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lab_png_play = new PngArrayLabel(PngArrayPlayWid);
        lab_png_play->setObjectName(QString::fromUtf8("lab_png_play"));

        gridLayout->addWidget(lab_png_play, 0, 0, 1, 1);


        retranslateUi(PngArrayPlayWid);

        QMetaObject::connectSlotsByName(PngArrayPlayWid);
    } // setupUi

    void retranslateUi(QWidget *PngArrayPlayWid)
    {
        PngArrayPlayWid->setWindowTitle(QCoreApplication::translate("PngArrayPlayWid", "PngArrayPlayWid", nullptr));
        lab_png_play->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PngArrayPlayWid: public Ui_PngArrayPlayWid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PNGARRAYPLAYWID_H
