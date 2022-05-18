#pragma once

#include "auntec_base_types.h"

#include <string>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

namespace AuntecBased
{
        /*!
        @brief 字符串替换V
        @param text 源字符串
        @param find 需要被替换的字符串
        @param replace 需要替换成的字符串
        @return 替换后的字符串
        */
        string str_replace(const char* pText, const char* pFind, const char* pReplace);


        /*!
        @brief 字符串转长整型
        */
        int64_t string_to_long(const char* pText);

        /*!
        @brief 分割字符串
        @param text 等待分割的字符串
        @param chars 分割符号
        */
        vector<string> str_split(const char* pText, const char* pChars);
}
