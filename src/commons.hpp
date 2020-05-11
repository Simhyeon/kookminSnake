#ifndef COMMONS_H
#define COMMONS_H

#include <utility>
#include <vector>

enum class DIRECTION{
	UP = 2,
	RIGHT = 1,
	DOWN = -2,
	LEFT = -1
};

// 2 -> 0, 1 : value/2(0) -> y, value %2(1) | -> x; -=value/2 , -=value%2 * 3 
// 1 -> 1, 0 value/2 -> y, value %2 		|-> x; -=value/2 , -=value%2 * 3
// -2 -> 0 -1
// -1 -> -1 0
enum class KEYINPUT{
	RIGHT = -1,
	LEFT = 1,
};

// Consider making assignment operator and comparison operator.
class Position{
	private:
		int x_pos;
		int y_pos;
	public:
		Position(int x = 0, int y = 0): x_pos(x), y_pos(y){};

		std::pair<int, int> get_position() {
			return std::pair<int, int>(x_pos,y_pos);
		}

		bool operator==(Position& pos){
			if (x_pos == pos.get_x() && y_pos == pos.get_y()){
				return true;
			} else {
				return false;
			}
		}

		bool operator==(const Position& pos){
			if (x_pos == pos.get_x() && y_pos == pos.get_y()){
				return true;
			} else {
				return false;
			}
		}

		// Make this operator complete
//		Position operator+=(const Position& pos){
//			
//		}

		int get_x() const{
			return x_pos;
		}
		int get_y() const{
			return y_pos;
		}

		void increment(int x, int y) {
			x_pos += x;
			y_pos += y;
		}
};

// Aliases
using PosVc=std::vector<Position>;

#endif
