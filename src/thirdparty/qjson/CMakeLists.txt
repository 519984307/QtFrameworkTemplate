
INCLUDE_DIRECTORIES(.)
add_library(qjson STATIC
        stack.hh
        serializerrunnable.h
        serializer.h
        qobjecthelper.h
        qjson_export.h
        qjson_debug.h
        position.hh
        parserrunnable.h
        parser.h
        parser_p.h
        location.hh
        json_scanner.h
        json_parser.hh
        FlexLexer.h
        serializerrunnable.cpp
        serializer.cpp
        qobjecthelper.cpp
        parserrunnable.cpp
        parser.cpp
        json_scanner.cpp
        json_scanner.cc
        json_parser.cc
        )

target_link_libraries(qjson Qt5::Core Qt5::Widgets)