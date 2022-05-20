#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include"interfaces/MainWidget/imainwidget.h"
#include"interfaces/ipluginmanager.h"
#include<QWidget>
namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget, public IMainWidget {
 
public:
    explicit MainWidget(IPluginManager* pluginManager, QWidget* parent = 0);
     ~MainWidget();

     virtual QWidget* instance();
};

#endif  // MAINWIDGET_H
