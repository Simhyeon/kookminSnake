#include "portal.hpp"
#include "commons.hpp"
#include <chrono>

GateEntry::GateEntry(){ }

GateEntry::GateEntry(const Position& pos, DIRECTION dir){
	position= pos; 
	direction = dir;
}
void GateEntry::set_direction(DIRECTION dir){
	direction= dir;
}

Position GateEntry::get_position(){
	return position;
}

DIRECTION GateEntry::get_direction(){
	return direction;
}

Portal::Portal(){ }
Portal::Portal(const Position& first,const Position& second, const DIRECTION first_dir, DIRECTION second_dir): timestamp(Util::get_time()), first_entry(first, first_dir), second_entry(second, second_dir) { }

Portal::Portal(const Portal& portal): timestamp(portal.timestamp), first_entry(portal.first_entry), second_entry(portal.second_entry){ }

Portal& Portal::operator=(Portal& port){
	timestamp = port.timestamp; 
	first_entry = port.first_entry;
	second_entry = port.second_entry;
	return *this;
}
Position Portal::get_first_pos() const{
	return first_entry.position;
}

Position Portal::get_second_pos() const{
	return second_entry.position;
}

DIRECTION Portal::get_first_dir() const{
	return first_entry.direction;
}

DIRECTION Portal::get_second_dir() const{
	return second_entry.direction;
}
