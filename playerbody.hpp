#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include "commons.hpp"


class PlayerBody{
private:
	DIRECTION direction;
	Position pos;
public:
	PlayerBody();
	DIRECTION get_direction();
	Position get_pos();
};

#endif
