#include "playerbody.hpp"
#include "commons.hpp"
#include <iostream>

PlayerBody::PlayerBody(){}
PlayerBody::PlayerBody(Position position, DIRECTION direction, unsigned int body_size){
	pos = position;
	dir_queue = std::deque<DIRECTION>(std::queue<DIRECTION>::container_type(body_size, direction));
	last_direction = direction;
}
PlayerBody::PlayerBody(Position position, std::deque<DIRECTION> copy){
	pos = position;
	dir_queue = copy;
}
const DIRECTION PlayerBody::get_direction() const{
	return dir_queue.front();
}

DIRECTION PlayerBody::pop_direction(){
	DIRECTION dir = dir_queue.front();
	dir_queue.pop_front();
	return dir;
}

void PlayerBody::push_direction(DIRECTION dir){
	dir_queue.push_back(dir);
}

void PlayerBody::push_direction_front(DIRECTION dir){
	dir_queue.push_front(dir);
}
const Position PlayerBody::get_pos() const{
	return pos;
}
void PlayerBody::increment_pos(int x, int y){
	pos.increment(x, y);
}
void PlayerBody::set_pos(const Position position){
	pos = position;
}
void PlayerBody::set_pos(int x, int y){
	pos = Position(x,y);
}
const std::deque<DIRECTION>& PlayerBody::get_dir_queue() const{
	return dir_queue;
}
DIRECTION PlayerBody::get_last_dir() const{
	return last_direction;
}
void PlayerBody::set_last_dir(DIRECTION dir){
	last_direction = dir;
}
