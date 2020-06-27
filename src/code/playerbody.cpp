/**
 * @file playerbody.cpp
 *
 * @author 육심현(20150803)
 *
 */

#include "playerbody.hpp"
#include "commons.hpp"
#include <iostream>

/// @author 육심현(20150803)
PlayerBody::PlayerBody(){}
/// @author 육심현(20150803)
PlayerBody::PlayerBody(Position position, DIRECTION direction, unsigned int body_size){
	pos = position;
	dir_queue = std::deque<DIRECTION>(std::queue<DIRECTION>::container_type(body_size, direction));
	last_direction = direction;
}
/// @author 육심현(20150803)
PlayerBody::PlayerBody(Position position, std::deque<DIRECTION> copy){
	pos = position;
	dir_queue = copy;
}
/// @author 육심현(20150803)
const DIRECTION PlayerBody::get_direction() const{
	return dir_queue.front();
}
/// @author 육심현(20150803)
DIRECTION PlayerBody::pop_direction(){
	DIRECTION dir = dir_queue.front();
	dir_queue.pop_front();
	return dir;
}
/// @author 육심현(20150803)
void PlayerBody::push_direction(DIRECTION dir){
	dir_queue.push_back(dir);
}
/// @author 육심현(20150803)
void PlayerBody::push_direction_front(DIRECTION dir){
	dir_queue.push_front(dir);
}
/// @author 육심현(20150803)
const Position PlayerBody::get_pos() const{
	return pos;
}
/// @author 육심현(20150803)
void PlayerBody::increment_pos(int x, int y){
	pos.increment(x, y);
}
/// @author 육심현(20150803)
void PlayerBody::set_pos(const Position position){
	pos = position;
}
/// @author 육심현(20150803)
void PlayerBody::set_pos(int x, int y){
	pos = Position(x,y);
}
/// @author 육심현(20150803)
const std::deque<DIRECTION>& PlayerBody::get_dir_queue() const{
	return dir_queue;
}
/// @author 육심현(20150803)
DIRECTION PlayerBody::get_last_dir() const{
	return last_direction;
}
/// @author 육심현(20150803)
void PlayerBody::set_last_dir(DIRECTION dir){
	last_direction = dir;
}
