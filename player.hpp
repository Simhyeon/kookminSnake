#ifndef PLAYER_H
#define PLAYER_H

#include "commons.hpp"
#include "item.hpp"
#include "wall.hpp"
#include "physics.hpp"
#include <vector>

enum class DIRECTION{
	UP = 2,
	RIGHT = 1,
	DOWN = -2,
	LEFT = -1
};
// 2 -> 0, 1 : value/2(0) -> y, value %2(1) -> x; -=value/2 , -=value%2 * 3 
// 1 -> 1, 0 value/2 -> y, value %2 -> x; -=value/2 , -=value%2 * 3
// -2 -> 0 -1
// -1 -> -1 0
enum class KEYINPUT{
	RIGHT = -1,
	LEFT = 1,
};

class PlayerBody {
private:
	DIRECTION direction;
	std::vector<Position> body;
	void add_body(); 
public:
	PlayerBody();
friend class PlayerBodySystem;
};

class PlayerBodySystem {
private:
	PlayerBody player;

	void change_direction(DIRECTION direction);
	void move();
	void move(Position);
	void rotate(KEYINPUT rotation);
	void change_length();
public:
	void c_input();
	Position peak_move() const;
	void procede(Collision);
};

#endif
