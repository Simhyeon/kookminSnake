#include "commons.hpp"
#include <cmath>
#include <iostream>

RGB::RGB(unsigned char r,unsigned char g,unsigned char b) :r(r), g(g), b(b) {}

std::ostream& operator<<(std::ostream& os, RGB& rgb){
	os << "R : " << rgb.r << " G : " << rgb.g << " B : " << rgb.b << "\n";
	return os;
}

//RGG 클래스의 캐릭터 변환자
// 붉은색은 머리
// 파란색은 몸통
// 회색은 벽
// 검은색은 영구벽이다.
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
// Epoch 시간을 long 타입 밀리세컨드로 가져온다. 실제 시간이 필요하지 않기 때문에 변환하지는 않는다.
// std::chrono::seconds로 하면 초단위로 변환한다.
long Util::get_time() {
	auto now = std::chrono::system_clock::now();
    auto now_second = std::chrono::time_point_cast<std::chrono::milliseconds>(now); 
    auto value = now_second.time_since_epoch();
    long duration = value.count();
	return duration;
}
int Util::get_dir_int(DIRECTION dir){
	return static_cast<int>(dir);
}

// 방향을 정수형으로 변환한 뒤 -1 을 곱하면 반대 방향이 리턴된다.
DIRECTION Util::get_reverse_dir(DIRECTION direction){
	return static_cast<DIRECTION>(-1 * static_cast<int>(direction));
}

// 방향에 할당된 정수 값을 2로 모듈 연산을 한 값을 x에, 
// 2로 나눈값에 -를 곱한 값을 y 에 더하면 
// 해당 방향으로 1만큼 이동한 값을 알 수 있다.
Position Util::get_modified_pos(Position position, DIRECTION direction){
	int dirct = static_cast<int>(direction);
	position.increment(dirct%2, -dirct/2);
	return position;
}
// 순서대로 만든 배열내에서 주어진 방향의 위치를 찾고
// 해당 위치에서 우 또는 좌로 1만큼 옆에 있는 값이 
// 주어진 방향에서 우 또는 좌로 회전한 방향을 나타낸다.
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

// Position의 생성자
Position::Position(int x , int y): x_pos(x), y_pos(y){};
Position::Position(const Position& pos): x_pos(pos.get_x()), y_pos(pos.get_y()){};

std::pair<int, int> Position::get_position() {
	return std::pair<int, int>(x_pos,y_pos);
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

bool Position::operator==(const Position& pos) const{
	if (x_pos == pos.get_x() && y_pos == pos.get_y()){
		return true;
	} else {
		return false;
	}
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

// 두 좌표에서 x와 y의 차이를 절대값으로 바꾼뒤 
// 두 값을 더하면 맨해튼 거리를 구할 수 있다.
int Position::get_manhattan(const Position& pos) const{
	return std::abs(x_pos - pos.get_x() + y_pos - pos.get_y());
}

std::ostream& operator<<(std::ostream& os, const Position& pos){
	os << "Position: [X: " << pos.get_x() << " Y: " << pos.get_y() << "]";
	return os;
}
