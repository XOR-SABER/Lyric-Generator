#ifndef _ALEX_MARKOV_PARSING
#define _ALEX_MARKOV_PARSING

#include <cstdlib>
#include <unordered_map>
#include <cctype>
#include <sstream>
#include <algorithm>

//Function Prototypes: 
void logo();
void screen_wipe();
bool invalidChar(char);
std::string filehandler();
void first_cap(std::string&);
void stripUnicode(std::string&);
void uppercaseify(std::string&);
void lowercaseify(std::string&);
void parse_filename(std::string&);
void strip_brackets(std::string&);
void strip_quotations(std::string&);
void strip_parenthesis(std::string&);
#endif