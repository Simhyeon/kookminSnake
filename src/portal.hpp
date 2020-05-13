#ifndef PORTAL_H
#define PORTAL_H

#include "commons.hpp"

class Portal{
private:
	const long timestamp;
	const Position first;
	const Position second;
public:
	Portal(Position, Position);

friend class PortalSystem;
};

#endif
