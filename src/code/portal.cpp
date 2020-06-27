/**
 * @file portal.cpp
 *
 * @author 육심현(20150803)
 *
 */

#include "portal.hpp"
#include "commons.hpp"
#include <chrono>

/// @author 육심현(20150803)
Portal::Portal() : timestamp(Util::get_time()){ }
/// @author 육심현(20150803)
Portal::Portal(const Position& first,const Position& second, const DIRECTION first_dir, DIRECTION second_dir): timestamp(Util::get_time()), first_entry(first), second_entry(second) { }
/// @author 육심현(20150803)
Portal::Portal(const Portal& portal): timestamp(portal.timestamp), first_entry(portal.first_entry), second_entry(portal.second_entry){ }
/// @author 육심현(20150803)
Portal& Portal::operator=(Portal& port){
	timestamp = port.timestamp; 
	first_entry = port.first_entry;
	second_entry = port.second_entry;
	return *this;
}
/// @author 육심현(20150803)
Position Portal::get_first_pos() const{
	return first_entry;
}
/// @author 육심현(20150803)
Position Portal::get_second_pos() const{
	return second_entry;
}
