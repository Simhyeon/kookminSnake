#ifndef PLAYER_H
#define PLAYER_H

#include "commons.hpp"
#include <vector>

// 이 방향을 이넘 클래스가 아니라 그냥 x,y 좌표로 구현하는게 더 이득이긴 하다. 직관성은 떨어지지만
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
	void add_body(); // This might be complex
public:
	PlayerBody();
friend class PlayerBodySystem;
};

class PlayerBodySystem {
private:
	PlayerBody player;

	void change_direction(DIRECTION direction);
	void move();
	Position peak_move() const;
	void rotate(KEYINPUT rotation);
	void get_item();
public:
	void process(char input);
};

#endif
