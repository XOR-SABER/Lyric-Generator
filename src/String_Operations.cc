#include "headers/String_Operations.hpp"

//Check for non-unicode characters
bool invalidChar (const char &c) { 
	return !(c>= 0 && c<128); 
}

//Turn food -> FOOD
void uppercaseify(std::string &s) {
	for (char &c : s) c = std::toupper(c);
}
//Turn FOOD -> food
void lowercaseify(std::string &s) {
	for (char &c : s) c = std::tolower(c);
}
//Turn FOOD -> Food, for starting a sentence
void first_cap(std::string &s) {
	if (s.empty()) return;
	for (char &c : s) c = std::tolower(c);
	s.at(0) = std::toupper(s.at(0));
}

//Eliminates all words between square brackets to remove informative lines in lyrics
void strip_brackets(std::string &s) {
	std::string retval;
	bool deleting = false;
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '[') deleting = true;
		else if (s[i] == ']') deleting = false;
		else if (!deleting) retval.push_back(s[i]);
	}
	s = retval;
}

// I added this since parenthesis look really messy and lead to non white space characters
void strip_parenthesis(std::string &s) {
	std::string retval;
	bool deleting = false;
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '(') deleting = true;
		else if (s[i] == ')') deleting = false;
		else if (!deleting) retval.push_back(s[i]);
	}
	s = retval;
}

//Eliminate quotations between the end and the beginning, to remove informative lines in lyrics
void strip_quotations(std::string &s) {
	std::string retval;
	bool deleting = false;
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '"') deleting = true;
		else if (s[i] == '"') deleting = false;
		else if (!deleting) retval.push_back(s[i]);
	}
	s = retval;
}