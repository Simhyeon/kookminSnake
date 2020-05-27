#include "playersystem.hpp"
#include "playerbody.hpp"

bool PlayerBodySystem::change_direction(DIRECTION direction, PlayerBody& head){
	if (head.get_direction() == direction) {
		return false;
	} else if (static_cast<int>(head.get_direction()) == -static_cast<int>(direction))  {
		return true;
	} else {
		head.set_direction(direction);
		return false;
	}
}

bool PlayerBodySystem::check_length(int size) {
	if (size < min_length) {
		return true;
	} else {
		return false;
	}
}

void PlayerBodySystem::process(ECSDB& db) {
	if (check_length(db.get_snake().size())){
		db.set_death(true);
		return;
	}
	auto dirct = get_console_input(db.get_inputs().front()); // placeholder
	if (dirct.first) {
		if (change_direction(dirct.second, db.get_snake()[0])) { // Problem == true
			db.set_death(true);
		}
	}
	move(db.get_snake());
	db.update_snake_map();
}

// Undefined
std::pair<bool, DIRECTION> PlayerBodySystem::get_console_input(char input) {
	// Check if input is valid
}

void PlayerBodySystem::move(std::vector<PlayerBody>& bodies){
	PlayerBody parent = bodies[0];
	PlayerBody cache;

	int dirct = static_cast<int>(bodies[0].get_direction());
	bodies[0].increment_pos(dirct%2, -dirct/2);

	// Should check if operation is optimal and change Position class implementation accordingly.
	for(auto it = bodies.begin() + 1; it != bodies.end(); it++) {
		cache = (*it);
		(*it).set_pos(parent.get_pos());
		(*it).set_direction(parent.get_direction());
		parent = cache;
	}
}
