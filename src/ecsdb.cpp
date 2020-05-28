#include "ecsdb.hpp"
#include "portal.hpp"
#include "commons.hpp"
#include "item.hpp"
#include "playerbody.hpp"
#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

constexpr int ECSDB::width;
constexpr int ECSDB::height;

// Functions	
// Constructor
// Currently for Debuggin
ECSDB::ECSDB() : start_time(Util::get_time()), portal(Position(-1, -1), Position(-1,-1)){
	// Make this as function for fuck's sake
	for (int i =0; i < width; i++){
		for (int j =0; j < height; j++){
			snake_map[i][j] = '`';
		}
	}
	snake = std::vector<PlayerBody>();

	for (int j =0; j < height; j++){
		for (int i =0; i < width; i++){
			if (j == 0 || j == height-1)	{
				snake_map[i][j] = '*';
				walls.push_back(Position(i,j));
			} else {
				snake_map[0][j] = '*';
				snake_map[width-1][j] = '*';
				walls.push_back(Position(0,j));
				walls.push_back(Position(width-1,j));
				break;
			}
		}
	}

	for(int i =0; i < width; i++){
		for(int j =0; j < height; j++){
			switch (snake_map[i][j]){
				case '`':
					empty.push_back(Position(i,j));
					break;
				default:
					break;
			}
		}
	}
}
// Getter
const long ECSDB::get_time() const { return start_time; }
const std::pair<int, int> ECSDB::get_measure() { return std::pair<int, int>(ECSDB::width, ECSDB::height); }
std::vector<PlayerBody>& ECSDB::get_snake(){ return snake; }
void ECSDB::update_snake_map(){
	// Refresh window
	for (int i =0; i < width; i++){
		for (int j =0; j < height; j++){
			snake_map[i][j] = '`';
		}
	}
	
	// Set all items
	for (auto it = growth.begin(); it != growth.end(); it++){
		snake_map[(*it).get_pos().get_x()][(*it).get_pos().get_y()] = 'P';
	}

	for (auto it = poison.begin(); it != poison.end(); it++){
		snake_map[(*it).get_pos().get_x()][(*it).get_pos().get_y()] = 'X';
	}

	// Set all walls
	for (int j =0; j < height; j++){
		for (int i =0; i < width; i++){
			if (j == 0 || j == height-1)	{
				snake_map[i][j] = '*';
			} else {
				snake_map[0][j] = '*';
				snake_map[width-1][j] = '*';
				break;
			}
		}
	}

	// Set portals
	if (portal.get_first_pos().get_x() != -1){ // 포탈이 아직 없지 않을 때 
		snake_map[portal.get_first_pos().get_x()][portal.get_first_pos().get_y()] = 'O';
		snake_map[portal.get_second_pos().get_x()][portal.get_second_pos().get_y()] = 'O';
	}

	// Set all player characters
	snake_map[get_head().get_pos().get_x()][get_head().get_pos().get_y()] = '@';
	for (auto it = snake.begin() + 1; it != snake.end(); it++){
		snake_map[(*it).get_pos().get_x()][(*it).get_pos().get_y()] = '#';
	}

	// Update for empty class
	empty = PosVc{};
	for(int i =0; i < width; i++){
		for(int j =0; j < height; j++){
			switch (snake_map[i][j]){
				case '`':
					empty.push_back(Position(i,j));
					break;
				case 'w':
					break;
				case '#':
					break;
				case '@':
					break;
				default:
					break;
			}
		}
	}
}
PlayerBody& ECSDB::get_head(){return snake[0];}
const bool ECSDB::get_death() const{return player_death;}
const PosVc& ECSDB::get_walls() const{return walls;}
const Portal& ECSDB::get_portal() const{return portal;}
ItmVc& ECSDB::get_growth(){return growth;}
ItmVc& ECSDB::get_poison(){return poison;}
PosVc& ECSDB::get_empty(){
	return empty;
}

const std::queue<char> ECSDB::get_inputs(){return console_inputs;}
// Setter
void ECSDB::set_death(bool value){ player_death = value; }
void ECSDB::set_snake(bool increment){ }
void ECSDB::set_portal(Portal portal){
	this->portal = portal;
}

void ECSDB::set_growth(Position position){
	growth.push_back(Item(position));
	empty.erase(std::remove(empty.begin(), empty.end(), position), empty.end());
}

void ECSDB::set_poison(Position position){
	poison.push_back(Item(position));
	empty.erase(std::remove(empty.begin(), empty.end(), position), empty.end());
}

void ECSDB::set_snake_map(Position pos, char ch){
	snake_map[pos.get_x()-1][pos.get_y()-1] = ch;
}
void ECSDB::remove_empty(Position pos){
	empty.erase(std::remove(empty.begin(), empty.end(), pos), empty.end());
}
