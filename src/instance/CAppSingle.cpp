#include "CAppSingle.h"

#ifdef _WIN32
typedef struct tagWNDINFO{
	HWND hWnd;
} WNDINFO, *LPWNDINFO;

BOOL CALLBACK CAppSingle::EnumAllWindowCallback(HWND hWnd, LPARAM lParam)
{
	wchar_t bufName[MAX_PATH] = {0};
	LPWNDINFO pInfo = (LPWNDINFO)lParam;
	::GetClassName(hWnd, bufName, MAX_PATH-1);
	const wchar_t wnd_class_name[] = L"Qt5152QWindowIcon";
	if(0 != wcscmp(wnd_class_name, bufName)){
	}else if ( GetProp( hWnd, CAppSingle::m_guidStr ) == 0 ){
	}else{
		pInfo->hWnd = hWnd;
		return FALSE;
	}
	return TRUE;
}


void CAppSingle::ActiveMainWindow()
{
	WNDINFO info = {NULL};
	::EnumWindows(CAppSingle::EnumAllWindowCallback, (LPARAM)&info);
	if(info.hWnd != NULL){
		// ::PostMessageW(info.hWnd, WM_ACTIVE_MAINWND, NULL, NULL); // FIX: QT的窗口激活？
		SendMessage( info.hWnd, WM_USER + 0x0F16, true, 0 ); // #define WM_USER_SHOW_WINDOW  WM_USER + 0x0F16

//		ShowWindow( info.hWnd, SW_SHOWNORMAL );
		SetForegroundWindow( info.hWnd );

		LPCWSTR p = GetCommandLineW();
		if ( !p ){ assert( 0 ); // 起码有软件本身路径
		}else if ( wcschr( p, L' ' ) ){ // 有不止一个参数？
			COPYDATASTRUCT cd = { 0 };
			cd.cbData = ( 1 + wcslen( p ) ) * sizeof( wchar_t );
			cd.lpData = ( void* )p;

			SendMessage( info.hWnd, WM_COPYDATA, ( WPARAM )0, ( LPARAM )&cd );
		}
	}
}

void CAppSingle::StartApp(const wchar_t* appGuidStr)
{
	assert(NULL != appGuidStr && wcslen(appGuidStr) > 0 && wcslen(appGuidStr) < 64);
	wcscpy_s(CAppSingle::m_guidStr, 63, appGuidStr);
	m_hInstance = CreateMutexW(NULL, TRUE, CAppSingle::m_guidStr);
	if(GetLastError() == ERROR_ALREADY_EXISTS){
		ActiveMainWindow();
		StopApp();
		exit(0);
	}
}

void CAppSingle::StopApp()
{
	if(m_hInstance != NULL && m_hInstance != INVALID_HANDLE_VALUE){
		CloseHandle((HANDLE)m_hInstance);
		m_hInstance = NULL;
	}
	ZeroMemory(CAppSingle::m_guidStr, 64*sizeof(wchar_t));
}
#endif // _WIN32

wchar_t CAppSingle::m_guidStr[64] = {0};

void* CAppSingle::m_hInstance = NULL;
