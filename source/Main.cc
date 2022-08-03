#include "headers/Markov_Chaining.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	std::string filename;
	// Just a function to wipe the screen
	screen_wipe();
	//File Handler function?
	if(argc > 1) {
		filename = argv[1];
	} else {
		cout << "Please enter a text file to open: ";
		cin >> filename;
		cout << endl;
	}

	Markov_Chaining Markov(filename);
	main_menu(Markov);
	return 0;
}