#ifndef PORTAL_H
#define PORTAL_H

#include "commons.hpp"

class Portal{
private:
	long timestamp;
	Position first;
	Position second;
public:
	Portal(const Position&, const Position&);
	//Portal(const Position&, const Position&);
	Portal(const Portal&);
	Portal& operator=(Portal&);
	Position get_first_pos();
	Position get_second_pos();

friend class PortalSystem;
};

#endif
