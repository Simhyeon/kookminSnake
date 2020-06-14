CC := g++
CFLAG := -w
LDLIBS := -lncurses -lyaml-cpp
SRC_DIR := src/code
OBJ_DIR := obj
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
EXE := Snake_game
DEBUG := Snake_game_Debug
DEP := libncurses5-dev libncursesw5-dev libyaml-cpp-dev libyaml-cpp0.5v5
all: env $(EXE)

${EXE} : ${OBJ} 
	@${CC} ${CFLAG} $^ ${LDLIBS} -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@${CC} ${CFLAG} -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

env :
	@echo "Installing prerequisites"
	sudo add-apt-repository universe
	sudo apt-get update
	sudo apt-get install -y ${DEP}
	@echo "Compiling ....(Take up to several seconds)"

install :
	@cp -f ${EXE} ${HOME}/.local/bin/

uninstall :
	@$(RM) $(HOME)/.local/bin/${EXE}

clean : 
	@$(RM) -r $(OBJ_DIR)

.PHONY: all clean Debug env
