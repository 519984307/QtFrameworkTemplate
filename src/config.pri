#各个pro项目设置编译中间过程临时文件路径,这里就设定为了工程主目录里的tmp文件夹,里面是各个工程文件名的文件夹
#指定ui文件转化的头文件存放目录指定qrc文件转化的头文件存放目录
RCC_DIR += ../../tmp/$$TARGET
#指定Moc文件存放目录
MOC_DIR += ../../tmp/$$TARGET
#目标文件(.obj)存放目录
OBJECTS_DIR += ../../tmp/$$TARGET
#指定ui文件转化的头文件存放目录
UI_DIR += forms

#设置名字
TARGET_INSTANCE    = QtFrameworkTemplate
TARGET_MANAGER     = QtFrameworkTemplateManager
TARGET_UTILS       = utils
TARGET_WEBWIDGET   = webwidget
TARGET_SKIN        = skin
TARGET_TRACE_EVENT = traceEvent
TARGET_DOWNLOAD    = bfdownload
TARGET_INTERFACE_PLUGIN = interfaces_plugin

#指定软件bin目录
BINDESTDIR = $$PWD/../bin
#指定软件目录输出的库目录
LIBSDESTDIR = $$PWD/libs
#指定输出的插件库目录
PLUGINSDESTDIR = $$BINDESTDIR/ui_plugins

#引入networl/core两个模块(本质就是包含头文件 链接库文件))
QT +=  network core

#对不同版本qt包含做特殊处理
isEqual(QT_MAJOR_VERSION, 5) {
QT += widgets printsupport sql widgets-private gui-private core-private svg-private
}else{
QT +=  gui
}

#mac平台处理
macx {
QT += macextras
}


win32{
#设置项目支持C++11
CONFIG += c++11
#设置项目支持libc++库
CONFIG += libc++
#下面两行实现项目生成的可执行文件中包含DebugInfo,可能会影响debug和release下的调试
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
}

#包含一些库
win32-msvc* {
    DEFINES *= W7API
    LIBS += User32.lib Ole32.lib Shell32.lib ShlWapi.lib Gdi32.lib ComCtl32.lib
}

macx {
QMAKE_TARGET_BUNDLE_PREFIX = "cn.billfish"
CONFIG += c++11
CONFIG += libc++
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
LIBS += -framework CoreServices -framework AppKit -framework Cocoa -framework IOKit -framework Carbon
#LIBS += -lssl -lcrypto -framework CoreServices -framework AppKit -framework Cocoa -framework IOKit -framework Carbon
LIBS += -framework Foundation
LIBS += -framework SystemConfiguration
LIBS += -framework CoreFoundation
LIBS += -framework Carbon
LIBS += -lobjc
# The ObjC API changed with Catalina, use the old one for now
# (there is code to use the new API, but it is untested,
# search for OBJC_OLD_DISPATCH_PROTOTYPES in the sources).
DEFINES += "OBJC_OLD_DISPATCH_PROTOTYPES=1"
QMAKE_LFLAGS    += -framework Carbon -framework IOKit -framework Cocoa -framework AppKit
CONFIG(release, debug|release):DEFINES += NDEBUG
QMAKE_CFLAGS_RELEASE += $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_CXXFLAGS_RELEASE += $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_OBJECTIVE_CFLAGS_RELEASE += $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE += $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
}

#设置项目
CONFIG += x86 ppc x86_64 ppc64

#Configurable values
isEmpty(INSTALL_PREFIX) {
  win32:INSTALL_PREFIX   = "c:"
  macx: INSTALL_PREFIX   = /Applications
}

isEmpty(INSTALL_APP_DIR){
  win32:INSTALL_APP_DIR  = $${TARGET_INSTANCE}
  macx: INSTALL_APP_DIR  = $${TARGET_INSTANCE}.app
}

isEmpty(INSTALL_LIB_DIR){
  win32:INSTALL_LIB_DIR  = .
  macx: INSTALL_LIB_DIR  = Frameworks
}

isEmpty(INSTALL_RES_DIR) {
  win32:INSTALL_RES_DIR  = .
  macx: INSTALL_RES_DIR  = Resources
}


win32 {
  DEFINES               += PLUGINS_DIR='\\\"./$${INSTALL_LIB_DIR}/ui_plugins\\\"'
  DEFINES               += RESOURCES_DIR='\\\"./$${INSTALL_RES_DIR}/resources\\\"'
  DEFINES               += TRANSLATIONS_DIR='\\\"./$${INSTALL_RES_DIR}/translations\\\"'
} else:macx {
  DEFINES               += PLUGINS_DIR='\\\"../PlugIns\\\"'
  DEFINES               += RESOURCES_DIR='\\\"../$${INSTALL_RES_DIR}\\\"'
  DEFINES               += TRANSLATIONS_DIR='\\\"../$${INSTALL_RES_DIR}/translations\\\"'
}
