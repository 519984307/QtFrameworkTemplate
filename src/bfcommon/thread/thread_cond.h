#ifndef thread_cond_h__
#define thread_cond_h__

#ifdef __cplusplus
extern "C" {
#endif

	typedef void* pthreadx_mutex_t;
	pthreadx_mutex_t pthreadx_mutex_init();
	void pthreadx_mutex_lock(pthreadx_mutex_t mutex);
	void pthreadx_mutex_unlock(pthreadx_mutex_t mutex);
	void pthreadx_mutex_destroy(pthreadx_mutex_t mutex);

	typedef void* pthreadx_cond_t;
	pthreadx_cond_t pthreadx_cond_init();
	int pthreadx_cond_wait(pthreadx_cond_t cond);
	void pthreadx_cond_signal(pthreadx_cond_t cond, unsigned char bReset);
	void pthreadx_cond_destroy(pthreadx_cond_t cond);

	typedef struct __pthreadx_t * pthreadx_t;
	pthreadx_t pthreadx_create(unsigned (__stdcall *initialcode)(void*), void* arg);
	unsigned int pthreadx_self();
	void pthreadx_exit(unsigned int code);
	void pthreadx_destroy(pthreadx_t pthreadx);
	void pthreadx_sleep(unsigned int msTime);

#ifdef __cplusplus
}
#endif

#endif
