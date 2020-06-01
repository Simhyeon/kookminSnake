#include "collisionsystem.hpp"
#include "playerbody.hpp"

void CollisionSystem::process(ECSDB & db){
	if (detect_collision(db.get_walls(), db.get_snake())){
		db.set_death(true);
	}
}

// 현재 Wall의 Position에 저장된 정보가 0 인덱스부터 시작한다. 이 점 유의하자. 
bool CollisionSystem::detect_collision(const PosVc& walls,const std::vector<PlayerBody>& bodies){
	const PlayerBody& head = bodies[0];
	for (const Position& wall: walls){
		if (head.get_pos() == wall) {
			return true;
		}
	}

	for (auto it = bodies.begin() + 1; it != bodies.end(); it++) {
		if (head.get_pos() == (*it).get_pos()) {
			return true;
		}
	}

	return false;
}
