#ifndef ISETTING_H__
#define ISETTING_H__

#include "auntec_base_types.h"

// ISTCALL
#ifndef ISTCALL
#	ifdef _MSC_VER
#		define ISTCALL __stdcall
#	elif defined(__GNUC__)
#		define ISTCALL __attribute__((__stdcall))
#	else
#		define ISTCALL
#	endif
#endif

// ISTEXPORT
#ifndef ISTEXPORT
#	ifdef __GNUC__
#		define ISTEXPORT __attribute__((visibility("default")))
#	else
#		define ISTEXPORT
#	endif
#endif

class ISetting
{
public:
	// traversal
	virtual signed int ISTCALL GetSessionCount() = 0;
	virtual const wchar_t* ISTCALL GetSessionName(signed int sessionIndex) = 0;
	virtual signed int ISTCALL GetSessionKeyCount(signed int sessionIndex) = 0;
	virtual const wchar_t* ISTCALL GetSessionKey(signed int sessionIndex, signed int keyIndex) = 0;
	virtual const wchar_t* ISTCALL GetSessionValue(signed int sessionIndex, signed int keyIndex) = 0;

	// read
	virtual const wchar_t* ISTCALL GetString(const wchar_t* sessionName, const wchar_t* keyName, const wchar_t* defaultValue=NULL) = 0;
	virtual int64_t ISTCALL GetInteger(const wchar_t* sessionName, const wchar_t* keyName, const int64_t& defaultValue=0) = 0;
	virtual double ISTCALL GetDouble(const wchar_t* sessionName, const wchar_t* keyName, const double& defaultValue=.0) = 0;
	virtual bool ISTCALL GetBoolean(const wchar_t* sessionName, const wchar_t* keyName, const bool& defaultValue=false) = 0;

	// write
	virtual bool ISTCALL SetString(const wchar_t* sessionName, const wchar_t* keyName, const wchar_t* keyValue) = 0;
	virtual bool ISTCALL SetInteger(const wchar_t* sessionName, const wchar_t* keyName, const int64_t& keyValue) = 0;
	virtual bool ISTCALL SetDouble(const wchar_t* sessionName, const wchar_t* keyName, const double& keyValue) = 0;
	virtual bool ISTCALL SetBoolean(const wchar_t* sessionName, const wchar_t* keyName, const bool& keyValue) = 0;

	// delete
	virtual bool ISTCALL DelKey(const wchar_t* sessionName, const wchar_t* keyName) = 0;

	//save to file
	virtual bool ISTCALL SaveFile() = 0;
	// free
	virtual void ISTCALL Free() = 0;
};

extern "C"
ISTEXPORT
ISetting* ISTCALL CreateSetting(const wchar_t* filePath, bool bSave=false);

#endif
