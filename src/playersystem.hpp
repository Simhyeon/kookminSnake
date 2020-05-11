#ifndef PLAYER_H
#define PLAYER_H

#include "commons.hpp"
#include "ecsdb.hpp"

class PlayerBodySystem {
private:
	void change_direction(DIRECTION direction);
	void move();
	void get_console_input(ECSDB&);
public:
	void process(ECSDB&);
};

#endif
