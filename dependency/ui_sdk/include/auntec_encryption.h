#ifndef _AUNTEC_ENCRYPTION_H
#define _AUNTEC_ENCRYPTION_H
#include "auntec_string_util.h"

namespace AuntecBased
{
	string auntec_encode(const void* pData, int dataSize, const char* pKey, int keySize=0);
	string auntec_decode(const void* pData, int dataSize, const char* pKey, int keySize=0);
};

#endif
