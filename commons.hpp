#ifndef COMMONS_H
#define COMMONS_H

#include <utility>

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
