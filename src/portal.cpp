#include "portal.hpp"
#include <chrono>

Portal::Portal(const Position& first,const Position& second): timestamp(Util::get_time()), first(first), second(second) { }
//Portal::Portal(const Position& first, const Position& second): timestamp(Util::get_time()), first(first), second(second) { }

Portal::Portal(const Portal& portal): timestamp(portal.timestamp), first(portal.first), second(portal.second){ }

Portal& Portal::operator=(Portal& port){
	timestamp = port.timestamp; 
	first = port.first;
	second = port.second;
	return *this;
}
Position Portal::get_first_pos(){
	return first;
}

Position Portal::get_second_pos(){
	return second;
}
