include(../../config.pri)

TARGET         = qxtglobalshortcut
TEMPLATE       = lib
CONFIG        += staticlib warn_off
DESTDIR        = $$LIBSDESTDIR
DEFINES       += QXT_STATIC
include(qxtglobalshortcut.pri)
