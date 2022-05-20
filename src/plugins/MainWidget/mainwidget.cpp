#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(IPluginManager *pluginManager, QWidget *parent)
{

}

MainWidget::~MainWidget()
{

}

QWidget* MainWidget::instance()
{
	return this;
}
