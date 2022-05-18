include(../../config.pri)

TARGET     = zlib
TEMPLATE   = lib
CONFIG    -= qt
CONFIG    += staticlib warn_off
DESTDIR        = $$LIBSDESTDIR
include(zlib.pri)
