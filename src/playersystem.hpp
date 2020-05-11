#ifndef PLAYER_H
#define PLAYER_H

#include "commons.hpp"
#include "ecsdb.hpp"
#include "playerbody.hpp"

class PlayerBodySystem {
private:
	void change_direction(DIRECTION, PlayerBody&);
	void move(std::vector<PlayerBody>& bodies);
	std::pair<bool, DIRECTION> get_console_input(char);
public:
	void process(ECSDB&);
};

#endif
