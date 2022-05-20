#include "mainwidgetplugin.h"

#if QT_VERSION < 0x050000
#include <QApplication>
#else
#include <QtWidgets/QApplication>
#endif
#include <QDesktopWidget>
#include <QStackedWidget>
#include <QDesktopServices>
#include <QTimer>

#include "widgetmanager.h"
#include "utils/console.h"
#include "utils/action.h"
#include "utils/messagebox.h"
//#include "bfEventTrack/bfeventtrack.h"

MainWidgetPlugin::MainWidgetPlugin()
{
}

MainWidgetPlugin::~MainWidgetPlugin()
{
#ifdef WIN32
  if(m_mainWidget)
    {
      m_mainWidget->deleteLater();
    }
#endif
}

void MainWidgetPlugin::pluginInfo(IPluginInfo* aPluginInfo) {
  aPluginInfo->name = tr("Main Widget");
  aPluginInfo->description =
      tr("Allows other modules to place their widgets in the main widget");
  aPluginInfo->version = "1.0";
  aPluginInfo->author = "Chuck Wilson";
  aPluginInfo->homePage = CLIENT_HOME_PAGE;
}

bool MainWidgetPlugin::initConnections(IPluginManager* aPluginManager,
                                       int& aInitOrder) {
  Q_UNUSED(aInitOrder);
  m_pluginManager = aPluginManager;

  /*
  IPlugin* plugin =
  m_pluginManager->pluginInterface("IProjectAccessManagerPlugin").value(0,NULL);
  if (plugin)
  {
      m_projectManager = qobject_cast<IProjectAccessManagerPlugin
  *>(plugin->instance()); if(m_projectManager)
      {

      }
  }
  */

    return true;
}

bool MainWidgetPlugin::initObjects()
{
    return true;
}

bool MainWidgetPlugin::initSettings()
{
    return true;
}

bool MainWidgetPlugin::startPlugin() {
    showStartupDialog();
    if(m_mainWidget == NULL)
    {
      //uint32_t startTime = BfEventTrack::GetInstance()->getStartTime();
      m_mainWidget = new MainWidget(m_pluginManager, NULL);
      //BfEventTrack::GetInstance()->LoadMainWidget(startTime, m_mainWidget);
    }
    return true;
}

//IMainWidgetPlugin
IMainWidget *MainWidgetPlugin::mainWidget() const
{
    return m_mainWidget;
}

void MainWidgetPlugin::showMainWidget()
{
    if(!m_pluginManager)
        return;

    WidgetManager::showActivateRaiseWindow(m_mainWidget);
    closeStartupDialog();
}

void MainWidgetPlugin::showStartupDialog()
{
    if(!m_pluginManager)
        return;
}

void MainWidgetPlugin::closeStartupDialog()
{

}

bool MainWidgetPlugin::isStartDialogVisible() const
{
    return false;
}


void MainWidgetPlugin::onAboutToClose()
{

}

void MainWidgetPlugin::onMainWidgetAboutToDestory()
{
    if(m_mainWidget)
    {
        m_mainWidget->instance()->close();
        m_mainWidget->instance()->deleteLater();
        m_mainWidget = NULL;
    }
}


#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(plg_mainwidgetwplugin, MainWidgetPlugin)
#endif
