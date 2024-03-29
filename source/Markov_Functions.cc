#include "headers/Markov_Functions.hpp"
#include "headers/read.h"

//Utility functions for changing the case on words

// Any way fuck that helper function, here's the O(N) one
std::string tokenize(const std::string &str) {
	std::string retval;
	retval.reserve(str.size());
	bool deleting = false;
	for (size_t i = 0; i < str.size(); i++) {
		switch (str[i]) {
			case '[':
			case '(':
				deleting = true;
				break;
			case ']':
			case ')':
				deleting = false;
				break;
		}
		if (!deleting){
			if(str[i] == '"') continue;
			if(!invalidChar(str[i])) {
			retval.push_back(std::toupper(str[i]));
			}
		}
	}
	return retval;
}

//Turn misc/mario.txt -> misc/
void parse_path(std::string &str) {
	std::string retval;
	int index = 0;
	while (true) {
		if(str[index] == '/') {
			retval.push_back(str[index]);
			break;
		}
		retval.push_back(str[index]);
		index++;
	}
	str = retval;
}

//Turn misc/mario.txt -> mario.txt
void reverse_parse_filename(std::string &str) {
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


//The logo if figlet is not installed on the local machine (ie: Windows and Mac and some unix machines)
const void logo(){
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

std::string filehandler() {
	//File handling using #include <filesystem>
	//Pro tip: Don't use std:: when not in main.
	namespace fsys = std::filesystem;

	//Slightly Wasteful of memory
	std::vector<fsys::path> paths_list; 
	std::vector<fsys::path> previous;

	//Casting
	fsys::path cast{fsys::current_path()};
	std::string path{cast.string()};
	path =+"lyrics/";

	//Looping iteration:


	bool nested = false;
	//o(n^2) but this is a interface so who cares? 
	cast = path;
	while(true) {
		//Declarations
		if(previous.empty()) nested = false;
		screen_wipe();
		unsigned int file_number = 0, input = 0; 
		paths_list.clear();
		std::cout << "\tCurrent Directory: " << path << std::endl;
		//List all the directories 
		for(auto &A : fsys::directory_iterator(path)) {
			std::cout << "\t" << file_number <<  ": "<< A.path() << std::endl;
			paths_list.push_back(A.path());
			file_number++;
		}
		if(nested) {
			//Are we in a directory?
			//Then list it
			std::cout << "\t" << file_number << ": Return to the previous directory" << std::endl;
		}
		input = read("\n\tSelect one of the options above: ");
		if(input >= file_number && nested) {
			//If we are in a directory and the input is greater or equal to the file number
			cast = previous.back();
			previous.pop_back();
			std::string reval{cast.string()};
			path = reval;
			continue;
		} else if (input < file_number) {
			//Change to a file or directory
			previous.push_back(cast);
			cast = paths_list.at(input);
			std::string reval{cast.string()};
			if(fsys::is_directory(cast)) {
				reverse_parse_filename(reval);
				std::cout << reval << std::endl;
				path = path + reval;
				nested = true;
			} else if(fsys::is_regular_file(cast)) {
				return reval;
			}
		} else {
			//A catch all
			continue;
		}
		
	}
	return "";
}


//Wipes the Screen and displays the logo
const void screen_wipe(){
	//Windows only lol!
	#if defined __WIN64__ || __WIN32__
	system("cls");
	logo();
	std::cout << "\tWindows Edtion! with 50% more developer!" << std::endl;
	#endif                                                                          
	
	//Linux only lol!
	#if defined __linux__
	if(system("clear")){}
	if(system("figlet -c lyric generator")){
		logo();
		std::cout << "\tPlease Install Figlet!" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "\tChad developer friendly linux!" << std::endl;
	std::cout << std::endl;
	#endif

	#if defined __MACH__1 || __APPLE__1
	system("clear");
	logo();
	std::cout << std::endl;
	#endif     
}

