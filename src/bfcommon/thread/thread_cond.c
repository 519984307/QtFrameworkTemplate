#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#include <process.h>
#endif

#include "thread_cond.h"

struct __pthreadx_t{
	unsigned thread_id;
	void* thread_handle;
};

pthreadx_mutex_t pthreadx_mutex_init()
{
	CRITICAL_SECTION* section = NULL;
	__try{
		section = (CRITICAL_SECTION*)malloc(sizeof(CRITICAL_SECTION));
		if(NULL == section){
			return NULL;
		}
		InitializeCriticalSection(section);
		return section;
	}__except(EXCEPTION_CONTINUE_EXECUTION){}
	if(NULL != section){
		free(section);
	}
	return NULL;
}

void pthreadx_mutex_lock( pthreadx_t mutex )
{
	__try{
		if(NULL != mutex){
			EnterCriticalSection((CRITICAL_SECTION*)mutex);
		}
	}__except (EXCEPTION_CONTINUE_EXECUTION){}
}

void pthreadx_mutex_unlock( pthreadx_t mutex )
{
	__try{
		if(NULL != mutex){
			LeaveCriticalSection((CRITICAL_SECTION*)mutex);
		}
	}__except(EXCEPTION_CONTINUE_EXECUTION){}
}

void pthreadx_mutex_destroy( pthreadx_t mutex )
{
	__try{
		if(NULL != mutex){
			CRITICAL_SECTION* p = (CRITICAL_SECTION*)mutex;
			DeleteCriticalSection(p);
			free(p);
		}
	}__except(EXCEPTION_CONTINUE_EXECUTION){}
}

pthreadx_cond_t pthreadx_cond_init()
{
	__try{
		return CreateEvent(NULL, FALSE, FALSE, NULL);
	}__except(EXCEPTION_CONTINUE_EXECUTION){}
	return NULL;
}

int pthreadx_cond_wait( pthreadx_cond_t cond )
{
	__try{
		if(NULL != cond){
			return WaitForSingleObject((HANDLE)cond, INFINITE);
		}
	}__except(EXCEPTION_CONTINUE_EXECUTION){}
	return -1;
}

void pthreadx_cond_signal( pthreadx_cond_t cond, unsigned char bReset )
{
	__try{
		if(NULL != cond){
			if(!bReset){
				SetEvent((HANDLE)cond);
			}else{
				ResetEvent((HANDLE)cond);
			}
		}
	}__except(EXCEPTION_CONTINUE_EXECUTION){}
}

void pthreadx_cond_destroy( pthreadx_cond_t cond )
{
	__try{
		if(NULL != cond){
			CloseHandle((HANDLE)cond);
		}
	}__except(EXCEPTION_CONTINUE_EXECUTION){}
}

pthreadx_t pthreadx_create( unsigned (__stdcall *initialcode)(void*), void* arg )
{
	pthreadx_t pthreadx = NULL;
	__try{
		pthreadx_t pthreadx = (pthreadx_t)malloc(sizeof(struct __pthreadx_t));
		if(NULL == pthreadx){
			return NULL;
		}
		memset(pthreadx, 0x00, sizeof(pthreadx_t));
		pthreadx->thread_handle = (void*)_beginthreadex(NULL, 0, initialcode, arg, 0, &(pthreadx->thread_id));
		if(NULL == pthreadx->thread_handle){
			free(pthreadx);
			return NULL;
		}
		return pthreadx;
	}__except(EXCEPTION_CONTINUE_EXECUTION){
		if(NULL != pthreadx){
			free(pthreadx);
		}
	}
	return NULL;
}

unsigned int pthreadx_self()
{
	return (unsigned int)GetCurrentThreadId();
}

void pthreadx_exit( unsigned int code )
{
	_endthreadex(code);
}

void pthreadx_destroy( pthreadx_t pthreadx )
{
	__try{
		if(NULL != pthreadx){
			WaitForSingleObject(pthreadx->thread_handle, INFINITE);
			CloseHandle((HANDLE)pthreadx->thread_handle);
			free(pthreadx);
		}
	}__except(EXCEPTION_CONTINUE_EXECUTION){}
}

void pthreadx_sleep(unsigned int msTime)
{
	Sleep(msTime);
}
