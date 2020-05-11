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
	const PosVc walls;
	PosVc empty;
	PosVc portals;
	PosVc goodies;
	PosVc poison;

	std::queue<char> console_inputs; // Placeholder
public:
	ECSDB();

	std::vector<PlayerBody>& get_snake();
	const bool get_death();
	const PosVc& get_walls();
	const PosVc& get_portals();
	const PosVc& get_goodies();
	const PosVc& get_posions();

	const std::queue<char> get_inputs(); // Placeholder

	void set_death(bool value);
	void set_snake(bool increment);
	void set_portal(bool increment, int entity_index);
	void set_goodies(bool increment, int entity_index);
	void set_poison(bool increment, int entity_index);

	void set_input(char input); // Placeholder
};

#endif
