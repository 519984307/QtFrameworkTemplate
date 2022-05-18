#ifndef CAPP_SINGLE_H__
#define CAPP_SINGLE_H__

#include "auntec_base_types.h"

class CAppSingle
{
public:
	/*!
	@brief 开启单例模式
	*/
	static void StartApp(const wchar_t* appGuidStr);

	/*!
	@brief 销毁单例模式
	*/
	static void StopApp();

private:
#ifdef _WIN32
	static BOOL CALLBACK EnumAllWindowCallback(HWND hWnd, LPARAM lParam);
#endif
	static void ActiveMainWindow();

private:
	static void* m_hInstance;
	static wchar_t m_guidStr[64];
};

#endif
