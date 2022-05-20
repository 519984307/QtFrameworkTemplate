TARGET          = mainwidget
include(mainwidget.pri)
include(../plugins.pri)

CONFIG += debug_and_release

QT += concurrent
win32{
    CONFIG(debug, debug|release){
        contains(QT_ARCH, x86_64) {

        LIBS += -L$$PWD/../../../dependency/zlib_r/win-x64-msvc/lib \
                -lzlib

        LIBS += -L$$PWD/../../../dependency/json_r/win-x64-msvc/lib \
                -ljson_vs19_v142_libmdd_a

        LIBS += -L$$PWD/../../../dependency/ui_sdk/win-x64-msvc/lib \
                    -lCommond \
                    -lGretaU \
                    -lLogServer \
                    -lNetwork \
                    -lSetting

        #LIBS += -L$$PWD/../../../dependency/MoyeaBased/win-x64-msvc/lib \
                    #-lmglobal



        } else {
        LIBS += -L$$PWD/../../../dependency/zlib_r/win-x86-msvc/lib \
                -lzlib

        LIBS += -L$$PWD/../../../dependency/json_r/win-x86-msvc/lib \
                -ljson_vs19_v142_libmdd_a

        LIBS += -L$$PWD/../../../dependency/ui_sdk/win-x86-msvc/lib \
                    -lCommond \
                    -lGretaU \
                    -lLogServer \
                    -lNetwork \
                    -lSetting


        # LIBS += -L$$PWD/../../../dependency/MoyeaBased/win-x86-msvc/lib \
                    #-lmglobal


        }
    } else {
        contains(QT_ARCH, x86_64) {
        LIBS += -L$$PWD/../../../dependency/zlib_r/win-x64-msvc/lib \
                -lzlib


        LIBS += -L$$PWD/../../../dependency/json_r/win-x64-msvc/lib \
                -ljson_vs19_v142_libmd_a

        LIBS += -L$$PWD/../../../dependency/ui_sdk/win-x64-msvc/lib \
                    -lCommon \
                    -lGretaU \
                    -lLogServer \
                    -lNetwork \
                    -lSetting

        #LIBS += -L$$PWD/../../../dependency/MoyeaBased/win-x64-msvc/lib \
                    #-lmglobal

        } else {
         LIBS += -L$$PWD/../../../dependency/zlib_r/win-x86-msvc/lib \
                -lzlib

         LIBS += -L$$PWD/../../../dependency/json_r/win-x86-msvc/lib \
                -ljson_vs19_v142_libmd_a


         LIBS += -L$$PWD/../../../dependency/ui_sdk/win-x86-msvc/lib \
                    -lCommon \
                    -lGretaU \
                    -lLogServer \
                    -lNetwork \
                    -lSetting

         #LIBS += -L$$PWD/../../../dependency/MoyeaBased/win-x86-msvc/lib \
                    #-lmglobal
        }
    }
}

macx{
         LIBS += -L$$PWD/../../../dependency/ui_sdk/osx-x64\
                    -lCommon \
                    -lLogServer \

#        LIBS += \
#                -L"../../../dependency/ATAnalytics/PLCrashReporter" \
#                -L"../../../dependency/openssl_r/osx-x64" \
#                -L"../../../dependency/sqlite3_r/osx-x64" \
#                -L"../../../dependency/iconv_r/osx-x64" \
#                -L"/usr/lib"\
#                -lCrashReporter-MacOSX-Static \
#                -Bstatic ../../../dependency/openssl_r/osx-x64/libcrypto.a \
#                -Bstatic ../../../dependency/openssl_r/osx-x64/libssl.a \
#                -lsqlite3

        LIBS += \
                -L$$PWD/../../../dependency/ATAnalytics/PLCrashReporter \
                -L$$PWD/../../../dependency/openssl_r/osx-x64 \
                -L$$PWD/../../../dependency/sqlite3_r/osx-x64 \
                -L$$PWD/../../../dependency/iconv_r/osx-x64 \
                -L"/usr/lib"\
                -lCrashReporter-MacOSX-Static \
                -lcrypto \
                -lssl \
                -lsqlite3 \


        LIBS += -L$$PWD/../../../dependency/zlib_r/osx-x64 \
                 -lz

        LIBS += -L$$PWD/../../../dependency/billfish_sdk/sdk/osx-x64 \
                -licuuc.54 \
                -licui18n.54 \
                -licudata.54 \
                -liconv.2.4.0 \

}


INCLUDEPATH += $$PWD/../../../dependency/ui_sdk/include
INCLUDEPATH += $$PWD/../../../dependency/billfish_sdk/sdk/include
INCLUDEPATH += $$PWD/../../../dependency/MoyeaBased/include
INCLUDEPATH += $$PWD/../../../dependency/zlib_r/include
INCLUDEPATH += $$PWD/../../../dependency/json_r/include
INCLUDEPATH += $$PWD/../../../dependency/openssl_r/include
INCLUDEPATH += $$PWD/../../../dependency/base_platform_sdk/include
INCLUDEPATH += $$PWD/Preferences

