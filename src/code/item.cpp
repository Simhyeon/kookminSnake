#include "item.hpp"
#include "commons.hpp"

Item::Item(): timestamp(Util::get_time()){}
Item::Item(Position pos): timestamp(Util::get_time()), pos(pos) {}

long Item::get_time(){
	return timestamp;
}

Position Item::get_pos(){
	return pos;
}

bool Item::operator==(const Item& rhs) const{
	return timestamp == rhs.timestamp && pos == rhs.pos;
}
