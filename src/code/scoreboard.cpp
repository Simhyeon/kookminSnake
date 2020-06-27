/**
 * @file scoreboard.cpp
 *
 * @author 류희재(20191587)
 *
 */

#include "scoreboard.hpp"
/// @author 류희재(20191587)
void ScoreSystem::process(ECSDB &db){

	if (db.get_growth_qual() <= db.get_growth_counter()){
		db.set_growth_ok(true);
	}

	if (db.get_poison_qual() <= db.get_poison_counter()){
		db.set_poison_ok(true);
	}

	if (db.get_length_qual() <= db.get_snake().size()){
		db.set_length_ok(true);
	} else {
		db.set_length_ok(false);
	}

	if (db.get_gate_qual() <= db.get_gate_counter()){
		db.set_gate_ok(true);
	}

	if (db.get_length_ok() && db.get_growth_ok() && db.get_poison_ok() && db.get_gate_ok()){
		db.set_sucess(true);
	}
}
