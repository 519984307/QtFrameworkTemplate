HEADERS += \
    $$PWD/FramelessHelper.h \
    $$PWD/bfBaseWindow/BFFontSetting.h \
    $$PWD/bfBaseWindow/BFMessageBox.h \
    $$PWD/bfBaseWindow/BfProgressDialog.h \
    $$PWD/bfBaseWindow/CNotificationFloatingWidget.h \
    $$PWD/bfBaseWindow/CResourceItem.h \
    $$PWD/bfBaseWindow/CScrollArea.h \
    $$PWD/bfBaseWindow/CLineEdited.h \
    $$PWD/bfBaseWindow/BFScrollBar.h \
    $$PWD/bfBaseWindow/PngArrayPlayWid.h \
    $$PWD/bfBaseWindow/CNewWidget.h \
    $$PWD/bfBaseWindow/CPushButton.h \
    $$PWD/bfBaseWindow/BFSkinManager.h \
    $$PWD/bfBaseWindow/CTitleToolTip.h \
    $$PWD/bfBaseWindow/CTitleBarWidget.h \
    $$PWD/bfBaseWindow/CPopupTitleBarWidget.h \
    $$PWD/bfBaseWindow/CPopupDialog.h \
    $$PWD/bfBaseWindow/CLineEdited.h \
    $$PWD/bfBaseWindow/BFComboBoxView.h \
    $$PWD/bfBaseWindow/BFImportEntranceWidget.h \
    $$PWD/bfBaseWindow/BFCustomMenu.h \
    $$PWD/bfBaseWindow/CIndexFloatingDialog.h \
    $$PWD/bfBaseWindow/CustomControls.h \
    $$PWD/bfBaseWindow/CHyperlinkLabel.h \
    $$PWD/bfBaseWindow/CIndexToCopyResultDialog.h \
    $$PWD/bfBaseWindow/CListSearchLineEdit.h \
    $$PWD/bfBaseWindow/BFHidenSideWidget.h \
    $$PWD/bfBaseWindow/BFSliderActionWidget.h \
    $$PWD/bfcrossplatformutils.h \
    $$PWD/bfobserver.h \
    $$PWD/bfqtutils.h \
    $$PWD/BFCommandLineParser.h \
    $$PWD/pimpl.h \
    $$PWD/pimpl_impl.h \
    $$PWD/pixmapconverter.h \
    clickablelabel.h \
    borderpixmap.h \
    borderimage.h \
    unzipfile.h \
    utilsexport.h \
    skinmanager.h \
    circleavatarlabel.h \
    windowsizetoolbar.h \
    toolbutton.h \
    colors.h \
    regexp.h \
    log.h \
    console.h \
    versionparser.h \
    messagebox.h \
    bftypeutils.h\
    QtFlieOperation.h\
    mapwidget.h\
    bfcheckfilestate.h \
    bfstructoperate.h \

SOURCES += \
    $$PWD/FramelessHelper.cpp \
    $$PWD/bfBaseWindow/BFFontSetting.cpp \
    $$PWD/bfBaseWindow/BFMessageBox.cpp \
    $$PWD/bfBaseWindow/BfProgressDialog.cpp \
    $$PWD/bfBaseWindow/CNotificationFloatingWidget.cpp \
    $$PWD/bfBaseWindow/CResourceItem.cpp \
    $$PWD/bfBaseWindow/CScrollArea.cpp \
    $$PWD/bfBaseWindow/CLineEdited.cpp \
    $$PWD/bfBaseWindow/BFScrollBar.cpp \
    $$PWD/bfBaseWindow/PngArrayPlayWid.cpp \
    $$PWD/bfBaseWindow/CNewWidget.cpp \
    $$PWD/bfBaseWindow/CPushButton.cpp \
    $$PWD/bfBaseWindow/BFSkinManager.cpp \
    $$PWD/bfBaseWindow/CTitleToolTip.cpp \
    $$PWD/bfBaseWindow/CTitleBarWidget.cpp \
    $$PWD/bfBaseWindow/CPopupTitleBarWidget.cpp \
    $$PWD/bfBaseWindow/CPopupDialog.cpp \
    $$PWD/bfBaseWindow/CLineEdited.cpp \
    $$PWD/bfBaseWindow/BFComboBoxView.cpp \
    $$PWD/bfBaseWindow/BFImportEntranceWidget.cpp \
    $$PWD/bfBaseWindow/BFCustomMenu.cpp \
    $$PWD/bfBaseWindow/CIndexFloatingDialog.cpp \
    $$PWD/bfBaseWindow/CustomControls.cpp \
    $$PWD/bfBaseWindow/CHyperlinkLabel.cpp \
    $$PWD/bfBaseWindow/CIndexToCopyResultDialog.cpp \
    $$PWD/bfBaseWindow/CListSearchLineEdit.cpp \
    $$PWD/bfBaseWindow/BFHidenSideWidget.cpp \ 
    $$PWD/bfBaseWindow/BFSliderActionWidget.cpp \
    $$PWD/bfcrossplatformutils.cpp \
    $$PWD/bfobserver.cpp \
    $$PWD/bfqtutils.cpp \
    $$PWD/BFCommandLineParser.cpp \
    $$PWD/pixmapconverter.cpp \
    clickablelabel.cpp \
    borderpixmap.cpp \
    borderimage.cpp \
    unzipfile.cpp \
    skinmanager.cpp \
    circleavatarlabel.cpp \
    windowsizetoolbar.cpp \
    toolbutton.cpp \
    colors.cpp \
    regexp.cpp \
    log.cpp \
    console.cpp \
    versionparser.cpp \
    messagebox.cpp \
    bftypeutils.cpp \
    QtFlieOperation.cpp\
    mapwidget.cpp\
    bfstructoperate.cpp \

FORMS += \
    $$PWD/bfBaseWindow/BFMessageBox.ui \
    $$PWD/bfBaseWindow/PngArrayPlayWid.ui \
    $$PWD/bfBaseWindow/CListSearchLineEdit.ui \
    messagebox.ui \

win32{

    SOURCES += widgetmanager.cpp \
     NcFramelessHelper.cpp \

    HEADERS += \
        $$PWD/bfBaseWindow/BFFileAndFolderDialog.h \
        system_os.h \

     SOURCES += \
        $$PWD/bfBaseWindow/BFFileAndFolderDialog.cpp \
        system_os.cpp \
}

macx{

OBJECTIVE_SOURCES += \
    Platform/MacOs/SystemUtils.mm \
    widgetmanager.mm \
    NcFramelessHelper.mm

INCLUDEPATH += ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK \

HEADERS += Platform/MacOs/os_define.h \
    Platform/MacOs/SystemUtilsCInterface.h \
    Platform/MacOs/SystemUtils.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SSZipArchive.h \

SOURCES += Platform/MacOs/os_define.cpp \

OBJECTIVE_SOURCES += \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SAGzipUtility.m \

}
