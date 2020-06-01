#ifndef PORTAL_H
#define PORTAL_H

#include "commons.hpp"

class Portal{
private:
	long timestamp;
	Position first_entry;
	Position second_entry;
public:
	Portal();
	Portal(const Position& first,const Position& second, const DIRECTION first_dir, DIRECTION second_dir);
	//Portal(const Position&, const Position&);
	Portal(const Portal&);
	Portal& operator=(Portal&);
	Position get_first_pos() const;
	Position get_second_pos() const;

friend class PortalSystem;
};

#endif
