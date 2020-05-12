#include "commons.hpp"
#include "collisionsystem.hpp"
#include "playerbody.hpp"

void CollisionSystem::Process(ECSDB & db){
	if (DetectCollision(db.get_walls(), db.get_snake()[0])){
		db.set_death(true);
	}
}

bool CollisionSystem::DetectCollision(const PosVc& walls, PlayerBody& head){
	for (Position wall: walls){
		if (head.get_pos() == wall) {
			return true;
		}
	}
	return false;
}
