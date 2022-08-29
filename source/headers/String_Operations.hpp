#ifndef _ALEX_STRING_OPS
#define _ALEX_STRING_OPS

//Standard Headers
#include <cctype>
#include <string>
#include <algorithm>

bool invalidChar(char);
void stripUnicode(std::string&);
void uppercaseify(std::string&);
void lowercaseify(std::string&);
void strip_brackets(std::string&);
void strip_quotations(std::string&);
void strip_parenthesis(std::string&);

#endif