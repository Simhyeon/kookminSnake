#include "playerbody.hpp"
#include "commons.hpp"

PlayerBody::PlayerBody(){}
PlayerBody::PlayerBody(DIRECTION dir, Position position){
	direction = dir;
	pos = position;
}
const DIRECTION PlayerBody::get_direction(){
	return direction;
}
void PlayerBody::set_direction(DIRECTION dir){
	direction = dir;
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
