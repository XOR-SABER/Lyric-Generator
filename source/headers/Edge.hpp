#ifndef _ALEX_EDGE
#define _ALEX_EDGE
#include <string>

struct Edge {
	std::string word; //The word we're connected to
	int weight = 0; //How often they follow us
};

#endif