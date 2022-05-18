include(../../config.pri)

TARGET         = minizip
TEMPLATE       = lib
CONFIG        -= qt
CONFIG        += staticlib warn_off
INCLUDEPATH   += ../..
DESTDIR        = $$LIBSDESTDIR
include(minizip.pri)
