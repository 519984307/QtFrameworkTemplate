SOURCES += \
    $$PWD/CAppSingle.cpp \
    main.cpp \
    pluginmanager.cpp \
    mainapplication.cpp \

HEADERS += \
    $$PWD/CAppSingle.h \
    pluginmanager.h \
    mainapplication.h \

INCLUDEPATH        += ../interfaces
INCLUDEPATH += $$PWD/../../dependency/ui_sdk/include
INCLUDEPATH += $$PWD/../../dependency/billfish_sdk/sdk/include
INCLUDEPATH += $$PWD/../../dependency/MoyeaBased/include
INCLUDEPATH += $$PWD/../../dependency/zlib_r/include
INCLUDEPATH += $$PWD/../../dependency/json_r/include
INCLUDEPATH += $$PWD/../../dependency/openssl_r/include
INCLUDEPATH += $$PWD/../../dependency/base_platform_sdk/include
INCLUDEPATH += $$PWD/../../dependency/billfish_sdk/sdk/include/libMediaSdk
