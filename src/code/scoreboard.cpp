#include "scoreboard.hpp"

void ScoreSystem::process(ECSDB &db){
	if (db.get_growth_qual() <= db.get_growth_counter() &&
			db.get_poison_qual() <= db.get_poison_counter())
			/*&& db.get_gate_qual() <= db.get_gate_counter())*/{
		db.set_sucess(true);
	}
}
