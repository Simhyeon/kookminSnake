#include "ecsdb.hpp"
#include "portal.hpp"
#include "commons.hpp"
#include "item.hpp"
#include "playerbody.hpp"
#include <vector>
#include <queue>

// Functions	
// Getter
const Time& ECSDB::get_time(){ return runtime; }
std::vector<PlayerBody>& ECSDB::get_snake(){ return snake; }
const bool ECSDB::get_death(){return player_death;}
const PosVc& ECSDB::get_walls(){return walls;}
const Portal& ECSDB::get_portal(){return portal;}
const ItmVc& ECSDB::get_growth(){return growth;}
const ItmVc& ECSDB::get_posion(){return poison;}
const std::queue<char> ECSDB::get_inputs(){return console_inputs;}
// Setter
void ECSDB::set_time(Time time){ runtime = time;	} 
void ECSDB::set_death(bool value){ player_death = value; }
void ECSDB::set_snake(bool increment){ }
void ECSDB::set_portal(Position first, Position second){}
void ECSDB::set_growth(bool increment, int entity_index){}
void ECSDB::set_poison(bool increment, int entity_index){}
