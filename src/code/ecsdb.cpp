#include "ecsdb.hpp"
#include "portal.hpp"
#include "commons.hpp"
#include "item.hpp"
#include "playerbody.hpp"
#include <cstdio>
#include <memory>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include "string.hpp"

// Functions	
// Constructor
// Currently for Debuggin
ECSDB::ECSDB(){}
void ECSDB::Init(int width, int height, char** snake_map, DIRECTION snake_direction) {
	this->width = width;
	this->height = height;
	this->snake_map = snake_map;
	start_time = Util::get_time(); 

	empty = std::vector<FILL>(width * height, FILL::NEVER);

	for(int i =0; i < width; i++){
		for(int j =0; j < height; j++){
			if (snake_map[i][j] == char_map.at("wall")){
				walls.push_back(Position(i,j));
			} else if (snake_map[i][j] == char_map.at("head") ||
					snake_map[i][j] == char_map.at("tail") ){
				int size = snake.size();
				snake.push_back(PlayerBody(Position(i,j), snake_direction, size));
				std::cout << "Putting snake to " << Position(i,j) << "\n";
				set_empty(i,j, FILL::FILL);
			} else if (snake_map[i][j] == char_map.at("iwall")) {
				iwalls.push_back(Position(i,j));
			} else {
				set_empty(i,j, FILL::EMPTY);
			}
		}
	}
}
ECSDB::ECSDB(int width, int height, char** snake_map, DIRECTION snake_direction)
	: width(width), height(height), snake_map(snake_map), start_time(Util::get_time()) {
	// Initialize empty
	empty = std::vector<FILL>(width * height, FILL::NEVER);

	for(int i =0; i < width; i++){
		for(int j =0; j < height; j++){
			if (snake_map[i][j] == char_map.at("wall")){
				walls.push_back(Position(i,j));
			} else if (snake_map[i][j] == char_map.at("head") ||
					snake_map[i][j] == char_map.at("tail") ){
				int size = snake.size();
				snake.push_back(PlayerBody(Position(i,j), snake_direction, size));
				std::cout << "Putting snake to " << Position(i,j) << "\n";
				set_empty(i,j, FILL::FILL);
			} else if (snake_map[i][j] == char_map.at("iwall")) {
				iwalls.push_back(Position(i,j));
			} else {
				set_empty(i,j, FILL::EMPTY);
			}
		}
	}
}

// This function is for renderer should be moved to proper position
void ECSDB::update_snake_map(){
	std::cout << "Update\n";
	for (int i =0; i < width; i++){
		for (int j =0; j < height; j++){
			snake_map[i][j] = char_map.at("empty");
		}
	}
	std::cout << "1\n";
	std::cout << growth.size() << "\n";
	for (Item& item: growth){
		snake_map[item.get_pos().get_x()][item.get_pos().get_y()] = char_map.at("growth");
	}
	std::cout << "2\n";
	for (Item& item: poison){
		snake_map[item.get_pos().get_x()][item.get_pos().get_y()] = char_map.at("poison");
	}
	std::cout << "3\n";

	for (PlayerBody& player: snake){
		snake_map[player.get_pos().get_x()][player.get_pos().get_y()] = char_map.at("tail");
	}
	// Set head char
	std::cout << "4\n";
	snake_map[snake[0].get_pos().get_x()][snake[0].get_pos().get_y()] = char_map.at("head");

	std::cout << "5\n";
	for (Position& pos: walls){
		snake_map[pos.get_x()][pos.get_y()] = char_map.at("wall");
	}

	std::cout << "6\n";
	for (Position& pos: iwalls){
		snake_map[pos.get_x()][pos.get_y()] = char_map.at("iwall");
	}

	std::cout << "7\n";
	if (portal.get_first_pos().get_x() != -1){
		snake_map[portal.get_first_pos().get_x()][portal.get_first_pos().get_y()] = char_map.at("gate");
		snake_map[portal.get_second_pos().get_x()][portal.get_second_pos().get_y()] = char_map.at("gate");
	}
}

// Getter
const long ECSDB::get_time() const { 
	return start_time; 
}

const std::pair<int, int> ECSDB::get_measure() const{ 
	return std::pair<int, int>(ECSDB::width, ECSDB::height); 
}

int ECSDB::get_width() const{
	return width;
}

int ECSDB::get_height() const{
	return height;
}

const std::vector<PlayerBody>& ECSDB::get_snake() const{ 
	return snake; 
}

std::vector<PlayerBody>& ECSDB::get_mut_snake(){ 
	return snake; 
}

const PlayerBody& ECSDB::get_head() const{
	return *(snake.begin());
}

const PlayerBody& ECSDB::get_tail() const{
	return *(snake.end()-1);
}

const bool ECSDB::get_death() const{
	return player_death;
}

const bool ECSDB::get_success() const{
	return player_success;
}

const PosVc& ECSDB::get_walls() const {
	return walls;
}

PosVc& ECSDB::get_mut_walls() {
	return walls;
}

const PosVc& ECSDB::get_iwalls() const{
	return iwalls;
}

const Portal& ECSDB::get_portal() const{
	return portal;
}

const ItmVc& ECSDB::get_growth() const{
	return growth;
}

ItmVc& ECSDB::get_mut_growth(){ 
	return growth;
}

const ItmVc& ECSDB::get_poison() const{
	return poison;
}

ItmVc& ECSDB::get_mut_poison(){
	return poison;
}

const std::vector<FILL>& ECSDB::get_empty() const{
	return empty;
}

const FILL ECSDB::get_empty(int x, int y) const{
	return empty[x * width + y];
}

const FILL ECSDB::get_empty(Position pos) const{
	return empty[pos.get_x() * width + pos.get_y()];
}

std::vector<FILL>& ECSDB::get_mut_empty(){
	return empty;
}

DIRECTION ECSDB::get_last_direction() const{
	return last_direction;
}

const std::queue<char> ECSDB::get_inputs(){return console_inputs;}

// Setter
void ECSDB::set_death(bool value){ 
	player_death = value; 
}

void ECSDB::set_sucess(bool value){ 
	player_success = value; 
}

void ECSDB::push_snake(PlayerBody body){
	snake.push_back(body);
}
void ECSDB::pop_snake(){
	snake.pop_back();
}

void ECSDB::set_portal(Portal portal){
	this->portal = portal;
}

void ECSDB::set_growth(Item item){
	growth.push_back(item);
}

void ECSDB::set_poison(Item item){
	poison.push_back(item);
}

void ECSDB::set_snake_map(Position pos, char ch){
	snake_map[pos.get_x()-1][pos.get_y()-1] = ch;
}

void ECSDB::set_empty(Position pos, FILL fill){
	empty[pos.get_x() * width + pos.get_y()] = fill;
}

void ECSDB::set_empty(int x, int y, FILL fill){
	empty[x * width + y] = fill;
}

void ECSDB::set_last_direction(DIRECTION direction){
	last_direction = direction;
}

void ECSDB::set_growth_counter(int increment){
	growth_counter += increment;
}

void ECSDB::set_poison_counter(int increment){
	poison_counter += increment;
}
