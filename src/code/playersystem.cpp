#include "playersystem.hpp"
#include "playerbody.hpp"

void PlayerBodySystem::change_direction(DIRECTION direction, std::vector<PlayerBody>& bodies){
	for(PlayerBody& item: bodies){
  		item.push_direction(direction);
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

	DIRECTION next = db.get_last_direction();

	change_direction(next, db.get_mut_snake());
	Position last_pos = db.get_snake()[db.get_snake().size() -1].get_pos(); 
	db.set_empty(last_pos.get_x(), last_pos.get_y(), FILL::EMPTY);
	move(db.get_mut_snake());
	db.set_empty(db.get_snake()[0].get_pos().get_x(), db.get_snake()[0].get_pos().get_y(), FILL::FILL);
}
// TODO
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
