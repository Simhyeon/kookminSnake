/**
 * @file portal.cpp
 *
 * @author 육심현
 *
 */

#include "portal.hpp"
#include "commons.hpp"
#include <chrono>

Portal::Portal() : timestamp(Util::get_time()){ }
Portal::Portal(const Position& first,const Position& second, const DIRECTION first_dir, DIRECTION second_dir): timestamp(Util::get_time()), first_entry(first), second_entry(second) { }

Portal::Portal(const Portal& portal): timestamp(portal.timestamp), first_entry(portal.first_entry), second_entry(portal.second_entry){ }

Portal& Portal::operator=(Portal& port){
	timestamp = port.timestamp; 
	first_entry = port.first_entry;
	second_entry = port.second_entry;
	return *this;
}
Position Portal::get_first_pos() const{
	return first_entry;
}

Position Portal::get_second_pos() const{
	return second_entry;
}
