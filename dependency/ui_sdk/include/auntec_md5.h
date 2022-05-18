#ifndef AUNTEC_MD5_H__
#define AUNTEC_MD5_H__

#include "auntec_base_types.h"

#include <string>
using namespace std;

namespace AuntecBased
{
#ifdef WIN32
	string auntec_file_md5(const char* file, bool bUpper=false);

	string auntec_file_md5(const wchar_t* file, bool bUpper=false);
#endif

	string auntec_data_md5(const void* szData, size_t nDataLen, bool bUpper=false);
}

#endif
