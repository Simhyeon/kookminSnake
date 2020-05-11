#ifndef ECSDB_H
#define ECSDB_H

#include "commons.hpp"
#include "playerbody.hpp"
#include <vector>
#include <queue>

class ECSDB{
private:
	bool player_death;
	std::vector<PlayerBody> snake;
	const std::vector<Position> walls;
	std::vector<Position> portals;
	std::vector<Position> goodies;
	std::vector<Position> poison;

	std::queue<char> console_inputs; // Placeholder
public:
	ECSDB();

	const bool get_death();
	const auto get_snake();
	const auto get_walls();
	const auto get_portals();
	const auto get_goodies();
	const auto get_posions();

	const auto get_inputs(); // Placeholder

	void set_death(bool value);
	void set_snake(bool increment);
	void set_portal(bool increment, int entity_index);
	void set_goodies(bool increment, int entity_index);
	void set_poison(bool increment, int entity_index);

	void set_input(char input); // Placeholder
};

#endif
