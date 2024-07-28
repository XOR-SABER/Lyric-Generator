#include "headers/Markov_Chaining.hpp"

//Print Overload: Prints out the whole graph
std::ostream& operator<<(std::ostream &outs, const Markov_Chaining &m) {
	for (const Vertex &v : m.graph) {
		outs << v;
	}
	outs << "\n\tTotal Start Count: " << m.total_start_count << std::endl;
	return outs;
}

//Private function: Basically Turns the constructor into a overrated helper
bool Markov_Chaining::cache_check(const std::string &filename) {
	source_file = filename;
	reverse_parse_filename(source_file);
	std::string cache_file = "cache/";
	cache_file += source_file;

    std::ifstream cache(cache_file);
	if(cache) {
		std::string userinput;
		std::cout << "\tCache file detected, do you want to use it?" << std::endl;
		std::cout << "\tit skips pharsing, making it faster to generate songs." << std::endl;
		std::cout << "\tPlease skip if file has been changed since last used" << std::endl;
		std::cout << "\tY / N: ";
		std::cin >> userinput;
		std::cout << std::endl;
		uppercaseify(userinput);
		if(userinput == "YES" || userinput == "Y") {
			return true;
		}
	}
	return false;
}

void Markov_Chaining::build_graph(const std::string &filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "File: " << filename << " doesn't exist." << std::endl;
		exit(EXIT_FAILURE);
	}
	//Load text from the file - uppercase each word read
    while (true) {
		// Start of a new sentence.
		std::string s = tokenize(readline(file));
		if (!file) break;
		if (!s.size()) continue;
		std::stringstream sts(s);
		bool first_word = true;
		size_t last_index = INT_MAX;
		// We combining 
		if(!graph.empty()) {
			combined = true;
			last_index = graph.size()-1;
		}
		// Start of a new word.
		while (true) {
			bool comma_follows = false;
			std::string word = read(sts); // Read a word from the line
			if (!sts || !word.size()) break;
			while (word.size() && word.back() == ',') {
				comma_follows = true;
				word.pop_back();
			}
			// Drop other punctuation from the end of the word
			while (word.size() && ispunct(word.back())) word.pop_back();
			if (!word.size()) continue; //If nothing left continue
			// Look up index in the vector using a hash table
			size_t index = 0;
			// Exists already
			if (hash.count(word)) index = hash[word];
			else { // Make the new vertex
				graph.emplace_back(Vertex{word});
				index = graph.size()-1;
				hash[word] = index;
			}
			Vertex &v = graph.at(index); // Grab reference to current vertex or a pointer would work too
			v.count++; // We've seen it one more time
			if (comma_follows) v.comma_count++;
			if (first_word) {
				// There's no previous
				v.start_count++;
				total_start_count++;
				first_word = false;
				last_index = index;
			}
			else {
				// Check the previous
				Vertex &prev_v = graph.at(last_index);
				prev_v.total_edge_weight++;
				bool found = false;
				for (Edge &e : prev_v.edges) {
					if (e.word == word) {
						found = true;
						e.weight++;
						break;
					}
				}
				// Not found in edge adjacency list get pushed back idiot.
				if (!found) {
					prev_v.edges.push_back({word,1});
				}
				last_index = index;
			}
		}
	}
	file.close();
	// Sanity check that we read in at least one sentence
	if (!total_start_count) {
		std::cout << "No sentences read, exiting program" << std::endl;
		exit(1);
	}
}

// File Parsing AKA: Markovify
Markov_Chaining::Markov_Chaining(const std::string &filename) {
	// Check for cache! if cache exist and the user accepts stops the constructor
	if(cache_check(filename)) {
		recover_graph();
		return;
	}
	// Build the graph then!
	build_graph(filename);
}

// The Sentence generation, 
void Markov_Chaining::sentence_generation() {
		const int sentences = read("\tHow many sentences do you wish to make? ");
		const int64_t sneed = read("\tPlease enter the random seed: ");
			
		srand(sneed);

		for (int i = 0; i < sentences; i++) {
			//Let's roll, litterally..
			int roll = rand() % total_start_count; 
			Vertex cur;
			for (const Vertex &v : graph) {
				roll -= v.start_count;
				if (roll < 0) {
					cur = v;
					break;
				}
			}
			std::string temp = cur.word;
			first_cap(temp);
			std::cout << "\t" << temp;
			// Generate sentence, since we have to 
			while (true) {
				// Roll to see if we end the sentence here or pick a random word
				int end_count = cur.count - cur.total_edge_weight;
				roll = rand() % cur.count - end_count;
				// Check for end first
				if (roll < 0) {
					std::cout << "." << std::endl;
					break;
				}
				// Make a separate random roll to see if we should emit a comma
				int roll2 = rand() % cur.total_edge_weight - cur.comma_count;
				if (roll2 < 0) std::cout << ',';

				// If not the end, then randomly pick an edge to follow based on the weight
				// Uses the first random roll to go through the rest of the weight
				for (const Edge &e : cur.edges) {
					roll -= e.weight;
					if (roll < 0) {
						cur = graph.at(hash[e.word]);
						std::string s = cur.word;
						lowercaseify(s);
						std::cout << " " << s;
						break;
					}
				}
			}
		}
		std::cout << "\n";
}

void Markov_Chaining::save_file(){
	std::string new_file = "cache/";
	new_file += source_file;

	std::ofstream outs(new_file);

	// Very Simular to the overload for output
	for(const Vertex &v : graph) {
		outs << v.word << " " 
		<< v.count << " " 
		<< v.total_edge_weight << " " 
		<< v.start_count << " "
		<< v.comma_count << " ";
		for(const Edge &e : v.edges){
			outs << e.word << " " << e.weight << " ";
		}
		outs << std::endl;
	}

	outs << "TSC: " << total_start_count << std::endl;
	outs.close();
	screen_wipe();
	std::cout << "\tSaving complete\n";
}

void Markov_Chaining::recover_graph(){
	// Assumes this is a new graph
	std::string recovered_file = "cache/";
	recovered_file += source_file;

	std::ifstream file(recovered_file);
	int index = 0;
	while(true) {
		std::string temp = readline(file);
		if(!file) break;
		if(!temp.size()) continue;
		// Yeah I know this looks like a waste of memory. 
		std::stringstream sts(temp);
		std::string main_word = read(sts);
		if(main_word == "TSC:"){
			total_start_count = int(read(sts));
			break;
		}
		// We really don't need to check if any of the data is in invalid if we generate the data ourselves. 
		Vertex v {main_word, uint32_t(read(sts)), uint32_t(read(sts)), uint32_t(read(sts)), uint32_t(read(sts))};
		hash[main_word] = index;
		index++;
		// We getting edgy
		while(true){
			std::string edge_word = read(sts);
			if(edge_word.empty()) break;
			Edge e; 
			e.word = edge_word;
			e.weight = int(read(sts));
			v.edges.push_back(e);
			if(!sts) break;
		}
		graph.push_back(v);
	}
	// Sanity check that we read in at least one sentence
	if (total_start_count == 0) {
		std::cout << "\tNo sentences read, exiting program. . . . .." << std::endl;
		exit(1);
	}
}

void Markov_Chaining::stats_graph(){
	// THIS CODE IS GROSS, I HATE IT, AM GOING TO KILL YOU, GIVE ME $200
	// THIS CODE KILLED MY FAMILY, ALEX YOU DUMB FUCK PLEASE CHANGE THIS IN THE FUTURE. 
	// ~ Future Alex

	// This could be done at read time. 
	// Using Edges, since its already a custom data type that holds a string and integer value
	// most common word to begin with
	Edge common_beginning;
	common_beginning.word = graph[0].word;
	common_beginning.weight = graph[0].start_count;
	// most common edge
	Edge common_edge;
	common_edge.word = graph[0].edges[0].word;
	common_edge.weight = graph[0].edges[0].weight;
	// Has the most edges
	Edge greatest_weight; 
	greatest_weight.word = graph[0].word;
	greatest_weight.weight = graph[0].total_edge_weight;
	// most common word
	Edge common_word;
	common_word.word = graph[0].word;
	common_word.weight = graph[0].count;
	// most common ending word
	Edge common_ending; 
	common_ending.word = graph[0].word;
	common_ending.weight = (graph[0].count - graph[0].total_edge_weight);

	// Traverse and pick
	for(Vertex &v : graph) {
		if((v.count - v.total_edge_weight) > common_ending.weight) {
			common_ending.word = v.word;
			common_ending.weight = (v.count - v.total_edge_weight);
		}
		if(v.start_count > common_beginning.weight) {
			common_beginning.word = v.word;
			common_beginning.weight = v.start_count;
		}
		if(v.total_edge_weight > greatest_weight.weight) {
			greatest_weight.word = v.word;
			greatest_weight.weight = v.total_edge_weight;
		}
		if(v.count > common_word.weight) {
			common_word.word = v.word;
			common_word.weight = v.count;
		}
		for(Edge &e : v.edges) {
			if(e.weight > common_edge.weight) 
				common_edge.word = e.word, common_edge.weight = e.weight;
		}
	}


	std::cout << "\tThe most word with the most weight: '" << greatest_weight.word 
			  << "' with a total edge weight of: " << greatest_weight.weight << "!\n";
	std::cout << "\tThe most common beginning word: '" << common_beginning.word 
			  << "' with a start count of: " << common_beginning.weight << "!\n";
	std::cout << "\tThe most common ending word: '" << common_ending.word 
			  << "' with a count of: " << common_ending.weight << "!\n";
	std::cout << "\n\tThe most common word: '" << common_word.word 
			  << "' with a count of: " << common_word.weight << "!\n";
	std::cout << "\tThe most edge word: '" << common_edge.word 
			  << "' with a count of: " << common_edge.weight << "!\n\n";
}

void main_menu(Markov_Chaining &markov){
	bool breakLoop = true;
	while(breakLoop) {
		std::cout << "\t1. Print Graph\n";
		std::cout << "\t2. Generate Random Lyrics\n";
		std::cout << "\t3. Save graph\n";
		std::cout << "\t4. To clear the screen\n";
		std::cout << "\t5. Combine files\n";
		std::cout << "\t6. Show graph stats\n";
		std::cout << "\t7. Exit Program\n";
		int choice = read("\tSelect one of the options above: ");
		//
		switch (choice)
		{
			case 1:
				screen_wipe();
				std::cout << markov << std::endl;
				break;
			case 2:
				screen_wipe();
				markov.sentence_generation();
				break;
			case 3:
				markov.save_file();
				break;
			case 4:
				screen_wipe();
				break;
			case 5:
				markov.build_graph(filehandler());
				break;
			case 6:
				markov.stats_graph();
				break;
			case 7:
				std::cout << "\n\tExiting..." << std::endl;
				breakLoop = false;
				break;

			default:
				break;
		}
	}
}
