#define _LARGEFILE64_SOURCE
#include "sysutils.h"
#include <stdarg.h>
#include <string.h>
#include <iomanip>
#include <sys/stat.h>

#if defined(WIN32) 
    #include <Windows.h>
    #include <process.h>
    #include <mmsystem.h>
    #include <objbase.h>
#else
    #include <dlfcn.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <limits.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <sys/param.h>
    #include <sys/sysctl.h>
    #include <uuid/uuid.h>
	#include <unistd.h>
#endif

#ifdef __APPLE__
#include <mach/mach_time.h>
#include <mach-o/dyld.h> 
#endif

#include "CBaseException.h"
#include "res_keeper.h"

#ifdef _MSC_VER
#pragma warning( disable : 4996)
#endif

namespace MoyeaBased {

int strCaseInsensitiveCompare(const char* str1,const char* str2)
{
#ifdef WIN32
    return stricmp(str1,str2);
#else
    return strcasecmp(str1,str2);
#endif
}

int strNCaseInsensitiveCompare(const char* str1,const char* str2, uint32_t len)
{
#ifdef WIN32
    return strnicmp(str1,str2, len);
#else
    assert(false);//not yet implement
    return 0;
#endif
}

    

#ifdef WIN32

///convert wide chars to multibytes
static char* wide_to_mtbytes(int c, const wchar_t* pWideText)
{
    assert(pWideText);

    int size = WideCharToMultiByte(c, 0, (LPCWSTR)pWideText, -1, NULL, 0, NULL, NULL);
    if (size == 0) {
        assert(false);
        return NULL;
    }
    char* pText = new char[size+1];
    if (WideCharToMultiByte(c, 0, (LPCWSTR)pWideText, -1, pText, size, NULL, NULL) == 0) {
        delete []pText;
        assert(false);
        return NULL;
    }
    pText[size] = '\0';
    return pText;
}

///convert multibytes to wide chars
static wchar_t* mtbytes_to_wide(int c, const char* pText)
{
    assert(pText);

    wchar_t* pWideText=NULL;
    int size = MultiByteToWideChar(c, 0, pText, -1, NULL, 0);
    if (size == 0) {
        assert(false);
        return pWideText;
    } else {
        pWideText = new wchar_t[size+1];
        if (MultiByteToWideChar(c, 0, pText, -1, (LPWSTR)pWideText, size) == 0) {
            delete []pWideText;
            pWideText = NULL;
            assert(false);
            return pWideText;
        } else {
            pWideText[size] = 0;
            return pWideText;
        }
    }
}

string utf8_to_local(const char* pText)
{
    assert(pText);

    wstring ws = utf8_to_wide(pText);
    char* pANSI = wide_to_mtbytes(CP_ACP, ws.c_str());
    if (pANSI == NULL) {        
        assert(false);
        return "";
    }

    string r = pANSI;
    delete []pANSI;
    return r;    
}

string local_to_utf8(const char* pText)
{
    assert(pText);

    wchar_t* pWideText = mtbytes_to_wide(CP_ACP, pText);
    if (pWideText == NULL) {
        assert(false);
        return "";
    }
    char* pUTF8 = wide_to_mtbytes(CP_UTF8, pWideText);
    if (pUTF8 == NULL) {
        assert(false);
        delete []pWideText;
        return "";
    }
    string r = pUTF8;
    delete []pUTF8;
    delete []pWideText;
    return r;
}

wstring utf8_to_wide(const char* pText)
{
    assert(pText);
    wchar_t* pWide = mtbytes_to_wide(CP_UTF8, pText);
    assert(pWide);
    wstring s = (wchar_t*)pWide;
    delete []pWide;
    return s;
}


string wide_to_utf8(const wchar_t* pText)
{
    assert(pText);
    char* pUTF8 = wide_to_mtbytes(CP_UTF8, pText);
    if (pUTF8 == NULL) {
        assert(false);
        return "";
    } else {
        string r = pUTF8;
        delete []pUTF8;
        return r;
    }
}

string get_local_time(time_t iTime)
{
    struct tm* tmTime = NULL;
    tmTime = localtime(&iTime);
    CheckPointer(tmTime);
    char szCompleteTime[100] = {0};
    sprintf(szCompleteTime,
        "%d-%02d-%02d %02d:%02d:%02d",
        1900 + tmTime->tm_year,
        1 + tmTime->tm_mon,
        tmTime->tm_mday,
        tmTime->tm_hour,
        tmTime->tm_min,
        tmTime->tm_sec);
    if(strcmp(szCompleteTime, "") == 0)
    {
        throw CBaseException(errUnexpected, "Get time failed", __LINE__, __FILE__);
    }
    std::string szLocalTime = szCompleteTime;
    return szLocalTime;
}
#else
// length of a utf8 (multibyte)char
// follows signature of mblen( const char *, size_t count ) but always behaves as if count==1
// does not check validity of trailing bytes (u[1]&0xc0)==0x80
int u8len( const char *u, size_t count )
{
    if( 0==count ) return 0;

    if( NULL==u ) return 0;
    else if( 0==*u ) return 0;
    else if( !(*u&~0x7f) ) return 1;
    else if( (*u&0xe0)==0xc0 ) return 2;
    else if( (*u&0xf0)==0xe0 ) return 3;
    else if( (*u&0xf8)==0xf0 ) return 4;
    else /* error */ return -1;
}

// convert utf8 (multibyte)char to wchar_t
// follows signature of mbtowc( wchar_t *, const char *, size_t count ) but always behaves as if count==1
int u8towc( wchar_t *w, const char *u, size_t count )
{
    /* assert */ if( NULL==w ) return -1;

    int len=u8len( u,1 );

    if( len<1 ) return len;
    else if( 1==len ) { w[0]=u[0]&0x7f; return len; }
    else if( 2==len ) { if( (u[1]&0xc0)!=0x80 ) /* error */ return -1;
    w[0]=((u[0]&0x1f)<<6)|(u[1]&0x3f);
    return 2; }
    else if( 3==len ) { if( (u[1]&0xc0)!=0x80 ) /* error */ return -1;
    if( (u[2]&0xc0)!=0x80 ) /* error */ return -1;
    w[0]=((u[0]&0x0f)<<12)|((u[1]&0x3f)<<6)|(u[2]&0x3f);
    return 3; }
    else if( 4==len ) { if( (u[1]&0xc0)!=0x80 ) /* error */ return -1;
    if( (u[2]&0xc0)!=0x80 ) /* error */ return -1;
    if( (u[3]&0xc0)!=0x80 ) /* error */ return -1;
    w[0]=((u[0]&0x07)<<18)|((u[1]&0x3f)<<12)|((u[2]&0x3f)<<6)|(u[3]&0x3f);
    return 4; }
    else /* error */ return -1;
}

// number of wchar_t required to represent a utf8 string
// follows signature of mbstowcs( NULL, char*, )
int u8swcslen( const char* pu )
{
    int len=0;
    char c;

    while( (c = *pu) )
    {
        if( !(c&0x80) ) { len++; pu+=1; }
        else if( (c&0xe0)==0xc0 ) { len++; pu+=2; }
        else if( (c&0xf0)==0xe0 ) { len++; pu+=3; }
        else if( (c&0xf8)==0xf0 ) { len++; pu+=4; }
        else /* error: add width of single byte character entity &#xFF; */ { len+=6; pu+=1; }
    }
    return len;
}

// convert a utf8 string to a wchar_t string
// follows signature of size_t mbstowcs( wchar_t *, const char *, size_t count )
size_t u8stowcs( wchar_t *pw, const char *pu, size_t count )
{
    size_t clen=0;

    if( NULL==pw ) return u8swcslen( pu );

    while( *pu && clen<count )
    {
        int ulen=u8towc( &pw[clen], pu, 1 );
        if( ulen<0 ) return (size_t)-1;
        else { clen++; pu+=ulen; }
    }
    if( '\0'==*pu && clen<count) pw[clen++]=L'\0';
    return clen;
}

// convert a wchar_t to a utf8 (multibyte)char
// follows signature of int wctomb( char *m, wchar_t w )
// requires m to point to a buffer of length 4 or more
int wctou8( char *m, wchar_t w )
{
    /* Unicode Table 3-5. UTF-8 Bit Distribution
    Unicode                     1st Byte 2nd Byte 3rd Byte 4th Byte
    00000000 0xxxxxxx           0xxxxxxx
    00000yyy yyxxxxxx           110yyyyy 10xxxxxx
    zzzzyyyy yyxxxxxx           1110zzzz 10yyyyyy 10xxxxxx
    000uuuuu zzzzyyyy yyxxxxxx  11110uuu 10uuzzzz 10yyyyyy 10xxxxxx
    */

    if( !(w&~0x7f) ) { m[0]=w&0x7f;
    m[1]='\0';
    return 1; }
    else if( !(w&~0x7ff) ) { m[0]=((w>>6)&0x1f)|0xc0;
    m[1]=(w&0x3f)|0x80;
    m[2]='\0';
    return 2; }
    else if( !(w&~0xffff) ) { m[0]=((w>>12)&0x0f)|0xe0;
    m[1]=((w>>6)&0x3f)|0x80;
    m[2]=(w&0x3f)|0x80;
    m[3]='\0';
    return 3; }
    else if( !(w&~0x1fffff) ) { m[0]=((w>>18)&0x07)|0xf0;
    m[1]=((w>>12)&0x3f)|0x80;
    m[2]=((w>>6)&0x3f)|0x80;
    m[3]=(w&0x3f)|0x80;
    m[4]='\0';
    return 4; }
    else return -1;
}
// number of char required to represent a wchar_t string in utf8
// follows signature of wcslen( wchar_t* ) or wcstombs( NULL, wchar_t*, )
int wcsu8slen( const wchar_t *pw )
{
    int len=0;
    wchar_t w;

    while( (w = *pw++) )
    {
        if( !(w&~0x7f) ) len+=1;
        else if( !(w&~0x7ff) ) len+=2;
        else if( !(w&~0xffff) ) len+=3;
        else if( !(w&~0x1fffff) ) len+=4;
        else /* error: add width of null character entity &#x00; */ len+=6;
    }
    return len;
}
// number of char required to represent a single wchar_t in utf8
// follows signature of mblen( const wchar_t )
int wcu8len( const wchar_t w )
{
    if( !(w&~0x7f) ) return 1;
    if( !(w&~0x7ff) ) return 2;
    if( !(w&~0xffff) ) return 3;
    if( !(w&~0x1fffff) ) return 4;
    return -1; /* error */
}
// convert a wchar_t string to utf8 string
// follows signature of size_t wcstombs( char *u, const wchar_t *w, size_t count )
size_t wcstou8s( char *pu, const wchar_t *pw, size_t count )
{
    int len=wcsu8slen( pw );

    if( NULL==pu ) return (size_t)len;

    size_t clen=0;
    wchar_t w;
    while( (w = *pw++) )
    {
        int ulen=wcu8len(w);

        if( ulen>=0 )
        {
            if( (clen+wcu8len(w))<=count ) { clen+=wctou8( pu, w ); pu+=ulen; }
            else break;
        }
        else
        {
            // untranslatable character so insert null character entity &#x00;
            if( (clen+6)<=count )
            {
                *pu++='&'; *pu++='#'; *pu++='x';
                *pu++='0'; *pu++='0';
                *pu++=';';
            }
            else break;
        }
    }

    return (size_t)clen;
}

wstring utf8_to_wide(const char* pText)
{
    uint32_t buf_size = u8stowcs(NULL, pText, 0);
    wchar_t *wchar_buf = new wchar_t[buf_size + 1];
    u8stowcs(wchar_buf, pText, buf_size);
    wchar_buf[buf_size] = '\0';
    wstring ret = wchar_buf;
    delete []wchar_buf;
    return ret;
}

string wide_to_utf8(const wchar_t* pText)
{
    uint32_t size = wcstou8s(NULL, pText, 0);
    char *buf = new char[size + 1];
    wcstou8s(buf, pText, size);
    buf[size] = '\0';
    string ret = buf;
    delete []buf;
    return ret;    
}
#endif

uint32_t get_system_time()
{
#ifdef WIN32
    return timeGetTime();
#else
    /*
    //FIXME 是否可用
    struct tms t;
    return times(&t);
    */
    return 0;
#endif
}

#if CONFIG_LOCAL_IS_UTF8
string local_to_utf8(const char* pText)
{
    assert(pText);
    return pText;
}

string utf8_to_local(const char* pText)
{
    assert(pText);
    return pText;
}
#endif
//////////////////////////////////////////////////////////////////////////

#if !defined(NDEBUG) 

void debug_print(const char *szMsg, ...)
{
    va_list arglist;
    char buffer[256];

    va_start(arglist, szMsg);
    vsnprintf(buffer, 256, szMsg, arglist);
    va_end(arglist);

#ifdef WIN32
    OutputDebugStringA(buffer);
    OutputDebugStringA("\n");
#else
    fprintf(stderr, "%s\n", buffer);
#endif
}
    
#endif

//////////////////////////////////////////////////////////////////////////
//Exception

string GetLastMoyeaExpAsText()
{
    string r;
    if (HasExp()) {
        int line = 0;
        string filename = GetMoyeaException()->GetExceptionSource(&line);
        r = "[!!! Exception Code: ";
        char buf[64];
        sprintf(buf, "%d", ExpCode());
        r += buf;
        r += "\n";
        r += "Msg: ";
        r += ExpMessage();
        r += "\n";
        r += "File: ";
        r += filename;
        r += "\n";
        r += "Line: ";
        sprintf(buf, "%d", line);
        r += buf;
        r += " !!!]";
    }
    return r;
}

string FormatMoyeaExp(const CBaseException & exp, string formatStr)
{
    string r;
    int32_t line = 0;
    string path = exp.GetExceptionSource(&line);
    path = extract_file_name(path);
    r = Format(formatStr, STR(path), line, exp.GetExceptionMsg());
    return r;
}

//////////////////////////////////////////////////////////////////////////

#ifdef WIN32

CXMutex::CXMutex()
{
    m_hMutex = CreateMutex(NULL, FALSE, NULL);
}

bool CXMutex::Lock(uint32_t dwTimeoutMilliseconds /* = INFINITE */)
{
    if (WaitForSingleObject(m_hMutex, dwTimeoutMilliseconds) == WAIT_OBJECT_0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CXMutex::Unlock()
{
    return ReleaseMutex(m_hMutex) != 0;
}

CXMutex::~CXMutex()
{
    CloseHandle(m_hMutex);
}

#else

CXMutex::CXMutex()
{
    memset((void*)&m_hMutex, 0, sizeof(m_hMutex));
    if (pthread_mutexattr_init(&m_Attr) != 0) {
        assert(false);
        ThrowExpWithErrno(errUnexpected, "pthread_mutexattr_init: ");
    }
    if (pthread_mutexattr_settype(&m_Attr, PTHREAD_MUTEX_RECURSIVE) != 0) {
        pthread_mutexattr_destroy(&m_Attr);
        assert(false);
        ThrowExpWithErrno(errUnexpected, "pthread_mutexattr_settype: ");
    }
    if (pthread_mutex_init(&m_hMutex, &m_Attr) != 0) {
        pthread_mutexattr_destroy(&m_Attr);
        assert(false);
        ThrowExpWithErrno(errUnexpected, "pthread_mutex_init: ");
    }
}

bool CXMutex::Lock(uint32_t dwTimeoutMilliseconds /* = INFINITE */)
{    
    int err;
    if (dwTimeoutMilliseconds == INFINITE) {
        err = pthread_mutex_lock(&m_hMutex);
        if(err == 0)
            return true;
        else {
            assert(err != EINVAL);
            debug_print("pthread_mutex_lock failed: %d\n", err);
            assert(false);
            return false;
        }
    } else {
        uint32_t ta = 0;
        while(ta <= dwTimeoutMilliseconds) {
            err = pthread_mutex_trylock(&m_hMutex);
            if (err == 0) {
               return true;
            } else {
                assert(err == EBUSY);
            }
            usleep(10000);
            ta += 10;
        }
        return false;
    }
}

bool CXMutex::Unlock()
{
    if(pthread_mutex_unlock(&m_hMutex) == 0)
        return true;
    else {
        assert(false);
        return false;
    }
}

CXMutex::~CXMutex()
{
    pthread_mutexattr_destroy(&m_Attr);
    pthread_mutex_destroy(&m_hMutex);
}

#endif

//////////////////////////////////////////////////////////////////////////
//CXEvent
CXEvent::CXEvent(bool bAutoReset, bool bInitialState)
{
#ifdef WIN32
    m_hEvent = CreateEvent(NULL, !bAutoReset, bInitialState, NULL);
    if (m_hEvent == NULL) {
        ThrowExpWithWin32Error(errUnexpected, errmCantCreateEvent);
    }
#else
    m_bState = bInitialState;
    if (pthread_mutex_init(&m_mutex, 0) != 0) {
        ThrowExpWithErrno(errUnexpected, "pthread_mutex_init: ");
    }
    if (pthread_cond_init(&m_cond, 0) != 0) {
        pthread_mutex_destroy(&m_mutex);
        ThrowExpWithErrno(errUnexpected, "pthread_cond_init: ");
    }
#endif
}

CXEvent::~CXEvent()
{
#ifdef WIN32
    CloseHandle(m_hEvent);
    m_hEvent = NULL;
#else
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);
#endif
}

void CXEvent::Set()
{
#ifdef WIN32
    SetEvent(m_hEvent);
#else
    pthread_mutex_lock(&m_mutex);
    m_bState = true;
    pthread_cond_broadcast(&m_cond);
    pthread_mutex_unlock(&m_mutex);
#endif
}

void CXEvent::Reset()
{
#ifdef WIN32
    ResetEvent(m_hEvent);
#else
    pthread_mutex_lock(&m_mutex);
    m_bState = false;
    pthread_mutex_unlock(&m_mutex);
#endif
}

bool CXEvent::Wait(uint32_t msTimeout)
{
#ifdef WIN32
    return WaitForSingleObject(m_hEvent, msTimeout) ==  WAIT_OBJECT_0;
#else
    bool b = true;
    pthread_mutex_lock(&m_mutex);
    if (!m_bState) {
        if (msTimeout == INFINITE) {
            pthread_cond_wait(&m_cond, &m_mutex);            
        } else {
            struct timespec t;
            t.tv_sec = msTimeout / 1000;
            t.tv_nsec = ((long)(msTimeout % 1000)) *  1000000L;
            if (pthread_cond_timedwait(&m_cond, &m_mutex, &t) == ETIMEDOUT) {
                b = false;
            }
        }
    }
    if (b && m_bAutoReset) {
        m_bState = false;
    }
    if (b) {
        pthread_mutex_unlock(&m_mutex);
    }
    return b;
#endif
}

//////////////////////////////////////////////////////////////////////////

#ifdef WIN32

int LockInc(volatile int* pInt)
{
    return (int)InterlockedIncrement((volatile long*)pInt);
}

int LockDec(volatile int* pInt)
{
    return (int)InterlockedDecrement((volatile long*)pInt);
}

int LockRead(volatile int* pInt)
{
    return (int)InterlockedExchangeAdd((volatile long*)pInt, 0);
}

int LockWrite(volatile int* pInt, int v)
{
    InterlockedExchange((volatile long*)pInt, (long)v);
    return v;
}
#endif

//////////////////////////////////////////////////////////////////////////
// critical section
//////////////////////////////////////////////////////////////////////////

#ifdef WIN32
void* init_critical(void)
{
    CRITICAL_SECTION* p = new CRITICAL_SECTION();
#ifdef _MSC_VER
    __try {
        InitializeCriticalSection(p);
    } __except(EXCEPTION_CONTINUE_EXECUTION)
    {
        assert(p);
        delete p;
        ThrowUnexpected();
    }
#else
    InitializeCriticalSection(p);
#endif
    return p;
}

void delete_critical(void* pCritical)
{
    CheckPointer(pCritical);
    CRITICAL_SECTION* p = (CRITICAL_SECTION*)pCritical;
    DeleteCriticalSection(p);
    delete p;
}

void enter_critical(void* pCritical)
{
    CheckPointer(pCritical);
#ifdef _MSC_VER
    __try {
        EnterCriticalSection((CRITICAL_SECTION*)pCritical);
    } __except (EXCEPTION_CONTINUE_EXECUTION) {
        ThrowUnexpected();
    }
#else
    EnterCriticalSection((CRITICAL_SECTION*)pCritical);
#endif
}

void leave_critical(void* pCritical)
{
    CheckPointer(pCritical);
#ifdef _MSC_VER
    __try {
        LeaveCriticalSection((CRITICAL_SECTION*)pCritical);
    } __except(EXCEPTION_CONTINUE_EXECUTION) {
        ThrowUnexpected();
    }
#else
    LeaveCriticalSection((CRITICAL_SECTION*)pCritical);
#endif
}

#else

void* init_critical(void)
{
    return new CXMutex();
}

void delete_critical(void* pCritical)
{
    CheckPointer(pCritical);
    CXMutex* p = (CXMutex*)pCritical;
    delete p;
}

void enter_critical(void* pCritical)
{
    CheckPointer(pCritical);
    CXMutex* p = (CXMutex*)pCritical;
    if (!p->Lock(INFINITE)) {
       assert(false);
       ThrowUnexpected();
    }
}

void leave_critical(void* pCritical)
{
    CheckPointer(pCritical);
    CXMutex* p = (CXMutex*)pCritical;
    if (!p->Unlock()) {
       assert(false);
    }
}

#endif

//////////////////////////////////////////////////////////////////////////
// Make full dir
//////////////////////////////////////////////////////////////////////////

void make_dir(const char* szDirName)
{
    CheckPointer(szDirName);
    vector<string> parts = StrSplit(szDirName, "\\/");
    size_t i=0;
    string err_str = "Can't create directory, DirName = ";
    err_str += szDirName;
#ifdef  WIN32
    wstring path;
    if (*szDirName=='/' || *szDirName=='\\') {
        path = L"/";
        i=1;
    }    
    for(; i<parts.size(); ++i) {
        if (parts[i].empty()) {
            continue;
        }
        path += utf8_to_wide(parts[i].c_str());
        path += L"/";        
        if (!CreateDirectoryW(path.c_str(), NULL)) {            
            DWORD err=GetLastError();
            if (err == ERROR_PATH_NOT_FOUND || err == ERROR_INVALID_NAME) {  //非法路径
                ThrowExp(errUnexpected, err_str.c_str());
            }
            if (parts[i][1] == ':') { //磁盘驱动器?
                continue;
            }
            
        }
    }
    if (!dir_exists(szDirName)) {
        ThrowExp(errUnexpected, err_str.c_str());
    }
#else    
    string path;
    if (*szDirName=='/' || *szDirName=='\\') {
        path = "/";
    }
    for(; i<parts.size(); ++i) {
        if (parts[i].empty()) {
            continue;
        }
        path += utf8_to_local(parts[i].c_str());
        path += "/";
        if (mkdir(path.c_str(), 0777) == -1) {
            if (errno != EEXIST) {
                ThrowExp(errUnexpected, err_str.c_str());
            }
            struct stat info;
            if (stat(path.c_str(), &info) != 0) {
                ThrowExp(errUnexpected, err_str.c_str());
            }
            if (!S_ISDIR(info.st_mode)) {
                ThrowExp(errUnexpected, err_str.c_str());
            }
        }
    }
#endif
}


void delete_dir( const char* path )
{
    find_data* findHandle = NULL;
    if(path == NULL || !strcmp(path, "")){
        return;
    }
    try{
        try{
            findHandle = find_first(path, "*");
        }catch(...){}

        if(NULL == findHandle){
            if(dir_exists(path)){
                goto ret_dir;
            }else if(file_exists(path)){
                file_delete(string(path));
                return;
            }
            return;
        }

        while(findHandle){
            string filePath = find_get_path(findHandle);
            if(!find_is_folder(findHandle)){
                file_delete(filePath);
            }else{
                delete_dir(filePath.c_str());
            }
            if(!find_next(findHandle)){
                break;
            }
        }

ret_dir:
        if(findHandle){
            find_close(findHandle);
        }
#ifdef WIN32
        wstring wPath = utf8_to_wide(path);
        if(!RemoveDirectoryW(wPath.c_str())){
            DWORD ret = GetLastError();
            ThrowMKExp(errUnexpected, "War: Remove %s folder is failed, Win32 err code: %d", path, ret);
        }
#else
        if(rmdir(path)){
            ThrowMKExp(errUnexpected, "War: Remove %s folder is failed", path);
        }
#endif
        return;
    }catch(...){}
}

//////////////////////////////////////////////////////////////////////////
// find folder utilities
//////////////////////////////////////////////////////////////////////////
#ifdef WIN32
struct find_data
{
    WIN32_FIND_DATAW data;
    string path;
    HANDLE find_hd;

    find_data()
    {
        find_hd = INVALID_HANDLE_VALUE;
    }
    ~find_data()
    {
        if (find_hd != INVALID_HANDLE_VALUE) {
            FindClose(find_hd);
            find_hd = INVALID_HANDLE_VALUE;
        }
    }
};


#else

struct find_data
{
    struct dirent * data;
    string path;
    DIR* find_hd;
    string pattern;
    find_data()
    {
        find_hd = NULL;
    }
    ~find_data()
    {
        if (find_hd != NULL) {
            closedir(find_hd);
            find_hd = NULL;
        }
    }
};

#endif



find_data* find_first(const char* path, const char* pattern)
{    
    if (path == NULL || pattern == NULL) {
        assert(false);
        ThrowExp(errBadPointer, "File path or pattern can't not be null");
    }
    
    find_data* pData = new find_data();
    ObjectHandleKeeper<find_data*> kFindData(pData);

    string full_path = expand_path(path);
    full_path = include_path_backslash(full_path.c_str());

    pData->path = full_path;

    bool bOK = true;
    int i;    

    string err_str = "No file can be found, path = ";
    err_str += pData->path;
    err_str += pattern;
#ifdef WIN32
    wstring find_path = utf8_to_wide(pData->path.c_str()) + utf8_to_wide(pattern);

    pData->find_hd = FindFirstFileW(find_path.c_str(), &pData->data);
    if (pData->find_hd == INVALID_HANDLE_VALUE) {
        
        ThrowExp(errNotExists, err_str.c_str());
    } 
    for(i=0; i<2; ++i) { //jump the two special file
        wstring name = pData->data.cFileName;
        if (name == L"." || name == L"..") {
            if (!find_next(pData)) {
                bOK = false;
                break;
            }
        } else break;
    }    
#else
    pData->pattern = pattern;
    string find_path = utf8_to_local(full_path.c_str());
    DIR* dir = opendir(find_path.c_str());
    if (dir == NULL) {
        ThrowExpWithErrno(errUnexpected, err_str.c_str());
    }
    pData->data = NULL;
    pData->find_hd = dir;
    if (!find_next(pData)) { //find the first file
        ThrowExpWithErrno(errUnexpected, err_str.c_str());
    }
    for(i=0; i<2; ++i) { //jump the two special file
        string name = pData->data->d_name;
        if (name == "." || name == "..") {
            if (!find_next(pData)) {
                bOK = false;
                break;
            }
        } else break;
    }    
#endif    
    if (bOK) {
        return kFindData.Detach();
    } else {
        ThrowExp(errNotExists, err_str.c_str());
    }
}

bool find_next(find_data* pFindData)
{
    find_data* pData = (find_data*)pFindData;
    try {
        CheckPointer(pData);
#ifdef WIN32
        if (FindNextFileW(pData->find_hd, &pData->data)) {
            return true;
        } else {
            if (GetLastError() == ERROR_NO_MORE_FILES) {
                ThrowExpWithWin32Error(errNoMore, "find_next error");
            } else {
                ThrowExpWithWin32Error(errUnexpected, "find_next error");
            }
        }
#else
        do {
            pData->data = readdir(pData->find_hd);
            if (pData->data == NULL) {
                ThrowExpWithErrno(errUnexpected, "find_next error");
            }
            if (!StrMatch(pData->data->d_name, pData->pattern.c_str())) { //if it's match the pattern
                continue;
            } else break;
        } while (true);
        return true;
#endif        
    } CatchMoyeaExp();
    return false;
}

bool find_is_folder(find_data* pFindData)
{
    find_data* pData = (find_data*)pFindData;
#ifdef WIN32
    if (pData->data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        return true;
    } else return false;
#else
    return (pData->data->d_type & DT_DIR);
#endif
}

void find_close(find_data* pFindData)
{
    if (pFindData) {
        delete pFindData;
    }
}

string find_get_path(find_data* pFindData)
{
    find_data* pData = (find_data*)pFindData;
#ifdef WIN32
    string name = wide_to_utf8((wchar_t*)pData->data.cFileName);
#else
    string name = local_to_utf8(pData->data->d_name);
#endif
        
    return pData->path + name;
}


bool file_exists(const char* file)
{
    if(file == NULL || !strcmp(file, "")){
        return false;
    }

    int iresult;
#ifdef WIN32
    struct _stat64 buf;
    wstring szPath = utf8_to_wide(file);
    iresult = _wstat64(szPath.c_str(), &buf);
#else
    struct stat buf;
    string szPath = utf8_to_local(file);
    iresult = stat(szPath.c_str(),&buf);
#endif

    if(iresult != 0){
        return false;
    }
#ifdef WIN32
    return buf.st_mode&S_IFDIR?false:true;
#else
    return S_ISDIR(buf.st_mode)?false:true;
#endif
}

bool dir_exists(const char* dir)
{
    if(dir == NULL || !strcmp(dir, "")){
        return false;
    }
    try {
        string err_str = "";
#if defined(WIN32)
        wstring path = utf8_to_wide(dir);
        wchar_t ch = path[path.length()-1];
        if (ch != '/' && ch != '\\') {
            path += L"/";
        }
        ch = path[path.length()-1];
        if (ch == '/' || ch == '\\') {
            path += L".";
        }
        HANDLE hd = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hd == INVALID_HANDLE_VALUE) {
            if (GetLastError() == ERROR_PATH_NOT_FOUND || GetLastError() == ERROR_INVALID_NAME) {
                return false;
            }
        } else CloseHandle(hd);
        WIN32_FILE_ATTRIBUTE_DATA ad;
        if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &ad)) {
            return false;
        }
        if ((ad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
            return false;
        }
        return true;
#elif defined(__APPLE__)
        struct stat info;
        string path = utf8_to_local(dir);
        if (stat(path.c_str(), &info) != 0) {
            err_str = "dir_exist: Can't stat the directory, dir = ";
            err_str += dir;
            ThrowExp(errUnexpected, err_str.c_str());
        }
        if (!S_ISDIR(info.st_mode)) {
            err_str = "dir_exist: It's not a directory, dir = ";
            err_str += dir;
            ThrowExp(errUnexpected, err_str.c_str());
        }
        return true;
#endif
    } catch(...){}
    return false;
}

string expand_path(const char* path)
{
    string err_str = "";
#ifdef WIN32
    wchar_t* pName;
    wstring real_path = utf8_to_wide(path);

    uint32_t nLen = GetFullPathNameW(real_path.c_str(), 0, NULL, NULL);
    if (nLen == 0) {
        throw CBaseException(errUnexpected, "Can't expand path", __LINE__, __FILE__);
    }
    MallocAllocator ma;
    nLen = nLen * 2 + 2;
    ma.Realloc(nLen);

    nLen = GetFullPathNameW(real_path.c_str(), nLen/2, (wchar_t*)ma.GetHandle(), &pName);

    return wide_to_utf8((wchar_t*)ma.GetHandle());
#else
    char fullpath[PATH_MAX]={0};
    if (realpath(path, fullpath) == NULL) {
//#ifdef __linux__
        if (errno == ENOENT) { //HACK: linux will return NULL when file does not exist
            ;
        } else
//#endif
        {
        err_str = "Can't expand path, path = ";
        err_str += path;
        ThrowExp(errUnexpected, err_str.c_str());
        }
    } 
    string full = fullpath;
    if (RightStr(path, 1) == "/") { 
        full = include_path_backslash(full.c_str());
    }
    return full;
#endif
}

string include_path_backslash(const char* path)
{
#ifdef WIN32
    const char backslash = '\\';
    const char backslash_str[] = "\\";
#else
  const char backslash = '/';
  const char backslash_str[] = "/";
#endif
    assert(path);
    string r = path;
    uint32_t len = (uint32_t)r.length();
    if (len > 0) {
        if (r[len-1] == '/' || r[len-1] == '\\') {
            r[len-1] = backslash;
        } else {
            r += backslash_str;
        }
    } else {
        r += backslash_str;
    }
    return r;
}

string extract_file_name(const string& path)
{
    try{
        string local_name = utf8_to_local(path.c_str());
        string err_str = "Can't detect file name length, file name = ";
        err_str += local_name;
        
#ifdef WIN32
        wstring real_path = utf8_to_wide(path.c_str());
        uint32_t len = GetFullPathNameW(real_path.c_str(), 0, NULL, NULL);
        if (len == 0) {
            throw CBaseException(errUnexpected, err_str.c_str(), __LINE__, __FILE__);
        }
        MallocAllocator ma;
        len = len * 2 + 2;

        ma.Realloc(len);
        void* pBuf = ma.GetHandle();
        wchar_t* pName=NULL;
        if (GetFullPathNameW(real_path.c_str(), len/2, (wchar_t*)pBuf, &pName) == 0) {
            throw CBaseException(errUnexpected, err_str.c_str(), __LINE__, __FILE__);
        }
        if (pName == NULL) {
            return "";
        }
        return wide_to_utf8(pName);
#else
        string full = expand_path(path.c_str());
        int pos = StrRPos(full, INFINITE, "/");
        if (pos == -1) {
            return full;
        } else {
            return SubStr(full, pos+1, INFINITE);
        }
#endif
    }CatchAllAndCopy();
    return "";
}

string extract_file_ext(const string& path)
{
    string::size_type  pp = path.rfind('.');
    string::size_type  ps1 = path.rfind('/');
    string::size_type  ps2 = path.rfind('\\');
    
    if (ps1 != string::npos && ps2 != string::npos) {
        ps1 = max(ps1, ps2);
    } else if (ps1 == string::npos) {
        ps1 = ps2;
    }

    if (pp == string::npos || (ps1 != string::npos && pp < ps1))
    {
        //No extension
        return "";
    }
    else
    {
        return path.substr(pp, path.length() - pp);
    }
}

string extract_file_path(const string& path)
{
#ifdef WIN32
    wstring real_path = utf8_to_wide(path.c_str());
    uint32_t len = GetFullPathNameW(real_path.c_str(), 0, NULL, NULL);
    if (len == 0) {
        throw CBaseException(errUnexpected, "Can't detect file name length", __LINE__, __FILE__);
    }
    MallocAllocator ma;
    len = len * 2 + 2;

    ma.Malloc(len);
    void* pBuf = ma.GetHandle();
    wchar_t* pName=NULL;
    if (GetFullPathNameW(real_path.c_str(), len/2, (wchar_t*)pBuf, &pName) == 0) {
        throw CBaseException(errUnexpected, "Can't detect file name length", __LINE__, __FILE__);
    }
    if (pName != NULL) {
        *pName = 0;
    }
    string ret = wide_to_utf8((wchar_t*)pBuf);
    return ret;
#else
  string full = expand_path(path.c_str());
  int pos = StrRPos(full, INFINITE, "/");
  if (pos == -1) {
     return include_path_backslash(full.c_str());
  } else {
     return LeftStr(full, pos+1);
  }
#endif
}

string change_file_ext(const string& path, const string& ext)
{
    int pp = (int)path.rfind('.');
    int ps1 = (int)path.rfind('/');
    int ps2 = (int)path.rfind('\\');
    ps1 = max(ps1, ps2);
    if (pp <= ps1) { //No extension
        return string(path.c_str()) + ext;
    } else {
        string r = path;
        r[pp] = 0;
        return string(r.c_str()) + ext;
    }    
}

string&  path_connect(string &source_path, const char * sub_path, bool end_with_delimiter/* = false*/)
{
    source_path = include_path_backslash(source_path.c_str());
    source_path += sub_path;
    if (end_with_delimiter)
    {
        source_path = include_path_backslash(source_path.c_str());
    }
    
    return source_path;
}


int64_t get_file_size(const string& path )
{
    try{
#ifdef WIN32
        struct _stat64 buf;
        wstring szPath = utf8_to_wide(path.c_str());
        int iresult = _wstat64(szPath.c_str(),&buf);
#else
        struct stat buf;
        string szPath = utf8_to_local(path.c_str());
        int iresult = stat(szPath.c_str(),&buf);
#endif
        if(iresult == 0){
            return buf.st_size;
        }else{
            ThrowMKExp(errUnexpected,"get file=%s size failed", path.c_str());
        }
    }CatchAllAndCopy();
    return 0;
}


uint64_t get_folder_size( const string& dir )
{
    uint64_t dwSize = 0;
    try {
        if (dir == "") {
            ThrowExp(errBadPointer, "empty path");
        }
        string srcFilePath = include_path_backslash(dir.c_str());

        find_data* fd = NULL;
        try {
            fd = find_first(srcFilePath.c_str(),"*");
        }CatchAllAndCopy();
        if (fd == NULL) {
            ThrowExp(errNotExists, "No file can be found");
        }
        do{
            if (find_is_folder(fd)){
                dwSize += get_folder_size(find_get_path(fd));
            }else{
                dwSize += get_file_size(find_get_path(fd).c_str());
            }
        }while(find_next(fd));
        find_close(fd);
    }CatchAllAndCopy();
    return dwSize;
}

int file_read(file_handle_t handle, void * buffer, uint32_t Count)
{
    try {
        CheckPointer(buffer);
#ifdef WIN32
        uint32_t nReadCount = 0;
        if(Count == 0){
            return 0;
        }
        if(ReadFile(HANDLE(handle),buffer,Count,LPDWORD(&nReadCount),NULL) == 0)
        {
            DWORD dw = GetLastError();
            if (dw == ERROR_HANDLE_EOF) {
                ThrowExp(errEndOfStream, "End of file");
            } else {
                ThrowExpWithWin32Error(errIO, "file_read error");
            }
        }
        else
        {
            if (nReadCount == 0) {
                ThrowExp(errEndOfStream, "End of file");
            }
            return nReadCount;
        }
#else
        int err = read(handle, buffer, Count);
        if (err == 0) {
            ThrowExp(errEndOfStream, "End of file");
        } else if (err < -1) {
            ThrowExpWithErrno(errIO, "file_read error");
        } else return  err;
#endif
    } CatchAllAndCopy();
    return -1;
}

int file_write(file_handle_t handle, const void * buffer, uint32_t Count)
{
    try {
        CheckPointer(buffer);   
#ifdef WIN32
        uint32_t nWriteCount = 0;
        if(!WriteFile(HANDLE(handle),buffer,Count,LPDWORD(&nWriteCount),NULL))
        {
            ThrowExpWithWin32Error(errIO, "file_write error");
        }
        else
        {
            return (int)nWriteCount;
        }
#else
        int err;
        err = write(handle, buffer, Count);
        if (err == -1) {
            ThrowExpWithErrno(errIO, "file_write error");
        }
        return err;
#endif
    } CatchAllAndCopy();
    return -1;
}

bool file_set_current_end(file_handle_t handle)
{
    try {
#ifdef WIN32
        if(!SetEndOfFile(HANDLE(handle)))
        {
            ThrowExpWithWin32Error(errIO, "file_set_current_end");
        }
#else
        if (ftruncate(handle, file_seek(handle, 0, SEEK_CUR)) != 0) {
            ThrowExpWithErrno(errIO, "file_set_current_end");
        }
#endif
        else
        {
            return true;
        }
    } CatchAllAndCopy();
    return false;
}

int64_t file_seek(file_handle_t handle, int64_t nOffset, int nOrigin)
{
    try {
#ifdef WIN32
        LARGE_INTEGER li;
        li.QuadPart = nOffset;
        li.LowPart = SetFilePointer ((HANDLE)handle, li.LowPart, &li.HighPart, (DWORD)nOrigin);
        if (li.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
        {
            ThrowExpWithWin32Error(errIO, "file_seek error");
        }
        return li.QuadPart;
#else
    int64_t r =    lseek(handle, nOffset, nOrigin);
    if (r == -1) {
        ThrowExpWithErrno(errIO, "file_seek error");
    }
    return r;
#endif
    } CatchAllAndCopy();
    return -1;
}

void file_close(file_handle_t handle)
{
    try {
#ifdef WIN32
        if(!CloseHandle((HANDLE)handle))
        {
            assert(false); //Pass a bad handle to me ? You must check your code
            ThrowExpWithWin32Error(errIO, "file_close error");
        } 
#else
        if(close(handle) != 0)
        {
            assert(false); //Pass a bad handle to me ? You must check your code
            ThrowExpWithErrno(errIO, "file_close error");
        } 
#endif
        else {
            ClearExp();
        }   
    } CatchAllAndCopy();
}

file_handle_t file_create(const string& fileName)
{  
    try {
        if (fileName.empty())
        {
            ThrowExp(errBadParam,"filename can't be empty");
        }
        //char err_msg[256] = {0};
        //string local_filename = utf8_to_local(fileName.c_str());
#ifdef WIN32
        HANDLE reHandel = CreateFileW(utf8_to_wide(fileName.c_str()).c_str(), GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
        if (reHandel == INVALID_HANDLE_VALUE)
        {
            string err_msg = "file_create error, filename is ";
            err_msg += utf8_to_local(fileName.c_str());
            //sprintf(err_msg, "file_create error, filename is %s", local_filename.c_str());
            ThrowExpWithWin32Error(errIO, err_msg.c_str());
        }
        else
        {
            return ClearExpAndEval((file_handle_t)reHandel);
        }
#else
    int access = O_TRUNC | O_CREAT | O_RDWR;
    #ifdef O_BINARY
        access |= O_BINARY;
    #endif
    int fd = open(fileName.c_str(), access, 0666);
    if (fd == -1) {
        string err_msg = "file_create error, filename is ";
        err_msg += fileName;
        //sprintf(err_msg, "file_create error, filename is %s", local_filename.c_str());
        ThrowExpWithErrno(errIO, err_msg.c_str());
    }
    return fd;
#endif
    } CatchAllAndCopy();
    return (file_handle_t)-1;
}

file_handle_t file_open(const string& fileName, uint16_t mode)
{
    try {
        string err_str = "";
        if (mode == fmCreate) {
            return file_create(fileName);
        }
#ifdef WIN32
        const uint32_t AccessMode[3] = {
            GENERIC_READ,
            GENERIC_WRITE,
            GENERIC_READ | GENERIC_WRITE
        };
        const uint32_t ShareMode[5]  = {
            0,
            0,
            FILE_SHARE_READ,
            FILE_SHARE_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE
        };

        HANDLE Result = NULL;
        if (((mode & 3) <= fmOpenReadWrite) && ((mode & 0xF0) <= fmShareDenyNone) )
        {
            wstring localFileName = utf8_to_wide(fileName.c_str());
            Result = CreateFileW(localFileName.c_str(), AccessMode[mode & 3],
                ShareMode[(mode & 0xF0) >> 4], NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, 0);
        } else {
            err_str = "file_open error: bad access mode, filename = ";
            err_str += utf8_to_local(fileName.c_str());
            ThrowExp(errBadParam, err_str.c_str());
        }
        if (INVALID_HANDLE_VALUE == Result)
        {
            err_str = "file_open error, filename = ";
            err_str += utf8_to_local(fileName.c_str());
            ThrowExpWithWin32Error(errIO, err_str.c_str());
        }
        else
        {
            return ClearExpAndEval((file_handle_t)Result);
        }
#else
        int flag = O_EXCL;
        const int access_mode[3] = {
            O_RDONLY,
            O_WRONLY,
            O_RDWR
        };
        if (((mode & 3) <= fmOpenReadWrite)) {
            flag |= access_mode[mode&3];
        } else {
            err_str = "file_open error: bad access mode, filename = ";
            err_str += fileName.c_str();
            ThrowExp(errBadParam, err_str.c_str());
        }
        int fd = open(fileName.c_str(), flag, 0666);
        if (fd == -1)
        {
            flag = access_mode[mode&3];
            fd = open(fileName.c_str(), flag, 0666);
            if (-1 == fd)
            {
                err_str = "file_open error, filename = ";
                err_str += fileName.c_str();
                ThrowExpWithErrno(errIO, err_str.c_str());
            }
        }
        return ClearExpAndEval(fd);
#endif
    } CatchAllAndCopy();
    return (file_handle_t)-1;
}

bool file_delete(const string& fileName)
{
    try {
        string err_str = "file_delete error, filename = ";
#ifdef WIN32
        if(DeleteFileW(utf8_to_wide(fileName.c_str()).c_str()) == 0)
        {
            err_str += utf8_to_local(fileName.c_str());
            ThrowExpWithWin32Error(errIO, err_str.c_str());
        }
#else
        if (unlink(fileName.c_str()) != 0) {
            err_str += fileName;
            ThrowExpWithErrno(errIO, err_str.c_str());
    }
#endif
        return ClearExpAndEval(true);
    } CatchAllAndCopy();
    return false;
}

bool move_file(const string& src, const string& dest)
{
    try {
        string err_str = "move_file error, filename = ";
#ifdef WIN32
        wstring src_w = utf8_to_wide(src.c_str());
        wstring dest_w = utf8_to_wide(dest.c_str());
        if (!MoveFileW(src_w.c_str(), dest_w.c_str())) {
            err_str += utf8_to_local(src.c_str());
            ThrowExpWithWin32Error(errIO, err_str.c_str());
        } else return true;
#else
        if (rename(src.c_str(), dest.c_str()) != 0) {
            err_str += src;
            ThrowExpWithErrno(errIO, err_str.c_str());
        } else return true;
#endif
    } CatchAllAndCopy();
    return false;
}

//////////////////////////////////////////////////////////////////////////
bool set_environment_variable(const string& evName, const string& evValue)
{
    try {
#ifdef WIN32
        if (!SetEnvironmentVariableW(utf8_to_wide(evName.c_str()).c_str(), utf8_to_wide(evValue.c_str()).c_str())) {
            ThrowExpWithWin32Error(errUnexpected, "set_environment_variable error");
        }    
#else
        if (setenv(evName.c_str(), evValue.c_str(), 1) != 0) {
            ThrowExpWithErrno(errUnexpected, "set_environment_variable error");
        }
#endif
        return ClearExpAndEval(true);
    } CatchAllAndCopy();
    return false;
}

bool get_environment_variable(const string& evName, string &evValue)
{
    try {
        string err_str = "get_environment_variable error, name = ";
        err_str += evName;
#ifdef WIN32
        wstring LocalName = utf8_to_wide(evName.c_str());
        wstring LocalValue = utf8_to_wide(evValue.c_str());
        MallocAllocator ma;
        DWORD BufferSize = 0;     
        BufferSize = GetEnvironmentVariableW(LocalName.c_str(), NULL,BufferSize);
        if (BufferSize == 0) {
            ThrowExpWithWin32Error(errNotExists, err_str.c_str());
        }
        ma.Malloc(2*BufferSize);
        DWORD re = GetEnvironmentVariableW(LocalName.c_str(), (LPWSTR )(void*)ma,BufferSize);
        if(re == 0)
        {
            ThrowExpWithWin32Error(errUnexpected, err_str.c_str());
        }
        else
        {
            LocalValue.append((wchar_t*)(void*)ma, BufferSize - 1);
            evValue = wide_to_utf8(LocalValue.c_str());
            return (true);
        }
#else
        char* val = getenv(evName.c_str());
        if (val == NULL) {
            ThrowExpWithErrno(errNotExists, err_str.c_str());
        }
        evValue.clear();
        evValue.append(val);
        return (true);
#endif
    } catch(...){}
    return false;
}

bool delete_environment_variable(const string& name)
{
    try {
#ifdef WIN32    
        if (!SetEnvironmentVariableW(utf8_to_wide(name.c_str()).c_str(), NULL)) {
            ThrowExpWithWin32Error(errNotExists, "delete_environment_variable error");
        }
        return ClearExpAndEval(true);
#else
        #ifdef __APPLE__
            unsetenv(name.c_str());
        #else
        if (unsetenv(name.c_str()) != 0) {
            ThrowExpWithErrno(errNotExists, "delete_environment_variable error");
        }
        #endif
        return ClearExpAndEval(true);
#endif
    } CatchAllAndCopy();
    return false;
}

string get_home_path()
{
    string val;
#ifdef WIN32
    string drive;
    get_environment_variable("HOMEDRIVE", drive);
    get_environment_variable("HOMEPATH", val);    
    val = drive + val;
    if(val.empty())
    {
        get_environment_variable("userProfile", val);
    }
#else
    get_environment_variable("HOME", val);    
#endif
    return val;
}


#ifdef WIN32
bool GetCurrentModuleName(string &ModuleName, IN HANDLE DLLHandle/* = INVALID_HANDLE_VALUE*/)
{
    HMODULE DLLModule = (HMODULE)DLLHandle;
    if (DLLModule == INVALID_HANDLE_VALUE)
    {
        DLLModule = NULL;        
    }
    
    string cln = GetCommandLineA();
    DWORD BufferSize = MAX_PATH; 
    MallocAllocator ma;
    ma.Malloc(MAX_PATH);
    DWORD re = GetModuleFileNameA(DLLModule, (char *)(void*)ma, BufferSize);
    if(re == 0)//if err
    {
        try
        {
            DWORD errCode = GetLastError();
            string errMsg = "GetEnvironmentVariable fail,error code is ";
            errMsg += IntToStr(errCode);
            ThrowExp(errUnexpected,errMsg.c_str());
        }CatchAllAndCopy();
        return false;
    }
    else if(re > BufferSize)//if buffer is not enough
    {
        BufferSize = re;
        ma.Malloc(BufferSize);        
        re = GetModuleFileNameA(DLLModule, (char *)(void*)ma, BufferSize);
        if(re == 0)
        {
            try
            {
                DWORD errCode = GetLastError();
                string errMsg = "GetEnvironmentVariable fail,error code is ";
                errMsg += IntToStr(errCode);
                ThrowExp(errUnexpected,errMsg.c_str());
            }CatchAllAndCopy();
            return false;
        }
    }

    string temStr((char *)(void*)ma);
    ModuleName = local_to_utf8(temStr.c_str());
    ma.Detach();
    return true;
}
bool AddSelfPathToEnvironmentVariable()
{
    string ModuleName;
    if (!GetCurrentModuleName(ModuleName))
    {
        return false;
    }
    string ModulePath = extract_file_path(ModuleName);
    ModulePath.erase(ModulePath.begin() + ModulePath.length() - 1);

    string OldValue;
    get_environment_variable("Path",OldValue);

    string::size_type nPos = -1;
    //判断是否已经包含
    if (OldValue.find(ModulePath) != nPos)
    {
        return true;
    }
    else
    {
        OldValue += ";";
        OldValue += ModulePath;
        return set_environment_variable("Path", OldValue);
    }

    return true;
}



#endif

string GetUnicodeFileName(const string & SourceName)
{
    string szFullName = expand_path(SourceName.c_str());
    string szFileExt = extract_file_ext(SourceName);
    string szPathName = change_file_ext(szFullName, "");
    string szNewFileName;
    int i = 0;
    while (file_exists(szFullName.c_str())
        && i < 40000)
    {   
        szNewFileName = Format("%s_%d", szPathName.c_str(),i) ;
        szFullName = szNewFileName + szFileExt;
        i++;
    }
    ClearExp();
    return szFullName;
}

//////////////////////////////////////////////////////////////////////////
// Data type API
//////////////////////////////////////////////////////////////////////////
uint16_t MakeWord(uint8_t A,uint8_t B)
{
    return A | B << 8;
}

uint32_t MakeLong(uint16_t A, uint16_t B )
{
    return A | B << 16;
}

uint16_t HiWord(uint32_t L)
{
    return L >> 16;
}

uint8_t HiByte(uint16_t W)
{
    return W >> 8;
}

uint16_t LoWord(uint32_t L)
{
    return uint16_t(L);
}

uint8_t LowByte(uint16_t W)
{
    return uint8_t(W);
}

rect_t FillRect(int32_t Xmin, int32_t Ymin, int32_t Xmax, int32_t Ymax)
{
    rect_t Result = {(float)Xmin, (float)Ymin, (float)Xmax, (float)Ymax};
    return Result;
}

int ascii_to_integer( char *string )
{
    int value;

    value = 0;

    /*
    ** Convert digits of the string one by one.
    */
    while( *string >= '0' && *string <= '9' ){
        value *= 10;
        value += *string - '0';
        string++;
    }

    /*
    ** Error check: if we stopped because of a nondigit, set the
    ** result to zero.
    */
    if( *string != '\0' )
        value = 0;

    return value;
}
//////////////////////////////////////////////////////////////////////////
//Math
//////////////////////////////////////////////////////////////////////////
double DegToRad(const double Degrees)
{
    return Degrees *(PI / 180);
}

//////////////////////////////////////////////////////////////////////////
//QueryInArray
//////////////////////////////////////////////////////////////////////////
bool QueryInArray(uint32_t nQueryNumber,IN uint32_t *pArray, uint32_t nArrayLength)
{
    if (pArray == NULL)
    {
        assert(pArray != NULL);
        return false;
    }

    for (uint32_t i = 0; i < nArrayLength ; i++)
    {
        if(*(pArray + i) == nQueryNumber)
        {
            return true;
        }
    }
    return false;
}


#ifdef WIN32

#pragma comment(lib, "winmm.lib")
struct timer_struct 
{
    timer_proc_t onTimer;
    void* pData;
    DWORD nTimer;
};

static VOID CALLBACK TimerProc(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
    timer_struct * ts = (timer_struct*)dwUser;
    ts->onTimer(ts->pData);
}

void* install_timer(unsigned int ms, timer_proc_t onTimer, void* pData)
{
    timer_struct * ts = new timer_struct;
    ts->onTimer = onTimer;
    ts->pData = pData;    
    ts->nTimer = timeSetEvent(ms,1000, TimerProc, (DWORD_PTR)ts, TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
    if (ts->nTimer == 0) {
        delete ts;
        return NULL;
    } else {
        return ts;
    }
}

void uninstall_timer(void* pTimer)
{
    if (pTimer == NULL) return;
    timer_struct * ts = (timer_struct*)pTimer;
    timeKillEvent(ts->nTimer);

    delete ts;
}

#endif

////////////////////DLL///////////////////////////////////////////////////


/*!
加载DLL
*/
void* load_dll(const char* path)
{
    assert(path != NULL);
#ifdef WIN32
    wstring p = utf8_to_wide(path);
    void* hModule = LoadLibraryW((LPCWSTR)p.c_str());
    return hModule;
#else
    return dlopen(path, RTLD_LAZY);
#endif
}

/*!
获取函数地址
*/
void* get_proc_addr(void* hModule, const char* proc)
{
    assert(proc != NULL);
#ifdef WIN32
    return (void*)GetProcAddress((HMODULE)hModule, proc);
#else
    return (void*)dlsym(hModule, proc);
#endif
}

/*!
释放DLL
*/
void free_dll(void* hModule)
{
    assert(hModule != NULL);
#ifdef WIN32
    FreeLibrary((HMODULE)hModule);
#else
    dlclose(hModule);
#endif
}

/*!
@brief 设置DLL的加载路径
@param path 文件夹路径
*/
void dll_set_load_path(const string& path)
{
    string paths;
    vector<string> path_arr;

#ifdef WIN32
    const char* path_var_name = "PATH";
    const char* path_sep = ";";
#else
    const char* path_var_name = "LD_LIBRARY_PATH";
    const char* path_sep = ":";
#endif
    get_environment_variable(path_var_name, paths);
    path_arr = StrSplit(paths, path_sep);
    for(uint32_t i=0; i<path_arr.size(); ++i) {
        if (path_arr[i] == path) {
            return;
        }
    }
    paths += path_sep;
    paths += path;
    set_environment_variable(path_var_name, paths);
}

string get_executable_path()
{
#ifdef WIN32
   MallocAllocator buf;
   buf.Malloc(4096);
   DWORD size = GetModuleFileNameW(NULL, (LPWSTR)buf.GetHandle(), buf.Size()/2);
   if (size == 0) {
      return "";
   }   
   return wide_to_utf8((wchar_t*)buf.GetHandle());
#elif defined(__APPLE__)
   char buf[4*PATH_MAX]={0};
   typedef int (*NSGetExecutablePathProcPtr)(char *buf, size_t *bufsize);
   NSGetExecutablePathProcPtr NSGetExecutablePath = NULL;
   NSGetExecutablePath = (NSGetExecutablePathProcPtr) NSAddressOfSymbol(NSLookupAndBindSymbol("__NSGetExecutablePath"));
   if (NSGetExecutablePath != NULL)
   {
       size_t pathLength = 4*PATH_MAX;
       (*NSGetExecutablePath)(buf, &pathLength);
       buf[4*PATH_MAX-1] = 0;
   }
   return buf;
#else
    assert(false);
    return "";
#endif
}


//////////////////////////////////////////////////////////////////////////

// Moyea 线程基类

CMoyeaBasedThread::CMoyeaBasedThread()
{
    bool bSuspend = true;//make sure suspend the thread
    m_bThreadExists = true;
#ifdef WIN32
    uint32_t tid;
    uint32_t flag = 0;
    if (bSuspend) {
        flag = CREATE_SUSPENDED;
    }
    m_bSuspended = bSuspend;
    m_ThreadHandle = _beginthreadex(NULL, 0, ThreadProc, this, flag, &tid);
    if (m_ThreadHandle == NULL) {
        ThrowUnexpected();
    }
#else
    m_bSuspended = bSuspend;
    if (pthread_create(&m_ThreadHandle, NULL, ThreadProc, this) != 0) {
        ThrowUnexpected();
    }
#endif
}

CMoyeaBasedThread::~CMoyeaBasedThread()
{
#ifdef WIN32
    if (m_ThreadHandle != NULL) {
        if (m_bSuspended)
        {
            assert(m_ThreadHandle != NULL);
            ResumeThread((HANDLE)m_ThreadHandle);
        }
        Wait(INFINITE);
        CloseHandle((HANDLE)m_ThreadHandle);
        m_ThreadHandle = NULL;
    }    
#else
    if (m_bThreadExists) {
        void* pExit=NULL;
       pthread_join(m_ThreadHandle, &pExit);
    }
#endif
}

void CMoyeaBasedThread::Suspend()
{
    m_bSuspended = true;
#ifdef WIN32
    assert(m_ThreadHandle != NULL);
    SuspendThread((HANDLE)m_ThreadHandle);
#endif
}

void CMoyeaBasedThread::Resume()
{
    m_bSuspended = false;
#ifdef WIN32
    assert(m_ThreadHandle != NULL);
    ResumeThread((HANDLE)m_ThreadHandle);
#endif
}    

bool CMoyeaBasedThread::Wait(uint32_t t)
{
#ifdef WIN32
    if (WaitForSingleObject((HANDLE)m_ThreadHandle, t) == WAIT_OBJECT_0) {
        return true;
    } else return false;
#else
    uint32_t ta=0;
    if (t != INFINITE) { 
        while(m_bThreadExists) {
            if (ta >= t) {
                return !m_bThreadExists;
            }
            usleep(10000); //10ms
            ta += 10;
        }
        return true;
    } else {
        while(m_bThreadExists) {
            usleep(10000);
        }
        return true;
    }
#endif
}

const CBaseException& CMoyeaBasedThread::GetThreadException(void) const
{
    return m_ThreadException;
}

bool CMoyeaBasedThread::IsSuspended()
{
  return m_bSuspended;
}

bool CMoyeaBasedThread::GetExitCode(uint32_t& nCode)
{
#ifdef WIN32
    if (m_bThreadExists) {
        return false;
    } else {
        return GetExitCodeThread((HANDLE)m_ThreadHandle, (LPDWORD)&nCode) != 0;
    }
#else
    if (m_bThreadExists) {
        return false;
    } else {
        nCode = m_ThreadExitCode;
        return true;
    }
#endif
}

#ifdef WIN32
uint32_t STDCALL CMoyeaBasedThread::ThreadProc(void* p)
{
    CMoyeaBasedThread* pThis = (CMoyeaBasedThread*)p;
    assert(p != NULL);

    uint32_t nCode = (uint32_t)-1;
    if (!pThis->m_bSuspended)
    {
        try {
            nCode = pThis->Execute();
        } CatchAllAndCopy();
    }
    pThis->m_ThreadException.Copy(GetMoyeaException());
    FreeExp();
    pThis->m_bThreadExists = false;
    _endthreadex(nCode);
    return nCode;
}

uintptr_t CMoyeaBasedThread::GetThreadHandle()
{
    return m_ThreadHandle;
}

#else
void* CMoyeaBasedThread::ThreadProc(void* p)
{
    CMoyeaBasedThread* pThis = (CMoyeaBasedThread*)p;
    assert(p != NULL);
    
    while(pThis->IsSuspended()) {
        usleep(10000);
    }
    uint32_t nCode = (uint32_t)-1;
    try {
        nCode = pThis->Execute();
    } CatchAllAndCopy();
    pThis->m_ThreadException.Copy(GetMoyeaException());
    FreeExp();
    pThis->m_ThreadExitCode = nCode;
    pThis->m_bThreadExists = false;
    pthread_exit(NULL);
    return NULL;
}

pthread_t CMoyeaBasedThread::GetThreadHandle()
{
    return m_ThreadHandle;
}
#endif

//////////////////////////////////////////////////////////////////////////

CMoyeaBasedProcess::CMoyeaBasedProcess(const string& cmdline,bool bOpenPipe)
{
    m_CmdLine = cmdline;
#ifdef WIN32
    m_hProcess = NULL;
    m_bOpenPipe = bOpenPipe;
#else
    m_pid = 0;
    m_LaunchThread = 0;
    m_ExitCode = 0;
    m_bOpenPipe = false;
#endif
    m_bWaitWhenDestruct=true;
}

void CMoyeaBasedProcess::SetWaitWhenDestruct(bool bWait)
{
    m_bWaitWhenDestruct = bWait;
}

bool CMoyeaBasedProcess::Run(bool bSuspend)
{
    return RunInternal(bSuspend, false);
}

CMoyeaBasedProcess::~CMoyeaBasedProcess()
{
#ifdef WIN32
    if (m_hProcess != NULL) {
        if (m_bWaitWhenDestruct) {
            try {
                Wait(INFINITE);
            } CatchAllAndCopy();
        }    
        CloseHandle(m_hProcess);
        CloseHandle(m_hThread);
    }
#else
    if (m_LaunchThread != 0) {
        if (m_bWaitWhenDestruct) {
            void* pExit=NULL;
            pthread_join(m_LaunchThread, &pExit);
        } else {
            pthread_cancel(m_LaunchThread);
            void* pExit=NULL;
            pthread_join(m_LaunchThread, &pExit);
        }
    }
#endif
}

unsigned long CMoyeaBasedProcess::GetPipeData(char* pBuffer,unsigned long ulBufferMaxLen)
{
    if( pBuffer == NULL || ulBufferMaxLen <= 0 || !m_bOpenPipe){
        return 0;
    }

    unsigned long ulReturnLen = 0;
#ifdef WIN32
    if( PeekNamedPipe(m_hPipeOutputRead, NULL, 0, NULL, &ulReturnLen, NULL) ){
        if( ulReturnLen >= ulBufferMaxLen ){
            BOOL bResult = ReadFile(
                m_hPipeOutputRead,      // handle of the read end of our pipe
                pBuffer,            // address of buffer that receives data
                ulBufferMaxLen,     // number of bytes to read
                &ulReturnLen, // address of number of bytes read
                NULL                  // non-overlapped.
                );
        }
    }
#endif
    return ulReturnLen;
}

bool CMoyeaBasedProcess::RunInternal(bool bSuspend, bool bBackgroundly)
{
#ifdef WIN32
    if (m_hProcess != NULL) {
        ThrowExp(errCallingContext, "The process has run already");
    }
    STARTUPINFOW info;
    GetStartupInfoW(&info);
    if (bBackgroundly) {
        info.wShowWindow = SW_HIDE;
        info.dwFlags = STARTF_USESHOWWINDOW;
    }else{
        info.wShowWindow = SW_SHOW;
    }

    if( m_bOpenPipe ){
        //创建管道
        SECURITY_ATTRIBUTES sa={0};
        sa.nLength = sizeof(sa);
        sa.bInheritHandle = TRUE;
        sa.lpSecurityDescriptor = NULL;

        //为标准输出重定向创建管道
        if( CreatePipe(&m_hPipeOutputRead,  // read handle
            &m_hPipeOutputWrite, // write handle
            &sa,      // security attributes
            0      // number of bytes reserved for pipe - 0 default
            )){
                info.hStdOutput  = m_hPipeOutputWrite;
                info.hStdError   = m_hPipeOutputWrite;
                info.dwFlags  |= STARTF_USESTDHANDLES;
        }
        //管道创建失败，还可以执行进程
    }

    wstring cmdline = utf8_to_wide(m_CmdLine.c_str());
    DWORD flag = 0;
    if (bSuspend) {
        flag = CREATE_SUSPENDED;
    }
    PROCESS_INFORMATION pinfo;
    if (!CreateProcessW(NULL, (LPWSTR)cmdline.c_str(), NULL, NULL, m_bOpenPipe, flag, NULL, NULL, &info, &pinfo)) {
        return false;
    }
    m_hProcess = pinfo.hProcess;
    m_hThread = pinfo.hThread;
    return true;
#else
    if (m_LaunchThread != 0) {
        ThrowExp(errCallingContext, "The process has run already");
    }
    m_bSuspended = bSuspend;
    m_bBackgroundly = bBackgroundly;
    m_pid = -1;
    if (pthread_create((pthread_t*)&m_LaunchThread, NULL, ProcessLuanchThread, this) != 0) {
        return false;
    }
    while(m_pid == -1) { //等待完成fork
        usleep(10000);
    }
    return m_pid != 0;
#endif
}

#ifndef WIN32
void* CMoyeaBasedProcess::ProcessLuanchThread(void* p)
{
    CMoyeaBasedProcess* pThis = (CMoyeaBasedProcess*)p;
    pThis->LaunchProcess();
    return NULL;
}

void CMoyeaBasedProcess::LaunchProcess()
{
    pid_t pid = fork();
    if (pid == 0) { //child process
        vector<string> arr;
        if (parse_cmd_line(m_CmdLine.c_str(), arr) == 0) {
            exit(-2);
        }
        char** argv = (char**)malloc((arr.size()+1)*sizeof(char*));
        if (argv == NULL) {
            exit(-1);
        }
        int i;
        for(i=0; i<(int)arr.size(); ++i) {
            argv[i] = (char*)arr[i].c_str();
        }
        argv[i] = NULL;
        pid = getpid();
        if (m_bBackgroundly) {
            signal(SIGHUP, SIG_IGN);
        }
        if (m_bSuspended) {
          kill(pid, SIGSTOP);
        }
        execvp(arr[0].c_str(), argv);
        exit(-2); 
    } else if (pid == -1) { //error
        m_pid = 0;
    } else {
        m_pid = pid;
        int err;
        pid_t status;
        do {
            err = waitpid(pid, (int*)&status, WNOHANG);
            if (err == 0) {
                usleep(10000);
                pthread_testcancel();
            } else if (err < 0) {
                m_ExitCode = (uint32_t)-1;
                break;
            } else if (WIFEXITED(status)) {
                m_ExitCode = (uint32_t)(WEXITSTATUS(status) & 0xFF);
                break;
            }
        } while(1);
    }
    m_LaunchThread = 0;
}
#endif

bool CMoyeaBasedProcess::RunBackgroundly(bool bSuspend)
{
    return RunInternal(bSuspend, true);
}

///挂起进程
void CMoyeaBasedProcess::Suspend()
{
#ifdef WIN32
    if (m_hProcess == NULL) {
        ThrowExp(errCallingContext, "The process has not run");
    }
    SuspendThread(m_hThread);
#else
    if (m_pid == 0) {
        ThrowExp(errCallingContext, "The process has not run");
    }
    kill(m_pid, SIGSTOP);
#endif
}

///恢复挂起的进程
void CMoyeaBasedProcess::Resume()
{
#ifdef WIN32
    if (m_hProcess == NULL) {
        ThrowExp(errCallingContext, "The process has not run");
    }
    ResumeThread(m_hThread);
#else
if (m_pid == 0) {
        ThrowExp(errCallingContext, "The process has not run");
    }
    kill(m_pid, SIGCONT);
#endif
}

bool CMoyeaBasedProcess::Wait(uint32_t t)
{
#ifdef WIN32
    if (m_hProcess == NULL) {
        ThrowExp(errCallingContext, "The process has not run");
    }
    return WaitForSingleObject(m_hProcess, t) == WAIT_OBJECT_0;
#else
   if (m_pid == 0) {
        ThrowExp(errCallingContext, "The process has not run");
    }
    if (t == INFINITE) {
        while (m_LaunchThread != 0) {
            usleep(10000);
        }
        return true;
    } else {
        uint32_t ta=0;
        while (m_LaunchThread != 0) {
            if (ta >= t) break;
            usleep(10000);
            ta += 10;
        }
        return m_LaunchThread == 0;
    }
#endif
}

bool CMoyeaBasedProcess::Terminate(uint32_t nCode)
{
#ifdef WIN32
    if (m_hProcess == NULL) {
        ThrowExp(errCallingContext, "The process has not run");
    }
    return TerminateProcess(m_hProcess, nCode) != 0;
#else
   if (m_pid == 0) {
        ThrowExp(errCallingContext, "The process has not run");
    }
    m_ExitCode = nCode;
    bool bOK = kill(m_pid, SIGKILL) == 0;    
    if (bOK) {
        void* pExit=NULL;
        pthread_join(m_LaunchThread, &pExit);
        m_ExitCode = nCode;
    }
    return bOK;
#endif
}

bool CMoyeaBasedProcess::GetExitCode(uint32_t& nCode)
{
#ifdef WIN32
    if (m_hProcess == NULL) {
        ThrowExp(errCallingContext, "The process has not run");
    }
    bool bErr = GetExitCodeProcess(m_hProcess, (DWORD*)&nCode) != 0;
    if (bErr && STILL_ACTIVE == nCode) return false;
    else return bErr;
#else
    if (m_pid == 0) {
        ThrowExp(errCallingContext, "The process has not run");
    } 
    if (m_LaunchThread != 0) { //process is not end
      return false;
    }
    nCode = m_ExitCode;
    return true;
#endif
}
#ifdef WIN32
HANDLE CMoyeaBasedProcess::GetProcessHandle()
{
    try{
        if(NULL == m_hProcess)
            ThrowExp(errNullValue, "process handle is null");
        return m_hProcess;
    }CatchAllAndCopy();
    return NULL;
}
#endif

#ifdef __APPLE__
int32_t CMoyeaBasedProcess::GetProcesspId()
{
    return m_pid;
}
#endif




//////////////////////////////////////////////////////////////////////////


CTmpFile::CTmpFile(const string& ext, const char* pfileName)
{
    m_bOwned = false;
    m_FilePathName = CreateTempFile("", ext);
    if (pfileName){
        m_FilePathName = extract_file_path(m_FilePathName) + pfileName + extract_file_ext(m_FilePathName);
    }
}

CTmpFile::CTmpFile(const string& folder, const string& ext)
{
    m_bOwned = false;
    m_FilePathName = CreateTempFile(folder, ext);
}

const string& CTmpFile::GetFilePathName()
{
    return m_FilePathName;
}
void CTmpFile::SetOwned(bool bOwn)
{
    m_bOwned = bOwn;
}

#ifdef WIN32
string CTmpFile::CreateTempFile(const string& folder, const string& ext)
{
    wchar_t path[MAX_PATH];
    wstring folder_wide;
    if (folder.empty()) {
        wchar_t folder_wide_arr[MAX_PATH+1];
        uint32_t nSize = GetTempPathW(MAX_PATH, folder_wide_arr);
        if (nSize == 0) {
            ThrowUnexpected();
        }        
        folder_wide = folder_wide_arr;
    } else {
        folder_wide = utf8_to_wide(folder.c_str());        
    }
    if (GetTempFileNameW(folder_wide.c_str(), L"", 0, path) == 0) {
        ThrowUnexpected();
    }
    wstring r = path;
    DeleteFileW(path);
    r += utf8_to_wide(ext.c_str());
    return wide_to_utf8(r.c_str());    
}
#else
string CTmpFile::CreateTempFile(const string& folder, const string& ext)
{
   char* pfull=NULL;
   if (folder.empty()) {
      pfull = tempnam(NULL, "tmpf");
   } else {
      pfull = tempnam(utf8_to_local(folder.c_str()).c_str(), "tmpf");
   }
   if (pfull == NULL) {
     ThrowUnexpected();
   }
   MallocAllocator ma;
   ma.Attach(pfull);
   string r = local_to_utf8(pfull);
   return r + ext;
}
#endif

CTmpFile::~CTmpFile()
{
    if (m_bOwned) {        
        #ifdef WIN32
            DeleteFileW(utf8_to_wide(m_FilePathName.c_str()).c_str());
        #else
            unlink(utf8_to_local(m_FilePathName.c_str()).c_str());
        #endif
    }
}


//////////////////////////////////////////////////////////////////////////

string TrimLeft(const string& text, const string& chars)
{
    const char* p = text.c_str();    
    const char* pc;
    while(*p) {
        pc = chars.c_str();
        while(*pc) {
            if (*pc == *p) {
                break;
            }
            ++pc;
        }
        if (*pc) ++p;
        else break;
    }
    return string(p);
}

string TrimRight(const string& text, const string& chars)
{
    if (text.empty()) return text;

    const char* p = text.c_str();    
    const char* pc;
    const char* q = p + (text.length()-1);
    while(q >= p) {
        pc = chars.c_str();
        while(*pc) {
            if (*pc == *q) {
                break;
            }
            ++pc;
        }
        if (*pc) --q;
        else break;
    }    
    string r;
    r.append(p, q-p+1);
    return r;
}


string Trim(const string& text, const string& chars)
{
    return TrimRight(TrimLeft(text, chars),chars);
}

static char* strupr(char* ps)
{
  char* p=ps;
  while(*p) {
    if (*p >= 'a' && *p <= 'z') {
       *p = *p - 'a' + 'A';
    }
    ++p;
  }
  return ps;
}
string UpperCase(const string& text)
{
    string r;
    r.append(text);
    strupr((char*)r.c_str());
    return r;
}

static char* strlwr(char* ps)
{
  char* p=ps;
  while(*p) {
    if (*p >= 'A' && *p <= 'Z') {
       *p = *p - 'A' + 'a';
    }
    ++p;
  }
  return ps;
}

string LowerCase(const string& text)
{
    string r;
    r.append(text);
    strlwr((char*)r.c_str());
    return r;
}

vector<string> StrSplit(const string& text, const string& chars,bool hasEmpty)
{
    vector<string> r;
    const char* p = text.c_str();
    const char* pc;
    const char* q = NULL;
    uint32_t len = 0;
    while(*p) {
        pc = chars.c_str();
        while(*pc) {
            if (*pc == *p) {
                break;
            }
            ++pc;
        }
        if (*pc) { //该字符需要删除
            if (len != 0) {
                string tmp;
                tmp.append(q, len);
                r.push_back(tmp);
            }
            else if(hasEmpty){
                r.push_back("");
            }
            ++p;
            len = 0;
        } else { //该字符不需要删除
            if (len == 0) {
                q = p;
            }
            len++;
            ++p;
        }
    }
    if (len != 0) {
        string tmp;
        tmp.append(q, len);
        r.push_back(tmp);
    }
    else if(hasEmpty){
        r.push_back("");
    }
    return r;
}

vector<wstring> WStrSplit(const wstring& text, const wstring& chars,bool hasEmpty)
{
    vector<wstring> r;
    const wchar_t *p = text.c_str();
    const wchar_t *pc;
    const wchar_t *q = NULL;
    uint32_t len = 0;
    while(*p!= NULL) {
        pc = chars.c_str();
        while(*pc) {
            if (*pc == *p) {
                break;
            }
            ++pc;
        }
        if (*pc) { //该字符需要删除
            if (len != 0) {
                wstring tmp;
                tmp.append(q, len);
                r.push_back(tmp);
            }
            else if(hasEmpty){
                wstring tmp;
                r.push_back(tmp);
            }
            ++p;
            len = 0;
        } else { //该字符不需要删除
            if (len == 0) {
                q = p;
            }
            len++;
            ++p;
        }
    }
    if (len != 0) {
        wstring tmp;
        tmp.append(q, len);
        r.push_back(tmp);
    }
    else if(hasEmpty)
    {
        wstring tmp;
        r.push_back(tmp);
    }
    return r;
}

bool GetNameValue(string line, string separator, string &name, string &value) {
    uint64_t index = line.find(separator, 0);
    if ((index == 0) || (index == string::npos))
        return false;
    name = line.substr(0, (uint32_t) index);
    value = line.substr((uint32_t) index + separator.length(), string::npos);
    return true;
}

int StrPos(const string& text, unsigned int start, const string& needle)
{
    size_t len = text.length();
    if (start >= len) {
        return -1;
    }
    if (needle == "") { //空字符串
        return -1;
    }
    size_t len2 = needle.length();
    for(unsigned int i=start; i<len; ++i) {
        unsigned int j;
        for(j=0; j<len2 && (i+j) < len; ++j) {
            if (text[i+j] != needle[j]) {
                break;
            }
        }
        if (j == len2) {
            return i;
        }
    }
    return -1;
}

int StrRPos(const string& text, unsigned int start, const string& needle)
{
    size_t len = text.length();
    if (len == 0) return -1;
    if (start > len-1) {
        start = (unsigned int)len-1;
    }
    if (needle == "") { //空字符串
        return -1;
    }
    size_t len2 = needle.length();
    for(int i=start; i>=0; --i) {
        unsigned int j;
        for(j=0; j<len2 && (i+j) < len; ++j) {
            if (text[i+j] != needle[j]) {
                break;
            }
        }
        if (j == len2) {
            return i;
        }
    }
    return -1;
}

string LeftStr(const string& text, unsigned int n)
{
    size_t len = text.length();
    if (n >= len) {
        return text;
    }
    MallocAllocator ma;
    ma.Malloc(n+1);
    char* p = (char*)ma.GetHandle();
    strncpy(p, text.c_str(), n);
    p[n] = '\0';
    return string(p);
}

string RightStr(const string& text, unsigned int n)
{
    size_t len = text.length();
    if (n >= len) {
        return text;
    }
    MallocAllocator ma;
    ma.Malloc(n+1);
    char* p = (char*)ma.GetHandle();
    strncpy(p, text.c_str()+len-n, n);
    p[n] = '\0';
    return string(p);
}

string SubStr(const string& text, unsigned int start, unsigned int len)
{
    size_t len2 = text.length();
    if (start >= len2) {
        return "";
    }
    return LeftStr(text.c_str()+start, len);
}

string StrReplace(const string& text, const string& find, const string& replace)
{
    string r;
    int pos = -1;
    unsigned int start_pos=0;
    unsigned int find_len=(unsigned int)find.length();

    if (find_len == 0) { //我们不查找空字符串
        return text;
    }
    for(;;) {
        pos = StrPos(text, start_pos, find);
        if (pos != -1) {
            if (pos != 0) {
                r = LeftStr(text, pos);
            }
            r += replace;
            start_pos = (unsigned int)pos + find_len;
        } else break;
    } 
    r += SubStr(text, start_pos, INFINITE);
    return r;
}

string StrReplaceAll(const string& text, const string& find, const string& replace)
{
    if (find.empty())
    {
        return text;
    }
    
    string r(text);
    string::size_type pos = 0;
    string::size_type a = find.size();
    string::size_type b = replace.size();
    while((pos = r.find(find,pos)) != string::npos) {
        r.replace(pos, a, replace);
        pos+=b;
    }
    return r;
}

string IntToStr(int d)
{
    stringstream tmp;
    tmp << d;
    return tmp.str();
}
string IntToFixStr(int d, int32_t len, char cFill, bool bHex)
{
    stringstream tmp;
    if (bHex) {
        tmp << setw(len) << setfill(cFill) << std::hex << d;
    } else {
        tmp << setw(len) << setfill(cFill) << d;
    }
    return tmp.str();
}

int StrToInt(const string& text)
{
    int r=0;
    sscanf(text.c_str(), "%d", &r);
    return r;
}

int parse_cmd_line(const string& cmdline, vector<string> & arr)
{
  arr.clear();
  const char* p = cmdline.c_str();
  string r;
  char state='0'; //使用0, \, "表示当前自动机的状态
  char oldstate='0';
  char ch;
  while((ch = *p++) != 0) {
    switch(state) {
        case '0':  //普通态
            if (ch == '\\') {
                state = '\\';
                oldstate = '0';
                continue;
            } else if (ch == ' ') { //参数间隔
                if (!r.empty()) {
                    arr.push_back(r);
                }
                r.clear();
                continue;
            } else if (ch == '"') { //进入引号状态
                if (r.empty()) { //参数首个字符为引号，切换当前状态，否则当成普通字符
                    state = '"';
                    oldstate = '"';
                } else {
                    r.append(&ch, 1);
                }
            } else {
                r.append(&ch, 1);
            }
            break;
        case '\\': //转义状态
            if (ch == '\\' || ch == '"') { //转义引号或者斜杠
                r.append(&ch, 1);
                state = oldstate; 
                continue;
            } else { //不是一个合法的转义
                r.append("\\", 1);
                r.append(&ch, 1);
                state = oldstate;
                continue;
            }
            break;
        case '"': //引号态
            if (ch == '\\') {
                oldstate = '"';
                state = '\\';
                continue;
            } else if (ch == '"') { //引号态结束？
              if (*p == ' ' || *p == '\0') {
                state = '0';
                oldstate = '0';
                arr.push_back(r);
                r.clear();
                continue;
              } else { //把引号当成普通字符
                r.append(&ch, 1);
              }
            } else {
                r.append(&ch, 1);
            }
            break;
    }
  }
  if (!r.empty()) {
       arr.push_back(r);
  }
  return (int)arr.size();
}

bool StrMatch(const char* text, const char* pattern)
{
    switch (pattern[0])
    {
    case '\0':
        return !text[0];

    case '*' :
        return StrMatch(text, pattern+1) || text[0] && StrMatch(text+1, pattern);

    case '?' :
        return text[0] && StrMatch(text+1, pattern+1);

    default  :
        return (toupper(pattern[0]) == toupper(text[0])) && StrMatch(text+1, pattern+1);
    }

}

//--生成GUID
string CreateGUIDString(bool haveBrace)
{
#ifdef WIN32
    char buf[64] = {0};
    GUID guid;
    CoInitialize(NULL);
    string format = "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}";
    if (!haveBrace) {
        format = "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X";
    }
    //FIXME 是否需要先调用CoInitialize，网上流传的版本是加上此函数，而我使用的时间不加也可以正常使用
    if (S_OK == ::CoCreateGuid(&guid)) {
        sprintf_s(buf, sizeof(buf),format.c_str(),
            guid.Data1,guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1],guid.Data4[2],
            guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    }
    return buf;
#else
    char str[36];
    uuid_t uuid;
    uuid_generate(uuid);
    uuid_unparse(uuid, str);
    string r(str);
    if (haveBrace) {
        r = "{" + r + "}";
    }
    return r;
#endif
}

string Format(string format, ...) {
#ifdef WIN32
    string result = "";
    va_list arguments;
    va_start(arguments, format);
    result = vformat(format, arguments);
    va_end(arguments);
    return result;
#else
    va_list arglist;
    char buffer[256];

    va_start(arglist, format.c_str());
    vsnprintf(buffer, 256, format.c_str(), arglist);
    va_end(arglist);

    return string(buffer);
#endif
}

#define MAX_PRINTF_SIZE 1024 * 1024

#ifdef WIN32
int vasprintf(char **strp, const char *fmt, va_list ap, int size = 256){
    if (size > MAX_PRINTF_SIZE)
    {
        return 0;
    }

    *strp=(char *)malloc(size + 1);
    int result=0;
    if((result=vsnprintf(*strp,size,fmt,ap))==-1){
        free(*strp);
        return vasprintf(strp,fmt,ap,size+size/2);
    }else{
        return result;
    }
}
#endif // WIN32

string vformat(string format, va_list args) {
#ifdef WIN32
    char *pBuffer = NULL;
    vasprintf(&pBuffer, STR(format), args);
    string result = pBuffer;
    free(pBuffer);
    return result;
#else
    assert(false); //FIXME not completed
    return "";
#endif // WIN
}

string BinaryToHexString(void * buffer,uint32_t len, string space/* = ""*/)
{
    CheckPointer(buffer);
    uint8_t * pBuffer = (uint8_t *)buffer;
    string result;
    for (uint32_t i = 0; i < len; i++)
    {
        result += Format("%02X%s", pBuffer[i], STR(space));
    }
    return result;
}

uint8_t chr2hex(char c)
{
    if(c <= 57 && c >= 48)
        return c-48;
    else if(c <= 102 && c >= 97)
        return c-97+10;

    return -1;
}

uint32_t hex2bin(string &src, OUT string &hex)
{
    src = LowerCase(src);
    const char * str = src.c_str();
    if(!str){
        return 0;
    }

    uint32_t len = (uint32_t)strlen(str);
    if(len % 2 != 0)//必须是双数
        return 0;

    uint32_t ret = len/2;
    len /= 2;

    //申请空间
    hex.resize(len);
    uint8_t *pBuffer = (uint8_t *)hex.data();

    while(len) {
        int d1 = chr2hex(*str); str++;
        int d2 = chr2hex(*str); str++;

        if(d1<0 || d2<0) {           
            *pBuffer=NULL;
            return -1;
        }

        *pBuffer = (unsigned char)(d1*16+d2);
        pBuffer++;
        len--;
    }
    return ret;
}

uint32_t HexToBin(string &ma, const char * pHex,string spliter)
{
    vector<string > hexList = StrSplit(pHex, spliter);
    ma.clear();

    uint32_t offset = 0;
    string outBuffer ;
    for(uint32_t i = 0; i< hexList.size(); i++)
    {
        offset = hex2bin(hexList[i], outBuffer);
        ma.append(STR(outBuffer),offset);//追加这一部分
    }
    return (uint32_t)ma.size();
}



#if !CONFIG_HAVE_ALIGNED_MALLOC

void * _aligned_malloc(
                       size_t size, 
                       size_t alignment
                       )
{
    if (alignment == 0) alignment = 1;
    void* p = malloc(size + alignment + 2*sizeof(size_t));
    if (p == NULL) return NULL;
    uint8_t* pm = (uint8_t*)p + 2*sizeof(size_t); //空出内存控制块的大小    
    size_t offset = (intptr_t)pm % alignment;
    if (offset != 0) {
        offset = alignment - offset;
    } 
    pm += offset; //移动内存指针到对齐的位置
    size_t* pmc = (size_t*)(pm - 2*sizeof(size_t)); //对齐的内存块前面紧跟内存控制块, 第一个size_t存放偏移, 第二个size_t存放内存块大小

    *pmc = offset; //在内存块的偏移
    *(pmc+1) = size; //在内存块的大小
    return pm;
}

void _aligned_free (
                    void *memblock
                    )
{
    size_t* pmc = (size_t*) ((uint8_t*)memblock - 2 * sizeof(size_t));
    uint8_t* p=(uint8_t*)memblock;
    p -= ((*pmc) + 2 * sizeof(size_t));
    free(p);
}

void * _aligned_realloc(
                        void *memblock, 
                        size_t size, 
                        size_t alignment
                        )
{
    if (alignment == 0) alignment = 1;
    if (!memblock) {
        return _aligned_malloc(size, alignment);
    } else {
        void* p = _aligned_malloc(size, alignment);
        if (p == NULL) {
            _aligned_free(memblock);
            return NULL;
        }
        size_t s = *((size_t*)memblock - 1);
        if (s > size) {
            s = size;
        }
        memcpy(p, memblock, s);
        _aligned_free(memblock);
        return p;
    }
}
#endif


//////////////////////////////////////////////////////////////////////////
// CDataBuffer2
CDataBuffer2::CDataBuffer2(bool bMutex)
{
    m_pCritical = NULL;
    if (bMutex) {
        m_pCritical = init_critical();
    }
    m_nDataSize = 0;
}


void CDataBuffer2::PushFront(const void* pData, size_t nSize)
{
    if (nSize == 0 || pData == NULL) return;
    DataNode dn;
    dn.m_pData = malloc(nSize);
    if (dn.m_pData == NULL) {
        ThrowExp(errNoMemory, "No enough memory");
    }
    dn.m_nDataOffset = 0;
    dn.m_nDataSize = nSize;
    memcpy(dn.m_pData, pData, nSize);

    CCriticalAutoLock lock(m_pCritical);
    m_DataQueue.push_front(dn);
    m_nDataSize += nSize;
}

void CDataBuffer2::Push(const void* pData, size_t nSize)
{
    if (nSize == 0 || pData == NULL) return;
    DataNode dn;
    dn.m_pData = malloc(nSize);
    if (dn.m_pData == NULL) {
        ThrowExp(errNoMemory, "No enough memory");
    }
    dn.m_nDataOffset = 0;
    dn.m_nDataSize = nSize;
    memcpy(dn.m_pData, pData, nSize);

    CCriticalAutoLock lock(m_pCritical);
    m_DataQueue.push_back(dn);
    m_nDataSize += nSize;
}

size_t CDataBuffer2::Pop(void* pData, size_t nSize)
{
    CCriticalAutoLock lock(m_pCritical);
    if (m_DataQueue.empty() ) {        
        return 0;        
    }
    size_t nRead = 0;
    while(nRead < nSize && !m_DataQueue.empty()) {
        DataNode& dn = m_DataQueue.front();
        if (nRead + dn.m_nDataSize - dn.m_nDataOffset > nSize) { //data is enough
            if (pData) {
                memcpy((uint8_t*)pData+nRead, (const uint8_t*)dn.m_pData+dn.m_nDataOffset, nSize-nRead);
            }
            dn.m_nDataOffset += nSize-nRead;                
            nRead = nSize;                
            m_nDataSize -= nRead;
            return nRead;
        } else { //not enough ?
            if (pData) {
                memcpy((uint8_t*)pData+nRead, (const uint8_t*)dn.m_pData+dn.m_nDataOffset,  dn.m_nDataSize - dn.m_nDataOffset);
            }
            nRead += dn.m_nDataSize - dn.m_nDataOffset;
            free(dn.m_pData);
            m_DataQueue.pop_front();
        }
    }
    m_nDataSize -= nRead;
    return nRead;
}

size_t CDataBuffer2::GetDataSize()
{
    CCriticalAutoLock lock(m_pCritical);
    return m_nDataSize;
}

void CDataBuffer2::Clear()
{
    CCriticalAutoLock lock(m_pCritical);
    while(!m_DataQueue.empty()) {
        DataNode& dn = m_DataQueue.front();
        free(dn.m_pData);
        m_DataQueue.pop_front();
    }
    m_nDataSize = 0;
}

CDataBuffer2::~CDataBuffer2()
{
    Clear();
    if (m_pCritical) {
        delete_critical(m_pCritical);
        m_pCritical = NULL;
    }
}

void MoyeaBased_Sleep(uint32_t nMilliseconds)
{
#ifdef WIN32
    // jim1007
    
    Sleep(nMilliseconds);
#else    
    usleep(nMilliseconds*1000);
#endif
}

uint32_t MoyeaBased_GetTicks(void)
{
#ifdef WIN32
    // jim1007
    
    return timeGetTime();

#elif defined(__APPLE__)
    static uint64_t start_time=0;
    static struct mach_timebase_info timebase;
    
    uint64_t t = mach_absolute_time();
    if (start_time == 0) {
       start_time = t;
       mach_timebase_info(&timebase);
    }
    t -= start_time;
    return t/1000*timebase.numer/(timebase.denom*1000);
#else
    //FIXME: 以下的实现方式当系统时间变化时会有问题
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000+tv.tv_usec/1000);    
#endif
}

int32_t get_cpu_count()
{
#ifdef WIN32
    string v;
    get_environment_variable("NUMBER_OF_PROCESSORS", v);
    int n = StrToInt(v);
    if (n == 0) n = 1;
    return n;
#elif defined(__APPLE__)
    int     count = 1;
    size_t  size=sizeof(count) ;
    if (sysctlbyname("hw.ncpu",&count,&size,NULL,0) != 0) return 1;
    return count; 
#else
    assert(false);
    //FIXME: Not implement yet
#endif
}

    //////////////////////////////////////////////////////////////////////////
    
    rect_t scaleToAspect(rect_t rc, uint32_t w, uint32_t h, rect_t &rcLeft, rect_t &rcRight)
    {
        if (w==0 || h==0)
        {
            return rc;
        }

        float fCenterXPos = rc.left + GetWidth(rc)/2;
        float fCenterYPos = rc.top + GetHeight(rc)/2;

        float fWidth = GetWidth(rc);
        float fHeight = GetWidth(rc) * h / w;

        bool bHeightNotChanged = false;
        rect_t middleRect = {0};
        if (fHeight > GetHeight(rc)) // 高度不变，拉伸宽度 
        {
            fHeight = GetHeight(rc);
            fWidth = GetHeight(rc) * w / h;

            bHeightNotChanged = true;

            middleRect = MakeRect(
                (float)(int32_t)(fCenterXPos-fWidth/2), 
                rc.top, 
                (float)(int32_t)(fCenterXPos+fWidth/2), 
                rc.bottom); 
        }
        else // 否则宽度不变，拉伸高度
        {
            middleRect = MakeRect(
                rc.left, 
                (float)(int32_t)(fCenterYPos-fHeight/2), 
                rc.right, 
                (float)(int32_t)(fCenterYPos+fHeight/2)); 
        }
            
        if (bHeightNotChanged)
        {
            rcLeft = MakeRect(rc.left, rc.top,
                middleRect.left, rc.bottom);

            rcRight = MakeRect(middleRect.right, middleRect.top,
                rc.right, rc.bottom);
        }
        else
        {
            rcLeft = MakeRect(rc.left, rc.top,
                rc.right, middleRect.top);

            rcRight = MakeRect(rc.left, middleRect.bottom,
                rc.right, rc.bottom);
        }

        return middleRect;
    }

    //////////////////////////////////////////////////////////////////////////
    //Base64
    string ZBase64::Encode(const unsigned char* data,int size, bool bLine /*= true*/)
    {
        //编码表
        const char EncodeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        //返回值
        string strEncode;
        unsigned char Tmp[4]={0};
        int LineLength=0;
        for(int i=0;i<(int)(size / 3);i++)
        {
            Tmp[1] = *data++;
            Tmp[2] = *data++;
            Tmp[3] = *data++;
            strEncode+= EncodeTable[Tmp[1] >> 2];
            strEncode+= EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
            strEncode+= EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
            strEncode+= EncodeTable[Tmp[3] & 0x3F];
			if(bLine){	//是否换行 根据RFC822规定，BASE64Encoder编码每76个字符，还需要加上一个回车换行
				LineLength+=4; 
				if(LineLength==76) {strEncode+="\r\n";LineLength=0;}
			}
        }
        //对剩余数据进行编码
        int Mod=size % 3;
        if(Mod==1)
        {
            Tmp[1] = *data++;
            strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
            strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4)];
            strEncode+= "==";
        }
        else if(Mod==2)
        {
            Tmp[1] = *data++;
            Tmp[2] = *data++;
            strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
            strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
            strEncode+= EncodeTable[((Tmp[2] & 0x0F) << 2)];
            strEncode+= "=";
        }

        return strEncode;
    }

    string ZBase64::Decode(const char* data, int size, OUT int& outBytes)
    {
        //解码表
        const char DecodeTable[] =
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            62, // '+'
            0, 0, 0,
            63, // '/'
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
            0, 0, 0, 0, 0, 0, 0,
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
            13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
            0, 0, 0, 0, 0, 0,
            26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
            39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
        };
        //返回值
        outBytes = 0;
        string strDecode;
        int nValue;
        int i= 0;
        while (i < size)
        {
            if (*data != '\r' && *data!='\n')
            {
                nValue = DecodeTable[*data++] << 18;
                nValue += DecodeTable[*data++] << 12;
                strDecode+=(nValue & 0x00FF0000) >> 16;
                outBytes++;
                if (*data != '=')
                {
                    nValue += DecodeTable[*data++] << 6;
                    strDecode+=(nValue & 0x0000FF00) >> 8;
                    outBytes++;
                    if (*data != '=')
                    {
                        nValue += DecodeTable[*data++];
                        strDecode+=nValue & 0x000000FF;
                        outBytes++;
                    }
                }
                i += 4;
            }
            else// 回车换行,跳过
            {
                data++;
                i++;
            }
        }
        return strDecode;
    }

	int64_t StringToInt64(const char* str)
	{
		int64_t val = 0;
		if(NULL != str && strlen(str) > 0){
#ifdef _MSC_VER
			sscanf_s(str, "%I64d", &val);
#else
			sscanf(str, "%lld", &val);
#endif
		}
		return val;
	}

	string Int64ToString(int64_t val)
	{
		char str[32] = {0};
#ifdef _MSC_VER
		sprintf_s(str, CountOfArray(str)-1, "%I64d", val);
#else
		sprintf(str, "%lld", val);
#endif
		return str;
	}
} //end of MoyeaBased
