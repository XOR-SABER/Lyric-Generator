# Lyric Generator

<img src="imgs\img1.png"></img>

Lyric Generator is a C++ program, that takes a .txt file of lyrics and generates 
a new set of lyrics using markov chains. 

## What is a markov chain 

A Markov Chain is a type of graph in which each vertex represents a word, and
the edges (directed and weighted) coming out of each vertex indicate how often
the other word came from that word. We load the graph using data from a corpus
of text, and the graph we get at the end of it can be used to generate new
sentences in the style of whatever we trained it with.

<img src="imgs\MarkovDiagram.png"></img>

Markov chain is a specific type of finite state machine that is used to model 
probabilistic processes. Both Markov chains and finite state machines have a 
finite set of states and transitions between those states, but the difference 
is in how the transitions are determined.

Each node is created using these two structs, Edge and Vertex. 

```C++
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
```

### I loaded 500 lines of hyperpop lyrics and got this beautiful gem. 
- "I'M POGGERS."
- "I THOUGHT SOMEONE ELSE WAS ALL SNUGGLY."
- "NOW, NOW."
- "HIT THE BIG BOYS COMING WITH THE PAST FEW REASONS."
- "FANDOM WITH THE PICTURE."
- "BUT I GO INSANE RIGHT NOW, NOW."
- "GRASSI, GRASSI, GRASSI, THATS THAT FIFTH DIMENSION FOUR, I GOTTA GO, TO ROLEPLAY AND POPPERS."
- "BUT I JUST WANT YOU SEE."
- "I RIDE."
- "I GO GO ON YOUR RIDE."

The bigger the data set, the better the lyrics. Pretty intresting right, but what 
does this program actually do. 

#### The program can preform the following tasks: 
1. Load data from disk into a graph
2. Generate Random Sentences
3. Generate a cache file for quick data storage
4. Generate stats for the graph
5. Implement using object oriented programming
6. Implement operator overloading 
7. use #include "filesystem"
8. Combine graphs
9. Use a graph with adjacency lists
10. Generate lyrics using probablity

## Part 1 - Loading Data

You need to build a graph (I created a couple sample classes and data
structures for you, but you can discard them if you are feeling lucky) using
the data loaded from disk. You'll load one line at a time from the file using
getline (or readline if you like my read library) and then read one word at a
time from that line. The first word needs to be noted that it was the first
word in a sentence, so that you have a starting point for generating random
sentences. You can also record if it ends a line, if you like, though it's not
necessary.

So, this goes into a lot of string manipulation, I even made a header called 
String_Operations.hpp to help with this process. 

I feel like knowing regex, make the time complexity of the tokenization 
process a bit faster. 

So the process goes like this, 
1. Take a whole line.
2. Strip all Quotations, Brackets, parentheses.
3. Remove punctuation, commas, periods, exclmation points, etc.
4. Keep track if it has a comma with comma count, and if it starts or ends a sentance. 
5. Put it in a associative array (Hash Table), to keep duplicates out.



Then as you read one word at a time in from the line, every word that follows
another word creates an edge between them with weight 1 (if there was no edge
before) or increases the existing edge weight by one if it is a duplicate.

Uppercaseify all inputs, so Tomato and TOMATO and tomato are the same.

### For example:
- APPLE TOMATO
- Apple TOMATO
- TOMATO APPLE
- TOMATO PEACH