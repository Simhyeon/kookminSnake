#ifndef PORTAL_H
#define PORTAL_H

#include "commons.hpp"

class Portal{
private:
	Time timestamp;
	Position first;
	Position second;

friend class PortalSystem;
};

#endif
