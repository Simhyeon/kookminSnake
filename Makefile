CC := g++
CFLAG := 
DFLAG := -Wall -W -g
LDLIBS := -lncurses
SRC_DIR := src/code
OBJ_DIR := obj
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXE := Snake_game
DEBUG := Snake_game_Debug

all: $(EXE)

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

Debug : clean $(DEBUG)

${DEBUG} : ${OBJ}
	${CC} ${DFLAG} $^ ${LDLIBS} -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	${CC} ${DFLAG} -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

.PHONY: all clean Debug
