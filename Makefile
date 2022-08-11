CC = g++ 
CC_FLAGS = -std=c++2a -O3 
CLS = clear
SC = source/
OBJ = source/objects/

all:
	${CC} ${CC_FLAGS} -c ${SC}*.cc
	${CC} ${CC_FLAGS} -o Markov *.o

clean:
	rm *.o
	rm Markov