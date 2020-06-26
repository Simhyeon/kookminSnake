/**
 * @file collisionsystem.cpp
 *
 * @author 육심현
 *
 */

#include "collisionsystem.hpp"
#include "playerbody.hpp"

void CollisionSystem::process(ECSDB & db){
	// 만약 플레이어가 다른 오브젝트와 충돌 했다면 죽는다.
	if (detect_collision(db.get_walls(), db.get_snake())){
		db.set_death(true);
	}
}

// 플레이어가 다른 오브젝트와 충돌했는가를 검사한다.
bool CollisionSystem::detect_collision(const PosVc& walls,const std::vector<PlayerBody>& bodies){

	const PlayerBody& head = bodies[0];
	// 플레이어가 벽과 충돌했는지를 검사한다.
	// 위치가 동일하다면 충돌한 것으로 본다.
	for (const Position& wall: walls){
		if (head.get_pos() == wall) { 
			return true;
		}
	}

	// 플레이어가 자기 몸과 충돌했는지를 검사한다.
	// 위치가 동일하다면 충돌한 것으로 본다.
	for (auto it = bodies.begin() + 1; it != bodies.end(); it++) {
		if (head.get_pos() == (*it).get_pos()) { 
			return true;
		}
	}

	return false;
}
