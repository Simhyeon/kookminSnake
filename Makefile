CC := g++
CFLAG := -Wall -W
LDLIBS := -lncurses
SRC_DIR := src
OBJ_DIR := obj
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXE := Snake_game

all: clean $(EXE)

${EXE} : ${OBJ}
	${CC} ${CFLAG} $^ ${LDLIBS} -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	${CC} ${CFLAG} -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

install :
	@cp -f ${EXE} ${HOME}/.local/bin/

uninstall :
	@$(RM) $(HOME)/.local/bin/${EXE}

clean : 
	@$(RM) -r $(OBJ_DIR)

.PHONY: all clean
