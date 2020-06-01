#ifndef PORTAL_H
#define PORTAL_H

#include "commons.hpp"

class GateEntry{
private:
	Position position;
	DIRECTION direction;
public:
	GateEntry();
	GateEntry(const Position& pos, DIRECTION dir);
	void set_direction(DIRECTION dir); 
	Position get_position();
	DIRECTION get_direction();

friend class Portal;
};

class Portal{
private:
	long timestamp;
	GateEntry first_entry;
	GateEntry second_entry;
public:
	Portal();
	Portal(const Position& first,const Position& second, const DIRECTION first_dir, DIRECTION second_dir);
	//Portal(const Position&, const Position&);
	Portal(const Portal&);
	Portal& operator=(Portal&);
	Position get_first_pos() const;
	Position get_second_pos() const;
	DIRECTION get_first_dir() const;
	DIRECTION get_second_dir() const;

friend class PortalSystem;
};

#endif
