#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include "commons.hpp"
#include <queue>

class PlayerBody{
private:
	std::deque<DIRECTION> dir_queue;
	Position pos;
	DIRECTION last_direction;
public:
	PlayerBody();
	PlayerBody(Position, DIRECTION direction, unsigned int body_size);
	PlayerBody(Position, std::deque<DIRECTION> copy);
	const DIRECTION get_direction() const;
	DIRECTION pop_direction();
	void push_direction(DIRECTION);
	void push_direction_front(DIRECTION dir);
	const Position get_pos() const;
	void increment_pos(int x, int y);
	void set_pos(const Position);
	void set_pos(int x, int y);
	DIRECTION get_last_dir() const;
	void set_last_dir(DIRECTION);

	const std::deque<DIRECTION>& get_dir_queue() const;
};

#endif
