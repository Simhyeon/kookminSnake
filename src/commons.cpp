#include "commons.hpp"
#include <cmath>
#include <iostream>

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
int Util::get_dir_int(DIRECTION dir){
	return static_cast<int>(dir);
}

Position::Position(int x , int y): x_pos(x), y_pos(y){};
Position::Position(const Position& pos): x_pos(pos.get_x()), y_pos(pos.get_y()){};

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

int Position::get_x() const{
	return x_pos;
}

int Position::get_y() const{
	return y_pos;
}

void Position::increment(int x, int y) {
	x_pos += x;
	y_pos += y;
}

Position& Position::operator=(const Position& pos){
	x_pos = pos.get_x();
	y_pos = pos.get_y();
	return *this;
}

Position& Position::operator+=(const Position& pos){
	x_pos = x_pos + pos.get_x();
	y_pos = y_pos + pos.get_y();
	return *this;
}

int Position::get_manhattan(const Position& pos) const{
	return std::abs(x_pos - pos.get_x() + y_pos - pos.get_y());
}

std::ostream& operator<<(std::ostream& os, const Position& pos){
	os << "Position: [X: " << pos.get_x() << " Y: " << pos.get_y() << "]";
	return os;
}
