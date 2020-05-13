#ifndef PHYSICS_H
#define PHYSICS_H

#include "commons.hpp"
#include "ecsdb.hpp"
#include "playerbody.hpp"

class CollisionSystem{
private:
	bool DetectCollision(const PosVc& wallas, const std::vector<PlayerBody>& bodies);
public:
	void Process(ECSDB&);
};

#endif
