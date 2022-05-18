#pragma once
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
extern "C" {
#include <iconv.h>
}

#define _countof(a) (sizeof(a)/sizeof(*(a)))
#define GetRValue(color) (uint8_t)((color) & 0xff)
#define GetGValue(color) (uint8_t)(((color) >> 8) & 0xff)
#define GetBValue(color) (uint8_t)(((color) >> 16) & 0xff)
#define ZeroMemory(p, N) memset(p, 0, N)
#define stricmp strcasecmp
#define strnicmp strncasecmp

typedef uint32_t COLORREF;
typedef int32_t DWORD;

int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen,
        char *outbuf, size_t outlen);

uint32_t GetTickCount();
