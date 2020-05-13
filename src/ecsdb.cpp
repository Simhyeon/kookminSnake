#include "ecsdb.hpp"
#include "portal.hpp"
#include "commons.hpp"
#include "item.hpp"
#include "playerbody.hpp"
#include <vector>
#include <queue>

// Functions	
// Getter
const long ECSDB::get_time() const { return start_time; }
const std::pair<int, int> ECSDB::get_measure() const { return std::pair<int, int>(width, height); }
std::vector<PlayerBody>& ECSDB::get_snake(){ return snake; }
PlayerBody& ECSDB::get_head(){return snake[0];}
const bool ECSDB::get_death() const{return player_death;}
const PosVc& ECSDB::get_walls() const{return walls;}
const Portal& ECSDB::get_portal() const{return portal;}
ItmVc& ECSDB::get_growth(){return growth;}
ItmVc& ECSDB::get_posion(){return poison;}
const std::queue<char> ECSDB::get_inputs(){return console_inputs;}
// Setter
void ECSDB::set_death(bool value){ player_death = value; }
void ECSDB::set_snake(bool increment){ }
void ECSDB::set_portal(Position first, Position second){}
void ECSDB::set_growth(Position){}
void ECSDB::set_poison(Position){}
