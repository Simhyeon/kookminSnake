#ifndef PORTALSYS_H
#define PORTALSYS_H

#include "ecsdb.hpp"
#include "commons.hpp"
#include <vector>

class PortalSystem{
private:
	const double portal_time = 5.0;
	void jump_snake();
	void set_portal();
	void remove_portal();

	void check_portal_interaction(ECSDB&);
public:
	// Search if player pos is conciding with portal if true then set player pos to somewhere else
	// Set portals
	void process(ECSDB&);
};

#endif
