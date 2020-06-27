/**
 * @file item.cpp
 *
 * @author 육심현(20150803)
 *
 */

#include "item.hpp"
#include "commons.hpp"

/// @author 육심현(20150803)
Item::Item(): timestamp(Util::get_time()){}
/// @author 육심현(20150803)
Item::Item(Position pos): timestamp(Util::get_time()), pos(pos) {}
/// @author 육심현(20150803)
long Item::get_time(){
	return timestamp;
}
/// @author 육심현(20150803)
Position Item::get_pos(){
	return pos;
}
/// @author 육심현(20150803)
bool Item::operator==(const Item& rhs) const{
	return timestamp == rhs.timestamp && pos == rhs.pos;
}
