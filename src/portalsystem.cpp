#include "commons.hpp"
#include "playerbody.hpp"
#include "portal.hpp"
#include "portalsystem.hpp"
#include <exception>

void PortalSystem::jump_snake(PlayerBody& body, Position destination, DIRECTION portal_dir) {
	int dirct = static_cast<int>(portal_dir);
	destination.increment(dirct%2, -dirct/2);
	body.set_pos(destination.get_x(), destination.get_y());
}

// 규칙을 이렇게 단순하게 할 수는 없음. 더 상세하게 디테일을 잡아야 함. 
DIRECTION PortalSystem::get_direction(Position destination, int width, int height){
	if (destination.get_x() == 0) {
		return DIRECTION::RIGHT;
	} else if (destination.get_x() == width -1) {
		return DIRECTION::LEFT;
	} else if (destination.get_y() == 0) {
		return DIRECTION::DOWN;
	} else if (destination.get_y() == height - 1) {
		return DIRECTION::UP;
	} else {
		std::cerr << "Pos : " << destination.get_x() << "\t" << destination.get_y() << "\n";
		throw std::exception();
	}
}

// 현재 wall의 위치를 관리하는 functionality가 없는 상황이다. 
// portal이 생겼다고 해도 wall의 정보가 사라지지 않는다.  -> 확실히 수정 해야함. 
// 이건 ecsdb에서 임시로 만든 constructor에서도 동일한 상황이다. 
Portal PortalSystem::regen_portal(const PosVc& walls) {
	int first, second;
	first = Util::get_rand(0, walls.size() - 1);
	second = Util::get_rand(0, walls.size() - 1);
	while (first == second || walls[first].get_manhattan(walls[second]) < 2) {
		second = Util::get_rand(0, walls.size() - 1);
	}
	return Portal(walls[first], walls[second]);
}

std::pair<Position, int> PortalSystem::check_portal_interaction(std::vector<PlayerBody>& bodies, const Portal& portal){
	// 시원치 않은 방법이지만 임시로 하자. 
	int counter = 0;
	for (PlayerBody& body : bodies){
		if (body.get_pos() == portal.first){
			return std::pair<Position, int>(Position(portal.second), counter);
		} else if (body.get_pos() == portal.second){
			return std::pair<Position, int>(Position(portal.first), counter);
		}
		counter++;
	}
	return std::pair<Position, int>(Position(-1,-1), -1);
}

void PortalSystem::process(ECSDB & db) {
	std::cout << "Portal processing\n";
	auto result = check_portal_interaction(db.get_snake(), db.get_portal());

	if (result.first.get_x() != -1){ // 포탈이 부딪히고 있다면 부딪힌 뱀을 이동시킨다. 
		DIRECTION portal_dir = get_direction(result.first, db.get_measure().first, db.get_measure().second);
		jump_snake(db.get_snake()[result.second], result.first, portal_dir);
		db.last_direction = portal_dir;
	} else { // 그렇지 않다면 regen 시킨다.
		if (Util::get_time() - db.get_portal().timestamp >= portal_time) {
			db.set_portal(regen_portal(db.get_walls()));
		}
	}
}
