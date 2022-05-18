include(../../config.pri)

TARGET         = qjson
TEMPLATE       = lib
CONFIG        += staticlib warn_off
DESTDIR        = $$LIBSDESTDIR
include(qjson.pri)
