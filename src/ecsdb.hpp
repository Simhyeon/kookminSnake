#ifndef ECSDB_H
#define ECSDB_H

#include "commons.hpp"
#include "item.hpp"
#include "portal.hpp"
#include "playerbody.hpp"
#include <vector>
#include <queue>

class ECSDB{
private:
	Time runtime;
	const int width, height;
	bool player_death;
	std::vector<PlayerBody> snake;
	PosVc walls;
	PosVc empty;
	Portal portal;
	ItmVc growth;
	ItmVc poison;

	std::queue<char> console_inputs; // Placeholder
public:
	ECSDB();

	const Time& get_time();
	std::vector<PlayerBody>& get_snake();
	const bool get_death();
	const PosVc& get_walls();
	const PosVc& get_portals();
	const ItmVc& get_growth();
	const ItmVc& get_posion();

	const std::queue<char> get_inputs(); // Placeholder

	void set_time(Time time);
	void set_death(bool value);
	void set_snake(bool increment);
	void set_portal(Position first, Position second);
	void set_growth(bool increment, int entity_index);
	void set_poison(bool increment, int entity_index);

	void set_input(char input); // Placeholder
};

#endif
