#ifndef NC_FRAMELESS_HELPER_H
#define NC_FRAMELESS_HELPER_H

#include <QObject>
#include "utilsexport.h"

class NcFramelessHelperImpl;

class UTILS_EXPORT NcFramelessHelper : public QObject
{

public:
    explicit NcFramelessHelper( QObject* parent = 0 );
    ~NcFramelessHelper();

    void activateOn( QWidget* topLevelWidget );
    void removeFrom( QWidget* topLevelWidget );

    void setWidgetMovable(QWidget* widget, bool movable );
    bool isWidgetMovable(QWidget* widget);

    void setWidgetResizable(QWidget* widget, bool resizable );
    bool isWidgetResizable(QWidget *widget);

    //Make sure to leave the same content margins
    //around the widget as the newBorderWidth
    //this can be done by
    //yourWidget->layout()->setMargin( newBorderWidth );
    //otherwise your widget will not expose the
    //area where this class works
    void setBorderWidth(QWidget* widget, int newBorderWidth );
    int borderWidth(QWidget* widget);

protected:
    virtual bool eventFilter( QObject* obj, QEvent* event );

private:
    NcFramelessHelperImpl* d;
};

#endif // NC_FRAMELESS_HELPER_H
