#include "headers/Markov_Chaining.hpp"
//Index Overload: Gets the value at a index using the [] operator
Vertex& Markov_Chaining::operator[](size_t index) {
	return graph.at(index);
}

//Print Overload: Prints out the whole graph
std::ostream& operator<<(std::ostream &outs, const Markov_Chaining &m) {
	for (const Vertex &v : m.graph) {
		outs << v;
	}
	outs << "Total Start Count: " << m.total_start_count << std::endl;
	return outs;
}

//File Parsing AKA: Markovify
Markov_Chaining::Markov_Chaining(std::string filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cout << "File: " << filename << " doesn't exist." << std::endl;
		exit(EXIT_FAILURE);
	}

	//Load text from the file - uppercase each word read
	source_file = filename;
	parse_filename(source_file);
	std::string cache_file = "cache/";
	cache_file += source_file;

    std::ifstream cache(cache_file);
	if(cache) {
		std::string userinput;
		std::cout << "Cache file detected, do you want to use it?" << std::endl;
		std::cout << "it skips pharsing, making it faster to generate songs." << std::endl;
		std::cout << "Please skip if file has been changed since last used" << std::endl;
		std::cout << "Y / N: ";
		std::cin >> userinput;
		uppercaseify(userinput);
		if(userinput == "YES" || userinput == "Y") {
			recover_graph();
			return;
		}
	}
    
    while (true) {
		std::string s = readline(file);
		uppercaseify(s);
		stripUnicode(s);
		strip_brackets(s);
		strip_parenthesis(s); 
		if (!file) break;
		if (!s.size()) continue;
		std::stringstream sts(s);
		bool first_word = true;
		size_t last_index = INT_MAX;
		while (true) {
			bool comma_follows = false;
			std::string word = read(sts); //Read a word from the line
			if (!sts || !word.size()) break;
			while (word.size() && word.back() == ',') {
				comma_follows = true;
				word.pop_back();
			}
			if(word.back() == '"'){
				word.pop_back();
			}
			if(word.front() == '"'){
				word.erase(0,1);
			}
			while (word.size() && ispunct(word.back())) //Drop other punctuation from the end of the word
				word.pop_back();
			if (!word.size()) continue; //If nothing left continue

			//Look up index in the vector using a hash table
			size_t index = 0;
			if (hash.count(word)) { //Exists already
				index = hash[word];
			}
			else { //Make the new vertex
				Vertex v = {word};
				graph.push_back(v);
				index = graph.size()-1;
				hash[word] = index;
			}
			Vertex &v = graph.at(index); //Grab reference to current vertex.
			v.count++; //We've seen it one more time
			if (comma_follows) v.comma_count++;
			if (first_word) {
				v.start_count++;
				total_start_count++;
				first_word = false;
				last_index = index;
			}
			else {
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
				if (!found) {
					prev_v.edges.push_back({word,1});
				}
				last_index = index;
			}
		}
	}
	//Sanity check that we read in at least one sentence
	if (total_start_count == 0) {
		std::cout << "No sentences read, exiting program" << std::endl;
		exit(1);
	}
}
//The Sentence generation, 
void Markov_Chaining::sentence_generation(){
		const int sentences = read("How many sentences do you wish to make?\n");
		const int64_t sneed = read("Please enter the random seed:\n");
			
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
			std::cout << temp;
			//Generate sentence, since we have to 
			while (true) {
				//Roll to see if we end the sentence here or pick a random word
				int end_count = cur.count - cur.total_edge_weight;
				roll = rand() % cur.count - end_count;
				//Check for end first
				if (roll < 0) {
					std::cout << "." << std::endl;
					break;
				}
				//Make a separate random roll to see if we should emit a comma
				int roll2 = rand() % cur.total_edge_weight - cur.comma_count;
				if (roll2 < 0) std::cout << ',';

				//If not the end, then randomly pick an edge to follow based on the weight
				//Uses the first random roll to go through the rest of the weight
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
}

void Markov_Chaining::save_file(){
	std::string new_file = "cache/";
	new_file += source_file;

	std::ofstream outs(new_file);

	//Very Simular to the overload for output
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
	outs << "TSC: 8";
	outs << std::endl;
	outs.close();
	std::cout << "Saving complete\n";
}
void Markov_Chaining::recover_graph(){
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
		Vertex v;
		v.word = main_word;
		v.count = int(read(sts));
		v.total_edge_weight = int(read(sts));
		v.start_count = int(read(sts));
		v.comma_count = int(read(sts));
		hash[main_word] = index;
		index++;
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
	//Sanity check that we read in at least one sentence
	if (total_start_count == 0) {
		std::cout << "No sentences read, exiting program" << std::endl;
		exit(1);
	}
}
void main_menu(Markov_Chaining &markov){
	bool breakLoop = true;
	while(breakLoop) {
		std::cout << "1. Print Graph and Quit\n";
		std::cout << "2. Generate Random Lyrics\n";
		std::cout << "3. Save graph\n";
		std::cout << "4. To clear the screen\n";
		std::cout << "5. Exit Program\n";
		int choice = read("Select one of the options above: ");
		switch (choice)
		{
			case 1:
				std::cout << markov << std::endl;
				break;
			case 2:
				markov.sentence_generation();
				break;
			case 3:
				markov.save_file();
				break;
			case 4:
				screen_wipe();
				break;
			case 5:
				std::cout << "Exiting" << std::endl;
				breakLoop = false;
				break;
			default:
				break;
		}
	}
}