HEADERS = mainwidgetplugin.h \
          mainwidget.h 

SOURCES = mainwidgetplugin.cpp \
          mainwidget.cpp 

FORMS += \
         mainwidget.ui 


win32{
 #HEADERS += CDiskDriver.h
 #SOURCES += CDiskDriver.cpp 
}

macx{
 HEADERS += macos/BFActionManager.h 
 SOURCES += macos/BFActionManager.cpp
}
