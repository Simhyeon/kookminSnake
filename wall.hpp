#ifndef WALL_H
#define WALL_H

#include "commons.hpp"
#include <vector>

class Time{

};

class Portals{
private:
	Position first;
	Position second;
	//Time timestamp;

public:

};

enum class WALLTYPE{
	NONE,
	WALL,
	PORTAL,
};

class Walls{

};

class WallSystem{
	private:
		const std::vector<Position> const_walls;
		std::vector<Position> walls;
		std::vector<Portals> portals; // do not use 0th

		void spawn_portals();
		void destroy_portals();

	public:
		WallSystem(int width, int height, int borderlength =1);
		const bool at_wall(int x, int y) const;
		const class Portals* at_portal(int x, int y) const;
		void manage_portal();
};

#endif
