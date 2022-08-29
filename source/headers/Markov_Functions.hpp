#ifndef _ALEX_MARKOV_PARSING
#define _ALEX_MARKOV_PARSING

//Standard Headers
#include <cctype>
#include <iostream>
#include <filesystem>

//Custom Headers
#include "read.h"
#include "String_Operations.hpp"


//Function Prototypes: Behold the usefulness of passing by refrence!
void logo();
void screen_wipe();
void tokenize(std::string&);
void first_cap(std::string&);
void parse_path(std::string&);
void reverse_parse_filename(std::string&);
std::string filehandler();

#endif