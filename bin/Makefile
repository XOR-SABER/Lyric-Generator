CC = g++ 
CC_FLAGS_DEBUG = -Wall -Wextra -pedantic 
CC_FLAGS_DEBUG2 = -Wshadow  -Wunreachable-code
SANITIZE = -fsanitize=address -g
CC_FLAGS = -std=c++2a
SC = ../src/
PROG = LyricGen

all:
	${CC} ${CC_FLAGS} -g ${SC}*.cc -o ${PROG}
debug:
	${CC} ${CC_FLAGS} ${CC_FLAGS_DEBUG} ${CC_FLAGS_DEBUG2} ${SC}*.cc -o ${PROG}
s:
	${CC} ${CC_FLAGS} ${SANITIZE} ${SC}*.cc -o ${PROG}

clean:
	rm *.o
	rm ${PROG}