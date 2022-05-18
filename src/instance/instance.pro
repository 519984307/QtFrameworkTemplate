include(../config.pri)
include(../install.pri)
include(./qtsingleapplication/src/qtsingleapplication.pri)
TARGET             = $$TARGET_INSTANCE
TEMPLATE           = app

QT += core xml network

LIBS              += -L$$LIBSDESTDIR
DESTDIR            = $$BINDESTDIR

DEPENDPATH        += ..
INCLUDEPATH       += ..

INCLUDEPATH       += ../thirdparty

LIBS += -L$$LIBSDESTDIR
LIBS += -l$$TARGET_UTILS -lqxtglobalshortcut
LIBS += -l$$TARGET_SKIN
LIBS += -l$$TARGET_TRACE_EVENT
LIBS += -l$$TARGET_DOWNLOAD
LIBS += -llog4qt
LIBS += -lbfcommon
INCLUDEPATH += ../utils
INCLUDEPATH += ../bfskinmodule
win32{
    CONFIG(debug, debug|release){
        contains(QT_ARCH, i386)  {
        LIBS += -L$$PWD/../../dependency/ui_sdk/win-x86-msvc/lib \
                    -lCommond \
                    -lGretaU \
                    -lLogServer \
                    -lNetwork \
                    -lSetting

        } else {
        LIBS += -L$$PWD/../../dependency/ui_sdk/win-x64-msvc/lib \
                    -lCommond \
                    -lGretaU \
                    -lLogServer \
                    -lNetwork \
                    -lSetting
        }
    } else {
        contains(QT_ARCH, i386)  {
        LIBS += -L$$PWD/../../dependency/ui_sdk/win-x86-msvc/lib \
                    -lCommon \
                    -lGretaU \
                    -lLogServer \
                    -lNetwork \
                    -lSetting
        } else {
         LIBS += -L$$PWD/../../dependency/ui_sdk/win-x64-msvc/lib \
                    -lCommon \
                    -lGretaU \
                    -lLogServer \
                    -lNetwork \
                    -lSetting
        }
    }
}

macx{
        LIBS += -L$$PWD/../../dependency/ui_sdk/osx-x64 \
                -lCommon \
                -lLogServer \

        LIBS += -L$$PWD/../../dependency/zlib_r/osx-x64 \
                 -lz

        DYLIB = $${TARGET}
        QMAKE_POST_LINK += install_name_tool -change lib$${TARGET_SKIN}.dylib  @executable_path/lib$${TARGET_SKIN}.dylib  $$DESTDIR/Billfish.app/Contents/MacOS/Billfish;
        QMAKE_POST_LINK += install_name_tool -change lib$${TARGET_TRACE_EVENT}.dylib  @executable_path/lib$${TARGET_TRACE_EVENT}.dylib  $$DESTDIR/Billfish.app/Contents/MacOS/Billfish;
        QMAKE_POST_LINK += install_name_tool -change lib$${TARGET_DOWNLOAD}.dylib  @executable_path/lib$${TARGET_DOWNLOAD}.dylib  $$DESTDIR/Billfish.app/Contents/MacOS/Billfish;
        QMAKE_POST_LINK += install_name_tool -change liblog4qt.dylib  @executable_path/liblog4qt.dylib  $$DESTDIR/Billfish.app/Contents/MacOS/Billfish;
        QMAKE_POST_LINK += install_name_tool -change libbfcommon.dylib  @executable_path/libbfcommon.dylib  $$DESTDIR/Billfish.app/Contents/MacOS/Billfish;
        message($$QMAKE_POST_LINK)



}

win32:RC_FILE      = instance.rc
macx:ICON          = icon.icns

#MacOS Info.plist
macx:QMAKE_INFO_PLIST = macosx/Info.plist

win32-msvc* {
    contains(QT_ARCH, i386) {
        message("32-bit")
        QMAKE_POST_LINK = export_x86.bat \"$(OutDir)\" \"$(QTDIR)\" \"$(VCInstallDir)\"
    } else {
        message("64-bit")
        QMAKE_POST_LINK = export_x64.bat \"$(OutDir)\" \"$(QTDIR)\" \"$(VCInstallDir)\"
    }
    #QMAKE_POST_LINK += $$quote($$AFTER_LINK_CMD_LINE)
}

#SVN Info

#isEmpty(SVN_REVISION) {
#  SVN_REVISION=$$system(svnversion -n -c ./../)
#  SVN_REVISION_INVALID = $$find(SVN_REVISION,Unversioned) $$find(SVN_REVISION,exported)
#}
#win32 {
#  exists(svninfo.h):system(del svninfo.h)
#  !isEmpty(SVN_REVISION):count(SVN_REVISION_INVALID,0) {
#    system(echo $${LITERAL_HASH}define SVN_REVISION \"$$SVN_REVISION\" >> svninfo.h) {
#      DEFINES         += SVNINFO
#      QMAKE_DISTCLEAN += svninfo.h
#    }
#  }
#} else {
#  exists(svninfo.h):system(rm -f svninfo.h)
#  !isEmpty(SVN_REVISION)::count(SVN_REVISION_INVALID,0) {
#    system(echo \\$${LITERAL_HASH}define SVN_REVISION \\\"$${SVN_REVISION}\\\" >> svninfo.h) {
#      DEFINES         += SVNINFO
#      QMAKE_DISTCLEAN += svninfo.h
#    }
#  }
#}


#Install
target.path        = $$INSTALL_BINS
#resources.path     = $$INSTALL_RESOURCES
#resources.files    = ../../resources/*
INSTALLS           += target

#Translation
TRANS_SOURCE_ROOT  = ..
include(../translations.pri)
include(../symbols.pri)
include(instance.pri)
