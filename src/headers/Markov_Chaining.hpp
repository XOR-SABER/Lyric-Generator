#ifndef _ALEX_MARKOV_CHAINING
#define _ALEX_MARKOV_CHAINING

//Standard Headers
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <sstream>

//Custom Headers
#include "read.h"
#include "Vertex.hpp"
#include "Markov_Functions.hpp"
#include "String_Operations.hpp"

//OOP: Markov Chaining with adjacency list
class Markov_Chaining {
	private:
		std::unordered_map<std::string ,size_t> hash; //Holds the index (in vec) of each word we've read
		std::vector<Vertex> graph; //Holds each word and who it's connected to via adjacency list
		std::string source_file; //Holds the source of the file. 
		size_t total_start_count = 0; //Holds how many sentences we've read
		bool combined = false;
		bool cache_check(const std::string &);
	public:
		Markov_Chaining() = delete;
		Markov_Chaining(const std::string &);
		void save_file();
		void recover_graph();
		void build_graph(const std::string &);
		void stats_graph();
		void sentence_generation();
		size_t get_total_start_count() const { return total_start_count; }
		friend std::ostream &operator<<(std::ostream &outs, const Markov_Chaining &m);
};

//Function Prototypes:
void main_menu(Markov_Chaining&);
#endif