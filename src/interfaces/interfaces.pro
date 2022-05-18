include(../config.pri)
include(../install.pri)

TARGET             = $$TARGET_INTERFACE_PLUGIN
TEMPLATE           = lib
CONFIG            += c++11
DESTDIR         = $$LIBSDESTDIR
CONFIG             += plugin
LIBS              += -L$$LIBSDESTDIR
DEPENDPATH        += ..
INCLUDEPATH       += ..
DEFINES += BUILD_INTERFACE_LIB

DLLDESTDIR = $$BINDESTDIR
#Translation

INCLUDEPATH += $$PWD/../../dependency/ui_sdk/include
INCLUDEPATH += $$PWD/../../dependency/billfish_sdk/sdk/include
INCLUDEPATH += $$PWD/../../dependency/MoyeaBased/include
INCLUDEPATH += $$PWD/../../dependency/zlib_r/include
INCLUDEPATH += $$PWD/../../dependency/json_r/include
INCLUDEPATH += $$PWD/../../dependency/openssl_r/include
INCLUDEPATH += $$PWD/../../dependency/base_platform_sdk/include
INCLUDEPATH += $$PWD/../../dependency/billfish_sdk/sdk/include/libMediaSdk
INCLUDEPATH += $$PWD/../utils

include(interfaces.pri)

include(../symbols.pri)


