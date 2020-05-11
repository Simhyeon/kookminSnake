#ifndef COMMONS_H
#define COMMONS_H

#include <utility>

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

class Position{
	private:
		int x_pos;
		int y_pos;
	public:
		Position(int x, int y): x_pos(x), y_pos(y){};

		std::pair<int, int> get_position() {
			return std::pair<int, int>(x_pos,y_pos);
		}

		void modify(int x, int y) {
			x_pos += x;
			y_pos += y;
		}
};

#endif
