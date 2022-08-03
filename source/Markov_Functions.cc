#include "headers/Markov_Functions.hpp"
#include <iostream>
//Utility functions for changing the case on words

//Check for non-unicode characters
bool invalidChar (char c) { 
	return !(c>= 0 && c<128); 
}

void parse_filename(std::string &str) {
	std::string retval;
	int index = str.size() - 1;
	while (true) {
		if(str[index] == '/') {
			break;
		}
		retval.push_back(str[index]);
		index--;
	}
	reverse(retval.begin(), retval.end());
	str = retval;
}

//Gets rid of any and all Unicode Characters
void stripUnicode(std::string & str) { 
    str.erase(std::remove_if(str.begin(),str.end(), invalidChar), str.end());  
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
	if (!s.size()) return;
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
void logo(){
	std::cout << std::endl;
	std::cout << "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+" << std::endl;
	std::cout << "|  L    Y   Y RRRR  III  CCC      GGG  EEEE N   N EEEE RRRR   AA  TTTTTT  OOO  RRRR   |" << std::endl;
	std::cout << "|  L     Y Y  R   R  I  C        G     E    NN  N E    R   R A  A   TT   O   O R   R  |" << std::endl;
	std::cout << "|  L      Y   RRRR   I  C        G  GG EEE  N N N EEE  RRRR  AAAA   TT   O   O RRRR   |" << std::endl;
	std::cout << "|  L      Y   R R    I  C        G   G E    N  NN E    R R   A  A   TT   O   O R R    |" << std::endl;
	std::cout << "|  LLLL   Y   R  RR III  CCC      GGG  EEEE N   N EEEE R  RR A  A   TT    OOO  R  RR  |" << std::endl;
	std::cout << "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+" << std::endl;
	std::cout << std::endl;
}

void screen_wipe(){
	//Windows only lol!
	#if defined __WIN64__ || __WIN32__
	system("cls");
	logo();
	std::cout << "Windows Edtion! with 50% more developer!" << std::endl;
	#endif                                                                          
	
	//Linux only lol!
	#if defined __linux__
	if(system("clear")){}
	if(system("figlet -c lyric generator")){
		logo();
		std::cout << "Please Install Figlet!" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Chad developer friendly linux!" << std::endl;
	std::cout << std::endl;
	#endif

	#if defined __MACH__1 || __APPLE__1
	system("clear");
	logo();
	std::cout << std::endl;
	#endif     
}

std::string filehandler() {
	std::string fileSelection;
	
}