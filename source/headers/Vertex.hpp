#ifndef _ALEX_VERTEX
#define _ALEX_VERTEX

//Standard Headers
#include <string>
#include <vector>
#include <iostream>

//Custom data type: To hold words and weights 
struct Edge {
	std::string word; //The word we're connected to
	unsigned int weight = 0; //How often they follow us
};

//Adjacency List style graph
struct Vertex {
	std::string word; //What word this vertex corresponds to, like APPLE
	unsigned int count = 0; //How often this word came up
	unsigned int total_edge_weight = 0; //Total weight of the edges coming out of this vertex
	unsigned int start_count = 0; //How often this word starts a sentence
	unsigned int comma_count = 0; //How often the word has a comma following it
	std::vector<Edge> edges; //Holds the words we're connected to, and how often they follow us, like {PEAR,3}
};

//Overloads,
std::ostream &operator<<(std::ostream &outs,const Edge &e);
std::ostream &operator<<(std::ostream &outs,const Vertex &v);
#endif