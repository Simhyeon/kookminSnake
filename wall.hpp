#ifndef WALL_H
#define WALL_H

#include "commons.hpp"
#include <vector>

class WallSystem{
	private:
		const std::vector<Position> const_walls;
		std::vector<Position> walls;
		std::vector<Position> Portals;
	public:
		WallSystem(int width, int height, int borderlength =2);
		const bool at_wall(int x, int y) const;
		const bool at_Portals(int x, int y) const;
};

#endif
