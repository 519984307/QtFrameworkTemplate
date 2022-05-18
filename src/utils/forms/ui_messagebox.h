/********************************************************************************
** Form generated from reading UI file 'messagebox.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEBOX_H
#define UI_MESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <windowsizetoolbar.h>

QT_BEGIN_NAMESPACE

class Ui_MessageBox
{
public:
    QVBoxLayout *verticalLayoutMain;
    QWidget *widgetTitleBar;
    QHBoxLayout *horizontalLayout;
    QLabel *labelTitle;
    QSpacerItem *horizontalSpacer;
    WindowSizeToolBar *widgetSizeToolBar;
    QWidget *widgetCenter;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelIcon;
    QLabel *labelTip;
    QSpacerItem *verticalSpacer_4;
    QWidget *widgetBottomBar;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MessageBox)
    {
        if (MessageBox->objectName().isEmpty())
            MessageBox->setObjectName(QString::fromUtf8("MessageBox"));
        MessageBox->resize(356, 243);
        MessageBox->setMinimumSize(QSize(356, 0));
        MessageBox->setMaximumSize(QSize(356, 16777215));
        verticalLayoutMain = new QVBoxLayout(MessageBox);
        verticalLayoutMain->setObjectName(QString::fromUtf8("verticalLayoutMain"));
        verticalLayoutMain->setContentsMargins(8, 8, 8, 8);
        widgetTitleBar = new QWidget(MessageBox);
        widgetTitleBar->setObjectName(QString::fromUtf8("widgetTitleBar"));
        widgetTitleBar->setMinimumSize(QSize(0, 38));
        widgetTitleBar->setMaximumSize(QSize(16777215, 38));
        horizontalLayout = new QHBoxLayout(widgetTitleBar);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 0, 0);
        labelTitle = new QLabel(widgetTitleBar);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));

        horizontalLayout->addWidget(labelTitle);

        horizontalSpacer = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widgetSizeToolBar = new WindowSizeToolBar(widgetTitleBar);
        widgetSizeToolBar->setObjectName(QString::fromUtf8("widgetSizeToolBar"));

        horizontalLayout->addWidget(widgetSizeToolBar);


        verticalLayoutMain->addWidget(widgetTitleBar);

        widgetCenter = new QWidget(MessageBox);
        widgetCenter->setObjectName(QString::fromUtf8("widgetCenter"));
        verticalLayout_2 = new QVBoxLayout(widgetCenter);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, -1, 10, -1);
        verticalSpacer_3 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, -1, -1, -1);
        labelIcon = new QLabel(widgetCenter);
        labelIcon->setObjectName(QString::fromUtf8("labelIcon"));
        labelIcon->setMinimumSize(QSize(48, 48));
        labelIcon->setMaximumSize(QSize(48, 48));
        labelIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/success.png")));
        labelIcon->setScaledContents(true);

        horizontalLayout_3->addWidget(labelIcon);

        labelTip = new QLabel(widgetCenter);
        labelTip->setObjectName(QString::fromUtf8("labelTip"));
        labelTip->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        labelTip->setWordWrap(true);

        horizontalLayout_3->addWidget(labelTip);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(2, 1);

        verticalLayoutMain->addWidget(widgetCenter);

        widgetBottomBar = new QWidget(MessageBox);
        widgetBottomBar->setObjectName(QString::fromUtf8("widgetBottomBar"));
        widgetBottomBar->setMinimumSize(QSize(0, 50));
        widgetBottomBar->setMaximumSize(QSize(16777215, 50));
        verticalLayout = new QVBoxLayout(widgetBottomBar);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 18, 18);
        verticalSpacer = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(156, 19, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(widgetBottomBar);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayoutMain->addWidget(widgetBottomBar);


        retranslateUi(MessageBox);

        QMetaObject::connectSlotsByName(MessageBox);
    } // setupUi

    void retranslateUi(QDialog *MessageBox)
    {
        MessageBox->setWindowTitle(QCoreApplication::translate("MessageBox", "Dialog", nullptr));
        labelTitle->setText(QCoreApplication::translate("MessageBox", "Warm tip", nullptr));
        labelIcon->setText(QString());
        labelTip->setText(QCoreApplication::translate("MessageBox", "Tip", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessageBox: public Ui_MessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEBOX_H
