SOURCES += \
    serializerrunnable.cpp \
    serializer.cpp \
    qobjecthelper.cpp \
    parserrunnable.cpp \
    parser.cpp \
    json_scanner.cpp \
    json_scanner.cc \
    json_parser.cc

HEADERS += \
    stack.hh \
    serializerrunnable.h \
    serializer.h \
    qobjecthelper.h \
    qjson_export.h \
    qjson_debug.h \
    position.hh \
    parserrunnable.h \
    parser.h \
    parser_p.h \
    location.hh \
    json_scanner.h \
    json_parser.hh \
    FlexLexer.h

OTHER_FILES += \
    json_scanner.yy \
    json_parser.yy
