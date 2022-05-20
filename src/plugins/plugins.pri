include(../config.pri)
include(../install.pri)

TEMPLATE            = lib
CONFIG             += plugin


LIBS               += -L$$LIBSDESTDIR
DEPENDPATH         += ../..
INCLUDEPATH        += ../..
INCLUDEPATH        += ../../thirdparty
INCLUDEPATH        += ../../interfaces
INCLUDEPATH        += ../../../dependency/billfish_sdk/sdk/include/
INCLUDEPATH        += ../../../dependency/billfish_sdk/sdk/include/libMediaSdk
INCLUDEPATH        += ../../../dependency/MoyeaBased/include

LIBS += -L$$LIBSDESTDIR
LIBS += -l$$TARGET_UTILS -lqxtglobalshortcut -lqjson
LIBS += -l$$TARGET_SKIN
#LIBS += -l$$TARGET_TRACE_EVENT
#LIBS += -l$$TARGET_DOWNLOAD
LIBS += -lbfcommon
#LIBS += -l$$TARGET_INTERFACE_PLUGIN
INCLUDEPATH += ../../utils
INCLUDEPATH += ../../bfskinmodule
INCLUDEPATH += ../../bfcommon

macx {
  QMAKE_LFLAGS    += -framework Carbon -framework IOKit -framework Cocoa
    DESTDIR         = $$PLUGINSDESTDIR
    LIBS += -L$$PWD/../../dependency/zlib_r/osx-x64 \
             -lz

    # 修改 path
    DYLIB = lib$${TARGET}.dylib
    QMAKE_POST_LINK += install_name_tool -change lib$${TARGET_SKIN}.dylib  @executable_path/lib$${TARGET_SKIN}.dylib  $$DESTDIR/$${DYLIB};
   # QMAKE_POST_LINK += install_name_tool -change lib$${TARGET_TRACE_EVENT}.dylib  @executable_path/lib$${TARGET_TRACE_EVENT}.dylib  $$DESTDIR/$${DYLIB};
    QMAKE_POST_LINK += install_name_tool -change lib$${TARGET_DOWNLOAD}.dylib  @executable_path/lib$${TARGET_DOWNLOAD}.dylib  $$DESTDIR/$${DYLIB};
    QMAKE_POST_LINK += install_name_tool -change libbfcommon.dylib  @executable_path/libbfcommon.dylib  $$DESTDIR/$${DYLIB};
    QMAKE_POST_LINK += install_name_tool -change lib$${TARGET_INTERFACE_PLUGIN}.dylib  @executable_path/lib$${TARGET_INTERFACE_PLUGIN}.dylib  $$DESTDIR/$${DYLIB};
    message($$QMAKE_POST_LINK)

} else:win32 {
  LIBS            += -luser32
    DESTDIR         = $$LIBSDESTDIR
    DLLDESTDIR = $$PLUGINSDESTDIR
}


#DESTDIR        = ../../libs

#Install
target.path         = $$INSTALL_PLUGINS
INSTALLS           += target

#Translation
TRANS_SOURCE_ROOT   = ../..
include(../translations.pri)
include(../symbols.pri)


