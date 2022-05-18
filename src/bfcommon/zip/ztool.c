#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

#include "zip.h"
#include "unzip.h"

#include "ztool.h"

#ifndef FILE_ATTRIBUTE_DIRECTORY
#   define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#endif

#define ZIP_GPBF_LANGUAGE_ENCODING_FLAG 0x800 // utf8

#define BUFFER_SIZE 4096

static int zip_add_file(zipFile zf, const wchar_t* fileNameInZip, const wchar_t* localFile, zip_compress_callback pcb, void* pctx)
{
    int ret = -1;
    int bmark = 0;
    LARGE_INTEGER li;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    DWORD dwFileAttr = GetFileAttributesW(localFile);
    if(dwFileAttr == INVALID_FILE_ATTRIBUTES){
        goto exit_lable;
    }

    if(INVALID_HANDLE_VALUE != (hFile = CreateFileW(localFile, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, ((dwFileAttr&FILE_ATTRIBUTE_DIRECTORY)!=0)?FILE_FLAG_BACKUP_SEMANTICS:0, NULL))){
        WORD wDate, wTime;
        FILETIME ftUTC, ftLocal;
        zip_fileinfo fileInfo;
        char fileNameInZipLocal[MAX_PATH] = {0};
        ZeroMemory(&fileInfo, sizeof(zip_fileinfo));
        WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)fileNameInZip, -1, fileNameInZipLocal, MAX_PATH-1, NULL, NULL);
        GetFileTime(hFile, NULL, NULL, &ftUTC);
        FileTimeToLocalFileTime(&ftUTC, &ftLocal);
        FileTimeToDosDateTime(&ftLocal, &wDate, &wTime);
        fileInfo.dosDate = ((((DWORD)wDate) << 16) | (DWORD)wTime);
        fileInfo.external_fa |= dwFileAttr;
        if(ZIP_OK != zipOpenNewFileInZip4(zf, fileNameInZipLocal, &fileInfo, NULL, 0, NULL,0, NULL, Z_DEFLATED, 9, 0, -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, NULL, 0, 0, ZIP_GPBF_LANGUAGE_ENCODING_FLAG)){
            goto exit_lable;
        }
        bmark = 1;
    }else{
        goto exit_lable;
    }

    if((dwFileAttr & FILE_ATTRIBUTE_DIRECTORY) != 0){
        ret = 0;
        goto exit_lable;
    }
    if(!GetFileSizeEx(hFile, &li)){
        goto exit_lable;
    }
    if(li.QuadPart > 0){
        BYTE byBuffer[BUFFER_SIZE];
        unsigned int counter = 0;
        while(li.QuadPart > 0){
            DWORD dwRead = 0;
            DWORD dwSizeToRead = 0;
            if((counter++)%10 == 0){
                if(NULL != pcb && 0 != pcb(pcb)){ // 回调检测
                    break;
                }
            }
            dwSizeToRead = li.QuadPart > (LONGLONG)BUFFER_SIZE ? BUFFER_SIZE : (DWORD)li.LowPart;
            if(!ReadFile(hFile, byBuffer, dwSizeToRead, &dwRead, NULL)){
                break;
            }
            if(zipWriteInFileInZip(zf, byBuffer, dwRead) < 0){
                break;
            }
            li.QuadPart -= (LONGLONG)dwRead;
        }
    }
    if(li.QuadPart <= 0){
        ret = 0;
    }

exit_lable:
    if(hFile != INVALID_HANDLE_VALUE){
        CloseHandle(hFile);
    }
    if(bmark){
        zipCloseFileInZip(zf);
    }
    return ret;
}

static int zip_add_files(zipFile zf, const wchar_t* fileNameInZip, const wchar_t* localFile, const wchar_t* parten, zip_compress_callback pcb, void* pctx)
{
    WIN32_FIND_DATAW fdw;
    wchar_t mchv[MAX_PATH] = {0};
    wchar_t rpath[MAX_PATH] = {0};
    HANDLE hFind = INVALID_HANDLE_VALUE;
    size_t rpathSize = wcslen(localFile);

    ZeroMemory(&fdw, sizeof(WIN32_FIND_DATAW));
    swprintf_s(rpath, MAX_PATH-1, L"%s", localFile);

    if(localFile[rpathSize-1] != (unsigned short)'/' && localFile[rpathSize-1] != (unsigned short)'\\'){
        ZeroMemory(rpath+rpathSize, (MAX_PATH-rpathSize)*sizeof(wchar_t));
        rpath[rpathSize] = (unsigned short)'\\';
    }
    swprintf_s(mchv, MAX_PATH-1, L"%s%s", rpath, parten);

    if(INVALID_HANDLE_VALUE == (hFind = FindFirstFileW(mchv, &fdw))){
        return 0;
    }

    do{
        wchar_t nextFileNameInZip[MAX_PATH] = {0};
        wchar_t nextLocalFilePath[MAX_PATH] = {0};

        if(NULL != pcb && 0 != pcb(pcb)){ // 回调检测
            break;
        }

        if(0 == wcscmp(fdw.cFileName, L".") || 0 == wcscmp(fdw.cFileName, L"..")){
            continue;
        }

        if((fdw.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0){
            swprintf_s(nextFileNameInZip, MAX_PATH-1, L"%s%s/", fileNameInZip, fdw.cFileName);
            swprintf_s(nextLocalFilePath, MAX_PATH-1, L"%s%s", rpath, fdw.cFileName);
            zip_add_file(zf, nextFileNameInZip, nextLocalFilePath, pcb, pctx);
            zip_add_files(zf, nextFileNameInZip, nextLocalFilePath, parten, pcb, pctx);
        }else{
            swprintf_s(nextFileNameInZip, MAX_PATH-1, L"%s%s", fileNameInZip, fdw.cFileName);
            swprintf_s(nextLocalFilePath, MAX_PATH-1, L"%s%s", rpath, fdw.cFileName);
            zip_add_file(zf, nextFileNameInZip, nextLocalFilePath, pcb, pctx);
        }
    }while(FindNextFileW(hFind, &fdw));

    FindClose(hFind);
    return 0;
}

static int zip_extract_file(unzFile uf, const wchar_t* dst, zip_uncompress_callback pcb, void* pctx)
{
    unz_file_info64 fileInfo;
    char fileNameInZip[MAX_PATH] = {0};
    wchar_t fileNameInZipW[MAX_PATH] = {0};
    wchar_t fileNameInLoaclW[MAX_PATH] = {0};
    if(UNZ_OK != unzGetCurrentFileInfo64(uf, &fileInfo, fileNameInZip, MAX_PATH-1, NULL, 0, NULL, 0)){
        return -1;
    }

    MultiByteToWideChar(CP_UTF8, 0, fileNameInZip, -1, (LPWSTR)fileNameInZipW, MAX_PATH-1);
    swprintf_s(fileNameInLoaclW, MAX_PATH-1, L"%s%s", dst, fileNameInZipW);

    if(fileInfo.external_fa&FILE_ATTRIBUTE_DIRECTORY){
        if(CreateDirectoryW(fileNameInLoaclW, NULL)){
            return 0;
        }else if(ERROR_ALREADY_EXISTS == GetLastError()){
            return 0;
        }
        return -1;
    }else{
        int ret = -1;
        int nSize = 0;
        DWORD dwWritten = 0;
        BYTE byBuffer[BUFFER_SIZE];
        HANDLE hFile = CreateFileW(fileNameInLoaclW, GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if(INVALID_HANDLE_VALUE == hFile){
            return ret;
        }
        if(UNZ_OK != unzOpenCurrentFile(uf)){
            CloseHandle(hFile);
            return ret;
        }

        while(1){
            nSize = unzReadCurrentFile(uf, byBuffer, BUFFER_SIZE);
            if(nSize <= 0){
                ret = 0;
                break;
            }else{
                if(!WriteFile(hFile, byBuffer, (DWORD)nSize, &dwWritten, NULL) || dwWritten != (DWORD)nSize){
                    break;
                }
            }
        }

        if(0 == ret){
            FILETIME ftLocal, ftUTC;
            DosDateTimeToFileTime((WORD)(fileInfo.dosDate>>16), (WORD)fileInfo.dosDate, &ftLocal);
            LocalFileTimeToFileTime(&ftLocal, &ftUTC);
            SetFileTime(hFile, &ftUTC, &ftUTC, &ftUTC);
        }

        CloseHandle(hFile);
        unzCloseCurrentFile(uf);
        return ret;
    }
}

static int zip_extract_files(zipFile uf, const wchar_t* dst, zip_uncompress_callback pcb, void* pctx)
{
    unsigned int i = 0;
    unz_global_info64 gi;
    wchar_t rpath[MAX_PATH] = {0};
    size_t rpathSize = wcslen(dst);

    swprintf_s(rpath, MAX_PATH-1, L"%s", dst);
    if(dst[rpathSize-1] != (unsigned short)'\\' && dst[rpathSize-1] != (unsigned short)'/'){
        ZeroMemory(rpath+rpathSize, (MAX_PATH-rpathSize)*sizeof(wchar_t));
        rpath[rpathSize] = (unsigned short)'\\';
    }

    if(!CreateDirectoryW(rpath, NULL)){
        if(ERROR_ALREADY_EXISTS != GetLastError()){
            return -1;
        }
    }

    ZeroMemory(&gi, sizeof(unz_global_info64));
    if(UNZ_OK != unzGetGlobalInfo64(uf, &gi)){
        return -1;
    }

    for(; i < gi.number_entry; ++i){
        if(NULL != pcb && 0 != pcb(pctx)){ // 回调检测
            break;
        }
        if(0 != zip_extract_file(uf, rpath, pcb, pctx)){
            assert(0);
            break;
        }
        if(i < gi.number_entry - 1){
            if(UNZ_OK != unzGoToNextFile(uf)){
                break;
            }
        }
    }
    return i >= gi.number_entry?0:-1;
}

int zip_compress2(const wchar_t* src, const wchar_t* dst, const wchar_t* parten, zip_compress_callback pcb, void* pctx)
{
    int ret = -1;
    zipFile zf = zipOpen64(dst, 0);
    if(NULL == zf){
        return ret;
    }
    ret = zip_add_files(zf, L"", src, parten, pcb, pctx);
    zipClose(zf, NULL);
    return ret;
}

int zip_compress(const wchar_t* src, const wchar_t* dst, zip_compress_callback pcb, void* pctx)
{
    return zip_compress2(src, dst, L"*", pcb, pctx);
}

int zip_uncompress(const wchar_t* src, const wchar_t* dst, zip_uncompress_callback pcb, void* pctx)
{
    int ret = -1;
    unzFile uf = unzOpen64(src);
    if(NULL == uf){
        return ret;
    }
    ret = zip_extract_files(uf, dst, pcb, pctx);
    unzClose(uf);
    return ret;
}
