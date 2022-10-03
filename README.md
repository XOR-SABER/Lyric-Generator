# Lyric Generator
A Markov Chain is a type of graph in which each vertex represents a word, and
the edges (directed and weighted) coming out of each vertex indicate how often
the other word came from that word. We load the graph using data from a corpus
of text, and the graph we get at the end of it can be used to generate new
sentences in the style of whatever we trained it with.

### I loaded 1500 lines of Wu-Tang lyrics and got the following results:
- "My glock like Voltron."
- "Bring da mother, bring da mother, bring it was kickin rhymes like ya Meth hittin caps on the GZA."
- "Diluted, broken down, your Wu is smokey bear when he don't need that Wu-Tang style."
- "Choppin' through your problems the gods are hotter than heavy metal frame."
- "Stop quick hold us so grab your whole era."

### Training it on the Declaration of Independence, I got this monster of a sentence out:
- "He has endeavoured to the lives our separation, and of English laws of our
trade with his assent to our constitution, and hold them, to dissolve the
supreme judge of immediate and payment of consanguinity we therefore, the most
wholesome and magnanimity, and the people and accordingly all men deriving
their country, to the conditions of right do all allegiance to attend to the
inhabitants of fatiguing them of an unwarrantable jurisdiction foreign
mercenaries to all experience hath shewn, that governments."

### Fun stuff!

You have to do the following for this assignment:
1. Load data from disk into a graph (5 points)
2. Generate Random Sentences (5 points)

## Part 1 - Loading Data (5 points)

You need to build a graph (I created a couple sample classes and data
structures for you, but you can discard them if you are feeling lucky) using
the data loaded from disk. You'll load one line at a time from the file using
getline (or readline if you like my read library) and then read one word at a
time from that line. The first word needs to be noted that it was the first
word in a sentence, so that you have a starting point for generating random
sentences. You can also record if it ends a line, if you like, though it's not
necessary.

Then as you read one word at a time in from the line, every word that follows
another word creates an edge between them with weight 1 (if there was no edge
before) or increases the existing edge weight by one if it is a duplicate.

Uppercaseify all inputs, so Tomato and TOMATO and tomato are the same.

### For example:
- APPLE TOMATO
- Apple TOMATO
- TOMATO APPLE
- TOMATO PEACH

#### Will create a graph that looks like this:
<pre>
       2          1
APPLE --> TOMATO --> PEACH
       1
	  <--
</pre>

APPLE started two lines, TOMATO started two lines. TOMATO ended two lines,
APPLE ended one line, PEACH ended one line.

## Part 2 - Generating Random Sentences (4 points)

So let's say you're ready to generate a random sentence. There were 4 lines in
the input file, so you will do a "int roll = rand() % 4" to get a number from
0 to 3. You then will go through each vertex in the graph (in the order they
were entered, DON'T MESS WITH THE ORDERING) and subtract off the start_count
of each vertex. If the roll is then negative, that's your start. For example,
say you rolled a 2.
The first element in the graph is APPLE, APPLE has a start_count of 2, so the
roll is reduced by 2 to 0. 0 is not negative, so we keep going. We get to
TOMATO next, which also has a start count of 2, so we subtract off 2 from
roll, giving us -2. This means that TOMATO is the start of the sentence.

Cool. So we output "Tomato" to the screen.

Next, we need to figure out what word comes next. Tomato appeared 4 times in
the input, 2 times as the end of a sentence (50% chance), and 2 times leading
to other words (25% chance of APPLE, 25% chance of PEACH). So let's say we
roll another die, modulus the number of times TOMATO appears (4), and we get a 3.
We subtract off the number of times it ends a sentence, and the roll is now 1.
We subtract off the number of times APPLE follows from TOMATO, and we now
have 0. This is still not negative, so we continue. We subtract 1 off for
PEACH (since PEACH comes from TOMATO one time) and it goes negative, and so
PEACH is our next node in the graph. 

Cool. So we output " peach" to the screen, and continue with peach as the
current node in the graph.

PEACH appears one time in the graph, and so we roll rand() % 1, giving us
zero. We start by subtracting the number of times PEACH ended a sentence (1),
giving us a negative number. So that's our choice. We output ".\n" and are
done with this sentence.

Move on to the next sentence, and you'll all done.

Good luck! Lol.