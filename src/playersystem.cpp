#include "playersystem.hpp"
#include "playerbody.hpp"

void PlayerBodySystem::change_direction(DIRECTION direction, std::vector<PlayerBody>& bodies){
	int counter = 0;
	for(PlayerBody& item: bodies){
  		item.push_direction(direction);
		counter++;
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

	DIRECTION next = db.last_direction;

	if (static_cast<int>(db.last_direction) != -static_cast<int>(next)){
		change_direction(next, db.get_snake());
	} else {
		db.set_death(true);
	}

	move(db.get_snake());
	// Update method should be changed according to new data structure
	db.update_snake_map();
}

// Undefined
std::pair<bool, DIRECTION> PlayerBodySystem::get_console_input(char input) {
	// Check if input is valid
}

void PlayerBodySystem::move(std::vector<PlayerBody>& bodies){
	std::cout << "Move called\n";
	for (PlayerBody& body : bodies){
		int dirct = static_cast<int>(body.pop_direction());
		body.increment_pos(dirct%2, -dirct/2);
	}
}
