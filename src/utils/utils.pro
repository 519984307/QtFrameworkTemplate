include(../config.pri)
include(../install.pri)

TARGET             = $$TARGET_UTILS
TEMPLATE           = lib
CONFIG            += staticlib
CONFIG            += c++11
DESTDIR        = $$LIBSDESTDIR

LIBS              += -L$$LIBSDESTDIR
LIBS              += -lzlib -lminizip -lqxtglobalshortcut -llog4qt

INCLUDEPATH       += ../thirdparty
INCLUDEPATH       += ../thirdparty/minizip
DEPENDPATH        += ..
INCLUDEPATH       += ..
INCLUDEPATH       += bfBaseWindow

QT -= phonon xmlpatterns
QT += xml

#Translation
TRANS_SOURCE_ROOT  = ..
include(../translations.pri)


include(utils.pri)


