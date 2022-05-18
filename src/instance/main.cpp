#include <QGuiApplication>
#include <QScreen>
#include <QLibrary>
#include <QDebug>
#include <QFont>
#include <QMap>
#if QT_VERSION < 0x050000
#include <QApplication>
#else
#include <QtWidgets/QApplication>
#endif

#include "mainapplication.h"
#include "definitions/basemoduletype.h"
//#include "download/networkaccessmanager.h"
//#include "interfaces/datacenter/data/iresponseinfo.h"
//#include "interfaces/datacenter/data/ifolderinfo.h"
//#include "interfaces/datacenter/data/ifileinfo.h"
//#include "interfaces/datacenter/data/itaginfo.h"
//#include "interfaces/datacenter/data/itypeinfo.h"
//#include "interfaces/datacenter/data/itaggroupinfo.h"
//#include "interfaces/datacenter/data/iscanduplicateresponseinfo.h"
//#include "interfaces/inetserver.h"
//#include "interfaces/datacenter/data/irecycleinfo.h"
//#include "interfaces/datacenter/iresourcelibrarymanager.h"
#include "CAppSingle.h"
#include <QCommandLineParser>
#include"utils/BFCommandLineParser.h"

int main(int argc, char* argv[]) {
  qRegisterMetaType<QVector<qint64>>("QVector<qint64>");


  QLocale::setDefault(QLocale(QLocale::Chinese, QLocale::AnyCountry));

  if (1) {
    // QScreen只有在QApplication初始化后才能获取，但是QApplication初始化后，再去设置QT_SCALE_FACTOR就不生效了。
    // 所以这里启用一个临时QApplication，用来获取QScreen，然后设置QT_SCALE_FACTOR。这样，后面的QApplication就可以生效了。
    QApplication app(argc, argv);
    // QScreen* screen = QGuiApplication::primaryScreen();
    // if(screen)
    {
      // qreal logicalDotsPerInch = screen->logicalDotsPerInch();
      // qreal physicalDotsPerInch = screen->physicalDotsPerInch();
      //double dpi  = logicalDotsPerInch / 96;
//            qDebug() << "primaryScreen Size:" << screen->size()
//                    << "physicalDotsPerInch:" << physicalDotsPerInch
//                    << "logicalDotsPerInch:" << logicalDotsPerInch
//                    << "dpi:" << dpi;
            //if(dpi > 1.0)
            {
                QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
                QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
                //qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
                //QString sDpi = QString::number(dpi);
                //qputenv("QT_SCALE_FACTOR", sDpi.toLocal8Bit());
                qputenv("QT_ENABLE_HIGHDPI_SCALING", "1");

                // 5.14.0
#if QT_VERSION > 0x050E00
                QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
            }
        }
    }


  MainApplication app(argc, argv);


  qInfo() << "app.arguments()" << app.arguments();
   //判断开机自启动，如果是则后台启动
  bool auto_start = BFCommandLineParser::IsSetAutoRun();
  if (auto_start) {
    //再次检测数值是否正确
    QString start_value = BFCommandLineParser::GetAutoRunValue();
    if (start_value == "auto") {
      auto_start = true;
    } else {
      auto_start = false;
    }
  }

    if (app.isRunning()) {
    app.sendMessage("raise_window_noop", 2000);

    //绿色包启动方式启动已经运行的软件，直接打开绿色包需要打开的库
    if (BFCommandLineParser::IsSetGreenPacketLibPath()) {
      QString path_lib = BFCommandLineParser::GetGreenPacketLibPath();
      app.sendMessage("green_packet_lib_path:" + path_lib, 2000);
    }
    // delete nam;
    return EXIT_SUCCESS;
  }


//新版本经过上面的app.isRunning里的操作已经不会重复启动，软件单例检测为了一些旧版本兼容
#ifdef _WIN32
    QString guid = "{5D1C4995-CFC4-4212-8358-E5B69581BEA0}";
    CAppSingle::StartApp(guid.toStdWString().c_str());
#endif

#ifdef WIN32
    QFont font;
    font.setFamily("Microsoft YaHei");
    app.setFont(font);
#endif
    // app.setActivationWindow(&app,1);
    app.addLibraryPath(app.applicationDirPath());
    // QtSingleApplication app("id",argc,argv);
    //自启动的不显示主窗体
    app.setMainWidgetVisible(auto_start ? false : true);
    app.exec();
#ifdef _WIN32
    CAppSingle::StopApp();
#endif
    return 0;
}
