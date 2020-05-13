#include "commons.hpp"
#include "playerbody.hpp"
#include "portal.hpp"
#include "portalsystem.hpp"
#include <exception>

void PortalSystem::jump_snake(PlayerBody& head, Position destination, DIRECTION direction) {
	int dirct = static_cast<int>(direction);
	destination.increment(dirct%2, -dirct/2);
	head.set_pos(destination.get_x(), destination.get_y());
	head.set_direction(direction);
}

DIRECTION PortalSystem::get_direction(Position destination, int width, int height){
	if (destination.get_x() == 0) {
		return DIRECTION::RIGHT;
	} else if (destination.get_x() == width) {
		return DIRECTION::LEFT;
	} else if (destination.get_y() == 0) {
		return DIRECTION::DOWN;
	} else if (destination.get_y() == height) {
		return DIRECTION::UP;
	} else {
		throw std::exception();
	}
}

Portal PortalSystem::regen_portal(const PosVc& walls) {
	int first, second;
	first = Util::get_rand(0, walls.size() - 1);
	second = Util::get_rand(0, walls.size() - 1);
	while (first != second) {
		second = Util::get_rand(0, walls.size() - 1);
	}
	return Portal(walls[first], walls[second]);
}

std::pair<bool, Position> PortalSystem::check_portal_interaction(const PlayerBody& head, const Portal& portal){
	if (head.get_pos() == portal.first){
		return std::pair<bool, Position>(true, portal.second);
	} else if (head.get_pos() == portal.second) {
		return std::pair<bool, Position>(true, portal.first);
	} else {
		return std::pair<bool, Position>(false, Position(-1,-1));
	}
}

void PortalSystem::process(ECSDB & db) {
	if (Util::get_time() - db.get_portal().timestamp >= portal_time) {
		regen_portal(db.get_walls());
	}
	auto result = check_portal_interaction(db.get_head(), db.get_portal());
	if (result.first){
		jump_snake(db.get_head(), result.second, get_direction(result.second, db.get_measure().first, db.get_measure().second));
	}
}
