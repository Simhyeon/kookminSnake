#include "playersystem.hpp"
#include "commons.hpp"
#include "playerbody.hpp"

void PlayerBodySystem::change_direction(DIRECTION direction, PlayerBody& head){
	if (head.get_direction() == direction) {
		return;
	} else if (static_cast<int>(head.get_direction()) == -static_cast<int>(direction))  {
		// Reverse direction input given. 
		// Kill or ignore
		return;
	} else {
		head.set_direction(direction);
	}
}

void PlayerBodySystem::process(ECSDB& db) {
	auto dirct =  get_console_input(db.get_inputs().front()); // placeholder
	if (dirct.first) {
		change_direction(dirct.second, db.get_snake()[0]);
	}
	move(db.get_snake());
}

std::pair<bool, DIRECTION> PlayerBodySystem::get_console_input(char input) {
	// Check if input is valid
}

void PlayerBodySystem::move(std::vector<PlayerBody>& bodies){
	int dirct = static_cast<int>(bodies[0].get_direction());
	bodies[0].increment_pos(dirct%2, -dirct/2);
	PlayerBody parent = bodies[0];
	PlayerBody cache;

	// Should check if operation is optimal and change Position class implementation accordingly.
	for(auto it = bodies.begin() + 1; it != bodies.end(); it++) {
		cache = (*it);
		(*it).set_pos(parent.get_pos());
		(*it).set_direction(parent.get_direction());
		parent = cache;
	}
}
