#include "headers/Markov_Chaining.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	std::string filename;
	//Check for Arguments
	if(argc > 1) {
		filename = argv[1];
	} else {
		//No Args?
		filename = filehandler();
	}
	// Just a function to wipe the screen
	screen_wipe();

	//Constructor for the program
	//init - initialize
	Markov_Chaining Markov(filename);
	
	//Menu function
	main_menu(Markov);
	return 0;
}
