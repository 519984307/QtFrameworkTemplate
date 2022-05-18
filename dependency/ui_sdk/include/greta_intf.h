#ifndef GRETA_INTF_H__
#define GRETA_INTF_H__

// MGICALL
#ifndef MGICALL
#	ifdef _MSC_VER
#		define MGICALL __stdcall
#	elif defined(__GNUC__)
#		define MGICALL __attribute__((__stdcall))
#	else
#		define MGICALL
#	endif
#endif

// MGIEXPORT
#ifndef MGIEXPORT
#	ifdef __GNUC__
#		define MGIEXPORT __attribute__((visibility("default")))
#	else
#		define MGIEXPORT
#	endif
#endif

#if defined(UNICODE) | defined(_UNICODE)
extern "C"
MGIEXPORT
bool MGICALL MGIMatch(const wchar_t* pText, const wchar_t* pattern);

extern "C"
MGIEXPORT
bool MGICALL MGIPhone(const wchar_t* pText);

extern "C"
MGIEXPORT
bool MGICALL MGIEmail(const wchar_t* pText);
#else
extern "C"
MGIEXPORT
bool MGICALL MGIMatch(const char* pText, const char* pattern);

extern "C"
MGIEXPORT
bool MGICALL MGIPhone(const char* pText);

extern "C"
MGIEXPORT
bool MGICALL MGIEmail(const char* pText);
#endif

#endif
