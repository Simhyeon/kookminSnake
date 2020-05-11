#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include "commons.hpp"


class PlayerBody{
private:
	DIRECTION direction;
	Position pos;
public:
	PlayerBody();
	PlayerBody(DIRECTION, Position);
	const DIRECTION get_direction();
	void set_direction(DIRECTION);
	const Position get_pos();
	void increment_pos(int x, int y);
	void set_pos(const Position);
	void set_pos(int x, int y);
};

#endif
