#include "commons.hpp"
#include "ecsdb.hpp"
#include "playerbody.hpp"
#include "portal.hpp"
#include "portalsystem.hpp"
#include <algorithm>
#include <array>
#include <exception>

void PortalSystem::jump_snake(PlayerBody& body, Position destination) {
	body.set_pos(destination.get_x(), destination.get_y());
}

std::pair<Position, DIRECTION> PortalSystem::get_jump_result(Position destination,int body_nubmer, ECSDB& db){

	if (destination.get_x() == 0) {
		return std::pair<Position,DIRECTION>(
				Util::get_modified_pos(destination, DIRECTION::RIGHT), 
				DIRECTION::RIGHT
				);
	} else if (destination.get_x() == db.get_width() -1) {
		return std::pair<Position,DIRECTION>(
				Util::get_modified_pos(destination, DIRECTION::LEFT), 
				DIRECTION::LEFT
				);
	} else if (destination.get_y() == 0) {
		return std::pair<Position,DIRECTION>(
				Util::get_modified_pos(destination, DIRECTION::DOWN), 
				DIRECTION::DOWN
				);
	} else if (destination.get_y() == db.get_height() - 1) {
		return std::pair<Position,DIRECTION>(
				Util::get_modified_pos(destination, DIRECTION::UP), 
				DIRECTION::UP
				);
	} 

	// TODO Modify more
	PosVc walls = db.get_walls();
	walls.insert(walls.end(), db.get_iwalls().begin(), db.get_iwalls().end());
	DIRECTION last_dir = db.get_snake()[body_nubmer].get_last_dir();

	DIRECTION new_dir = db.get_snake()[body_nubmer].get_last_dir();
	Position new_pos =  Util::get_modified_pos(destination, new_dir);
	// Staight First 
	if (std::find_if(walls.begin(), walls.end(), [&](const Position& wall){return wall == new_pos;}) == walls.end()){
		return std::pair<Position, DIRECTION>(new_pos, new_dir);
	}

	// Left First
	new_dir = Util::rotate_dir(last_dir, DIRECTION::LEFT);
	new_pos =  Util::get_modified_pos(destination, new_dir);

	if (std::find_if(walls.begin(), walls.end(), [&](const Position& wall){return wall == new_pos;}) == walls.end()){
		return std::pair<Position, DIRECTION>(new_pos, new_dir);
	}

	// Then right
	new_dir = Util::rotate_dir(last_dir, DIRECTION::RIGHT);
	new_pos =  Util::get_modified_pos(destination, new_dir);

	if (std::find_if(walls.begin(), walls.end(), [&](const Position& wall){return wall == new_pos;}) == walls.end()){
		return std::pair<Position, DIRECTION>(new_pos, new_dir);
	}

	// Then back
	new_dir = Util::get_reverse_dir(last_dir);
	new_pos = Util::get_modified_pos(destination, new_dir);

	if (std::find_if(walls.begin(), walls.end(), [&](const Position& wall){return wall == new_pos;}) == walls.end()){
		return std::pair<Position, DIRECTION>(new_pos, new_dir);
	}

	// This is logical error 
	// At least one side should be open if it is not w immune wall.
	throw std::exception();
}

Portal PortalSystem::regen_portal(const Portal& portal, PosVc& walls) {
	std::cout << "Regening portal\n";
	int first, second;
	int wall_size = walls.size();
	Position first_pos, second_pos;
	first = Util::get_rand(0, walls.size() - 1);
	
	first_pos = Position(walls[first]);

	std::swap(walls[first], walls[wall_size-1]);
	walls.pop_back();
	wall_size = walls.size();

	second = Util::get_rand(0, walls.size() - 1);
	while (walls[first].get_manhattan(walls[second]) <= 2) {
		second = Util::get_rand(0, walls.size() - 1);
	}

	second_pos = Position(walls[second]);
	std::swap(walls[second], walls[wall_size-1]);
	walls.pop_back();

	// 포탈 위치에 있던 position을 다시 wall로 집어넣는다. 
	if (portal.get_first_pos().get_x() != -1){
		std::cout << "Putting wall poisition back\n";
		walls.push_back(portal.get_first_pos());
		walls.push_back(portal.get_second_pos());
	}

	// TODO
	return Portal(first_pos, second_pos, DIRECTION::UP, DIRECTION::UP);
}

std::pair<Position, int> PortalSystem::check_portal_interaction(const std::vector<PlayerBody>& bodies, const Portal& portal){
	// 시원치 않은 방법이지만 임시로 하자. 
	std::cout << "Chekcing portl inte\n";
	int counter = 0;
	for (const PlayerBody& body : bodies){
		if (body.get_pos() == portal.get_first_pos()){
			std::cout << "First int\n";
			return std::pair<Position, int>(portal.second_entry, counter);
		} else if (body.get_pos() == portal.get_second_pos()){
			std::cout << "Second int\n";
			return std::pair<Position, int>(portal.first_entry, counter);
		}
		counter++;
	}
	return std::pair<Position, int>(Position(-1,-1), -1);
}

void PortalSystem::process(ECSDB & db) {
	std::cout << "Portal processing\n";
	auto result = check_portal_interaction(db.get_snake(), db.get_portal());

	if (result.second != -1){ // 포탈이 부딪히고 있다면 부딪힌 뱀을 이동시킨다. 
		std::pair<Position, DIRECTION> jump_for = get_jump_result(result.first, result.second, db);
		Position destination = Util::get_modified_pos(result.first, jump_for.second);
		jump_snake(db.get_mut_snake()[result.second], destination);
		db.set_empty(destination, FILL::FILL);
		db.set_last_direction(jump_for.second);

	} else { // 그렇지 않다면 regen 시킨다.
		std::cout << "Checking regen\n";
		std::cout << Util::get_time() << "\n";
		std::cout << db.get_portal().timestamp << "\n";
		if (Util::get_time() - db.get_portal().timestamp >= portal_time) {
			std::cout << "Regenning\n";
			Portal portal = regen_portal(db.get_portal(), db.get_mut_walls());
			db.set_portal(portal);
		}
	}
}
