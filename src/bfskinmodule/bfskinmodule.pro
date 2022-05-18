include(../config.pri)
include(../install.pri)

TARGET             = $$TARGET_SKIN
TEMPLATE           = lib
CONFIG            += c++11
DESTDIR         = $$LIBSDESTDIR
CONFIG             += plugin

LIBS              += -L$$LIBSDESTDIR
LIBS += -l$$TARGET_UTILS
DEPENDPATH        += ..
INCLUDEPATH       += ..
DEFINES += BUILD_SKIN_LIB

DLLDESTDIR = $$BINDESTDIR
#Translation

include(bfskinmodule.pri)

include(../symbols.pri)


