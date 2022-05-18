#ifndef WINDOWSIZETOOLBAR_H
#define WINDOWSIZETOOLBAR_H

#include <QWidget>
#include "toolbutton.h"
#include "utilsexport.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

class UTILS_EXPORT WindowSizeToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit WindowSizeToolBar(QWidget *parent = 0);
    enum {
        ButtonsPos_Top,
        ButtonsPos_Mid,
        ButtonsPos_Bottom
    };
    void initializeButtons(bool bContainCloseButton = true, bool bContainMinimizeButton = true, bool bContainMaximumButton = false);

    QHBoxLayout* buttonsLayout() {return m_buttonsLayout;}
    ToolButton* closeButton() {return m_closeButton;}
    ToolButton* minimizeButton() {return m_minimizeButton;}
    ToolButton* maximumButton() {return m_MaximumButton;}

signals:
    void closeButtonClicked();
    void minimizeButtonClicked();
    void maximumButtonClicked();

public slots:


private:
    ToolButton* m_closeButton;
    ToolButton* m_minimizeButton;
    ToolButton* m_MaximumButton;
    QHBoxLayout* m_buttonsLayout;
    QVBoxLayout* m_mainLayout;
    //QVBoxLayout* m_mainLayout;
};

#endif // WINDOWSIZETOOLBAR_H
