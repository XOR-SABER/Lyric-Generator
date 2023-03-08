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
const void logo();
const void screen_wipe();
void first_cap(std::string&);
void parse_path(std::string&);
void reverse_parse_filename(std::string&);
std::string tokenize(const std::string&);
std::string filehandler();

#endif