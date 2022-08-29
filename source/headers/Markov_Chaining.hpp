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
		//TODO: Replace with custom chaining hash
		std::unordered_map<std::string ,size_t> hash; //Holds the index (in vec) of each word we've read
		std::vector<Vertex> graph; //Holds each word and who it's connected to via adjacency list
		std::string source_file; //Holds the source of the file. 
		long long total_start_count = 0; //Holds how many sentences we've read
		bool combined = false;
		bool cache_check(std::string);
	public:
		Markov_Chaining() = delete;
		Markov_Chaining(std::string);
		void save_file();
		void recover_graph();
		void build_graph(std::string);
		void stats_graph();
		void sentence_generation();
		long long get_total_start_count() { return total_start_count; }
		Vertex& operator[](size_t index);
		friend std::ostream &operator<<(std::ostream &outs, const Markov_Chaining &m);
};

//Function Prototypes:
void main_menu(Markov_Chaining&);
#endif