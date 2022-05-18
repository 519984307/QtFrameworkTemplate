
#pragma once

#define STRICT_TYPED_ITEMIDS  // in case you do IDList stuff you want this on
                              // for better type saftey
#define UNICODE 1

#include <objbase.h>
#include <propkey.h>
#include <propvarutil.h>
#include <shlobj.h>   // shell stuff
#include <shlwapi.h>  // QISearch, easy way to implement QI
#include <strsafe.h>
#include <windows.h>
#include <windowsx.h>  // for WM_COMMAND handling macros
#include <shellapi.h>
#include <QString>
#include <QWidget>

#pragma comment(lib, "shlwapi.lib")   // link to this
#pragma comment(lib, "comctl32.lib")  // link to this
#pragma comment(lib, "propsys.lib")   // link to this

// set up common controls v6 the easy way
#pragma comment( \
    linker,      \
    "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

void PickFilesAndFolders(QWidget* widget = nullptr, const QString& title = QString(),
                         const QString& dir = QString());
