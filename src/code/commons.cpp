#include "commons.hpp"
#include <cmath>
#include <iostream>

RGB::RGB(unsigned char r,unsigned char g,unsigned char b) :r(r), g(g), b(b) {}

std::ostream& operator<<(std::ostream& os, RGB& rgb){
	os << "R : " << rgb.r << " G : " << rgb.g << " B : " << rgb.b << "\n";
	return os;
}

//For Debugging
RGB::operator char(){
	if (r == 205 &&
	g == 66 &&
	b == 66){
		return '@';
	} else if (r == 68 &&
	g == 66 &&
	b == 205) {
		return '#';
	} else if (r == 169 &&
	g == 169 &&
	b == 169) {
		return '*';
	} else if (r == 0 &&
	g == 0 &&
	b == 0) {
		return 'H';
	} else {
		return '`';
	}
}

bool operator==(RGB& lhs, RGB& rhs){
	return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b);
}

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
DIRECTION Util::get_reverse_dir(DIRECTION direction){
	return static_cast<DIRECTION>(-1 * static_cast<int>(direction));
}
Position Util::get_modified_pos(Position position, DIRECTION direction){
	int dirct = static_cast<int>(direction);
	position.increment(dirct%2, -dirct/2);
	return position;
}
DIRECTION Util::rotate_dir(DIRECTION origin, DIRECTION rotation){
	auto it = std::find(dir_array.begin(), dir_array.end(), Util::get_dir_int(origin));
	if (rotation == DIRECTION::RIGHT){
		if (it == dir_array.end()-1){
			return static_cast<DIRECTION>(*(dir_array.end()));
		} else {
			return static_cast<DIRECTION>(*(it+1));
		}
	} else if (rotation == DIRECTION::LEFT) {
		if (it == dir_array.begin()){
			return static_cast<DIRECTION>(*(dir_array.end()-1));
		} else {
			return static_cast<DIRECTION>(*(it-1));
		}
	} else {
		throw std::exception();
	}
}
std::array<int, 4> Util::dir_array = {2,1,-2,-1};

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