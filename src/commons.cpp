#include "commons.hpp"

int Util::get_rand(int min, int max){
	// srand((unsigned) time(0)); // 함수를 너무 빨리 부르면 시드가 변하지 않는다. 더 깔끔하게 해결할 것 
	return (rand() % max) + min;
}
long Util::get_time() {
	auto now = std::chrono::system_clock::now();
    auto now_second = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto value = now_second.time_since_epoch();
    long duration = value.count();
	return duration;
}

Position::Position(int x , int y): x_pos(x), y_pos(y){};

std::pair<int, int> Position::get_position() {
	return std::pair<int, int>(x_pos,y_pos);
}

// Temporary 
bool Position::operator==(const Position& pos) const{
	if (x_pos == pos.get_x() && y_pos == pos.get_y()){
		return true;
	} else {
		return false;
	}
}

const int Position::get_x() const{
	return x_pos;
}

const int Position::get_y() const{
	return y_pos;
}

void Position::increment(int x, int y) {
	x_pos += x;
	y_pos += y;
}
