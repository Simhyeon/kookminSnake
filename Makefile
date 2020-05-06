CC = g++
CCFLAG = -Wall -W
EXT = -lncurses
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=%.o)
TAR = Snake_game

${TAR} : ${OBJ}
	${CC} ${CCFLAG} $^ ${EXT} -o $@

%.o : %.cpp
	${CC} ${CCFLAG} -c $< -o $@

install :
	@cp -f ${TAR} ${HOME}/.local/bin/

uninstall :
	@rm -f $HOME/.local/bin/${TAR}

clean : 
	@rm -f *.o
