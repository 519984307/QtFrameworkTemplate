#ifndef __AUNTEC_BASE_TYPES_H
#define __AUNTEC_BASE_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "auntec_base_config.h"

#ifdef __cplusplus
extern "C" {
#endif

// thiscall
#ifndef THISCALL
#	ifdef _MSC_VER
#		define THISCALL __thiscall
#	elif defined(__GNUC__)
#		define THISCALL __attribute__((__thiscall))
#	else
#		define THISCALL
#	endif
#endif

// stdcall
#ifndef STDCALL
#	ifdef _MSC_VER
#		define STDCALL __stdcall
#	elif defined(__GNUC__)
#		define STDCALL __attribute__((__stdcall))
#	else
#		define STDCALL
#	endif
#endif

// ccall
#ifndef CCALL
#	ifdef _MSC_VER
#		define CCALL __cdecl
#	elif defined(__GNUC__)
#		define CCALL __attribute__((__cdecl))
#	else
#		define CCALL
#	endif
#endif

// callback
#ifndef CALLBACK
#	define CALLBACK STDCALL
#endif

// INLINE
#ifndef INLINE
#	define INLINE __inline
#endif

// export
#ifndef EXPORT
#	ifdef _MSC_VER
#		define EXPORT
#	elif defined(__GNUC__)
#		define EXPORT __attribute__((visibility("default")))
#	else
#		define EXPORT
#	endif
#endif

#if !CONFIG_HAVE_INTTYPES
typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed int int32_t;
typedef unsigned int uint32_t;

#ifdef _MSC_VER	
	typedef signed __int64 int64_t;
	typedef unsigned __int64 uint64_t;
#else
	typedef signed long long int64_t;
	typedef unsigned long long uint64_t;
#endif

#endif

// 表明参数是入口参数
#ifndef IN
#	define IN
#endif

// 表明参数是出口参数
#ifndef OUT
#	define OUT
#endif

// 表明这是一个会抛出异常的函数，为异常式编程
#ifndef MEXP
#	define MEXP
#endif

// 表明这是一个不抛出异常的函数，且支持漠野异常报告机制
#ifndef MAPI
#	define MAPI
#endif

// 说明这个接口方法或类是开发者(可能)需要使用的
#ifndef MDEV
#	define MDEV 
#endif

// 说明这个接口方法一定返回可用数据(一般是内部维护的数据)
#ifndef MRES
#	define MRES
#endif

// 最大字体名长度
#ifndef MAX_FONT_NAME
#	define MAX_FONT_NAME	64
#endif

// 最大路径长度
#ifndef MAX_PATH
#	define MAX_PATH 260
#endif

// Infinite timeout
#ifndef INFINITE
#	define INFINITE	0xFFFFFFFF
#endif

#ifndef FREE_INTERFACE
#	define FREE_INTERFACE(x) if(NULL != (x)){ (x)->Free(); (x) = NULL; }
#endif

#ifndef FREE_DLL_HANDLE
#	define FREE_DLL_HANDLE(x) if(NULL != (x)){ AuntecBased::auntec_free_dll((x)); (x) = NULL; }
#endif

#ifndef SAFE_FREE
#	define SAFE_FREE(x) if(NULL != (x)){ free((x)); (x) = NULL; }
#endif

#ifndef SAFE_DELETE
#	define SAFE_DELETE(x) if(NULL != (x)){ delete (x); (x) = NULL; }
#endif

#ifndef BAD_PARAM    
#	define BAD_PARAM(x) if(NULL == (x)){throw "bad param"; }
#endif

#ifndef CountOfArray
#	define CountOfArray(arr) (sizeof(arr)/sizeof(arr[0]))
#endif

#ifdef __cplusplus
}
#endif

#endif
