#include "string_utils.h"

namespace AuntecBased {



string str_replace(const char* pText, const char* pFind, const char* pReplace)
{
    return string(pText);
}

int64_t string_to_long(const char* pText)
{
    int64_t r=0;
    sscanf(pText, "%lld", &r);
    return r;
}

vector<string> str_split(const char* pText, const char* pChars)
{
    vector<string> r;
	std::string s = pText;
	std::string delimiter = pChars;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		r.push_back(token);
		s.erase(0, pos + delimiter.length());
	}

    return r;
}



}
