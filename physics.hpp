#ifndef PHYSICS_H
#define PHYSICS_H

#include <utility>
#include "commons.hpp"
#include "wall.hpp"
#include "item.hpp"

enum class COLLTYPE{
	NONE,
	WALL,
	PORTAL,
	ITEM,
};

class Physics{
private:
	Position playerPosition;
public:
	void UpdatePlayerPos(int x, int y);
	COLLTYPE DetectCollision(WallSystem& wall_system, ItemSystem &item_system);
};

#endif
