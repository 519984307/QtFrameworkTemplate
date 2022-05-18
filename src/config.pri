RCC_DIR += ../../tmp/$$TARGET
MOC_DIR += ../../tmp/$$TARGET
OBJECTS_DIR += ../../tmp/$$TARGET
UI_DIR += forms

TARGET_INSTANCE = QtFrameworkTemplate
TARGET_MANAGER  = QtFrameworkTemplateManager

TARGET_UTILS    = utils
TARGET_WEBWIDGET = webwidget
TARGET_SKIN    = skin
TARGET_TRACE_EVENT = traceEvent
TARGET_DOWNLOAD    = bfdownload
TARGET_INTERFACE_PLUGIN = interfaces_plugin

BINDESTDIR = $$PWD/../bin
LIBSDESTDIR = $$PWD/libs
PLUGINSDESTDIR = $$BINDESTDIR/ui_plugins


QT +=  network core

isEqual(QT_MAJOR_VERSION, 5) {
QT += widgets printsupport sql widgets-private gui-private core-private svg-private
} else {
QT +=  gui
}

macx {
QT += macextras
}

win32{
CONFIG += c++11
CONFIG += libc++
QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
}

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

CONFIG += x86 ppc x86_64 ppc64


#Configurable values
isEmpty(INSTALL_PREFIX) {
  win32:INSTALL_PREFIX   = "c:"
  macx: INSTALL_PREFIX   = /Applications
}

isEmpty(INSTALL_APP_DIR) {
  win32:INSTALL_APP_DIR  = $${TARGET_INSTANCE}
  macx: INSTALL_APP_DIR  = $${TARGET_INSTANCE}.app
}

isEmpty(INSTALL_LIB_DIR) {
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
