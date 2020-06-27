/**
 * @file ecsdb.cpp
 *
 * @author 육심현(20150803) 류희재(20191587)
 *
 */

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
/// @author 육심현(20150803)
ECSDB::ECSDB(){}
/// @author 육심현(20150803)
ECSDB::~ECSDB(){
	delwin(playboard);
	delwin(scoreboard);
	delwin(titleboard);
	endwin();
}
/// @author 육심현(20150803)
void ECSDB::Init(int width, int height, std::vector<std::vector<char>> snake_map, DIRECTION snake_direction, int growth_count, int poison_count, int gate_count, int length, int max_length) {

	// Init 하면서 내부 변수를 모두 초기화 한다.
	this->width = width;
	this->height = height;
	this->snake_map = std::vector<std::vector<char>>(snake_map);
	start_time = Util::get_time(); 
	player_death = false;
	player_success = false;
	snake.clear();
	walls.clear();
	iwalls.clear();
	growth.clear();
	poison.clear();
	set_portal(Portal());

	growth_qual = growth_count;
	poison_qual = poison_count;
	gate_qual = gate_count;
	growth_counter = 0;
	poison_counter = 0;
	gate_counter = 0;
	length_qual = length;
	this->max_length = max_length;

	growth_ok = false;
	poison_ok = false;
	length_ok = false;
	gate_ok = false;

	last_direction = snake_direction;
	empty = std::vector<FILL>(width * height, FILL::NEVER);

	// Filemanager를 통해서 읽어온 color_map을 차례대로 읽으면서
	// 해당하는 색깔에 연결된 캐릭터 값을 발견한 경우에는
	// 그에 맞는 컴포넌트를 생성한다.
	for(int i =0; i < width; i++){
		for(int j =0; j < height; j++){
			if (snake_map[i][j] == char_map.at("wall")){
				walls.push_back(Position(i,j));
			} else if (snake_map[i][j] == char_map.at("head") ||
					snake_map[i][j] == char_map.at("tail") ){
				int size = snake.size();
				snake.push_back(PlayerBody(Position(i,j), snake_direction, size));
				set_empty(i,j, FILL::FILL);
			} else if (snake_map[i][j] == char_map.at("iwall")) {
				iwalls.push_back(Position(i,j));
			} else {
				set_empty(i,j, FILL::EMPTY);
			}
		}
	}
}

// 렌더러 시스템이 해야할 일을 대신 임시로 하는 함수
// 컴포넌트들을 모두 순회하면서 snake_map을 완성한다.
// 완성된 snake_map을 어떻게 렌더링 할 지는 렌더러 시스템의 몫이다.
/// @author 육심현(20150803)
void ECSDB::update_snake_map(){
	// 모든 캐릭터를 빈 것으로 초기화한다.
	for (int i =0; i < width; i++){
		for (int j =0; j < height; j++){
			snake_map[i][j] = char_map.at("empty");
		}
	}
	// 성장 아이템
	for (Item& item: growth){
		snake_map[item.get_pos().get_x()][item.get_pos().get_y()] = char_map.at("growth");
	}
	// 독 아이템
	for (Item& item: poison){
		snake_map[item.get_pos().get_x()][item.get_pos().get_y()] = char_map.at("poison");
	}

	// 몸체
	for (PlayerBody& player: snake){
		snake_map[player.get_pos().get_x()][player.get_pos().get_y()] = char_map.at("tail");
	}
	// 머리는 따로 다른 캐릭터를 할당한다.
	snake_map[snake[0].get_pos().get_x()][snake[0].get_pos().get_y()] = char_map.at("head");

	// 벽
	for (Position& pos: walls){
		snake_map[pos.get_x()][pos.get_y()] = char_map.at("wall");
	}

	// 영구 벽
	for (Position& pos: iwalls){
		snake_map[pos.get_x()][pos.get_y()] = char_map.at("iwall");
	}

	// 게이트(포탈)
	if (portal.get_first_pos().get_x() != -1){
		snake_map[portal.get_first_pos().get_x()][portal.get_first_pos().get_y()] = char_map.at("gate");
		snake_map[portal.get_second_pos().get_x()][portal.get_second_pos().get_y()] = char_map.at("gate");
	}
}

// Getter
// Getter를 mutable한 것과 mutable하지 않은 것으로 나눈 이유는
// mutable한 getter를 사용하는 경우와 immuatablbe한 getter를 
// 사용하는 경우를 코더가 컴파일 타임에 알게 하기 위함이다. 
// Rust의 영향을 받았다.

/// @author 육심현(20150803)
const long ECSDB::get_time() const { 
	return start_time; 
}
/// @author 육심현(20150803)
const std::pair<int, int> ECSDB::get_measure() const{ 
	return std::pair<int, int>(ECSDB::width, ECSDB::height); 
}
/// @author 육심현(20150803)
int ECSDB::get_width() const{
	return width;
}
/// @author 육심현(20150803)
int ECSDB::get_height() const{
	return height;
}
/// @author 육심현(20150803)
const std::vector<PlayerBody>& ECSDB::get_snake() const{ 
	return snake; 
}
/// @author 육심현(20150803)
std::vector<PlayerBody>& ECSDB::get_mut_snake(){ 
	return snake; 
}
/// @author 육심현(20150803)
const PlayerBody& ECSDB::get_head() const{
	return *(snake.begin());
}
/// @author 육심현(20150803)
const PlayerBody& ECSDB::get_tail() const{
	return *(snake.end()-1);
}
/// @author 육심현(20150803)
const bool ECSDB::get_death() const{
	return player_death;
}
/// @author 육심현(20150803)
const bool ECSDB::get_success() const{
	return player_success;
}
/// @author 육심현(20150803)
const PosVc& ECSDB::get_walls() const {
	return walls;
}
/// @author 육심현(20150803)
PosVc& ECSDB::get_mut_walls() {
	return walls;
}
/// @author 육심현(20150803)
const PosVc& ECSDB::get_iwalls() const{
	return iwalls;
}
/// @author 육심현(20150803)
const Portal& ECSDB::get_portal() const{
	return portal;
}
/// @author 육심현(20150803)
const ItmVc& ECSDB::get_growth() const{
	return growth;
}
/// @author 육심현(20150803)
ItmVc& ECSDB::get_mut_growth(){ 
	return growth;
}
/// @author 육심현(20150803)
const ItmVc& ECSDB::get_poison() const{
	return poison;
}
/// @author 육심현(20150803)
ItmVc& ECSDB::get_mut_poison(){
	return poison;
}
/// @author 육심현(20150803)
const std::vector<FILL>& ECSDB::get_empty() const{
	return empty;
}
/// @author 육심현(20150803)
const FILL ECSDB::get_empty(int x, int y) const{
	return empty[x * width + y];
}
/// @author 육심현(20150803)
const FILL ECSDB::get_empty(Position pos) const{
	return empty[pos.get_x() * width + pos.get_y()];
}
/// @author 육심현(20150803)
std::vector<FILL>& ECSDB::get_mut_empty(){
	return empty;
}
/// @author 육심현(20150803)
DIRECTION ECSDB::get_last_direction() const{
	return last_direction;
}

// Setter
/// @author 육심현(20150803)
void ECSDB::set_death(bool value){ 
	player_death = value; 
}
/// @author 육심현(20150803)
void ECSDB::set_sucess(bool value){ 
	player_success = value; 
}
/// @author 육심현(20150803)
void ECSDB::push_snake(PlayerBody body){
	snake.push_back(body);
}
/// @author 육심현(20150803)
void ECSDB::pop_snake(){
	snake.pop_back();
}
/// @author 류희재(20191587)
WINDOW* ECSDB::get_scoreboard() const{
	return scoreboard;
}
/// @author 류희재(20191587)
WINDOW* ECSDB::get_playboard() const{
	return playboard;
}
/// @author 류희재(20191587)
WINDOW* ECSDB::get_titleboard() const{
	return titleboard;
}
/// @author 육심현(20150803)
void ECSDB::set_portal(Portal portal){
	this->portal = portal;
}
/// @author 육심현(20150803)
void ECSDB::set_growth(Item item){
	growth.push_back(item);
}
/// @author 육심현(20150803)
void ECSDB::set_poison(Item item){
	poison.push_back(item);
}
/// @author 육심현(20150803)
void ECSDB::set_snake_map(Position pos, char ch){
	snake_map[pos.get_x()-1][pos.get_y()-1] = ch;
}
/// @author 육심현(20150803)
void ECSDB::set_empty(Position pos, FILL fill){
	empty[pos.get_x() * width + pos.get_y()] = fill;
}
/// @author 육심현(20150803)
void ECSDB::set_empty(int x, int y, FILL fill){
	empty[x * width + y] = fill;
}
/// @author 육심현(20150803)
void ECSDB::set_last_direction(DIRECTION direction){
	last_direction = direction;
}
/// @author 류희재(20191587)
void ECSDB::set_growth_counter(int increment){
	growth_counter += increment;
}
/// @author 류희재(20191587)
void ECSDB::set_poison_counter(int increment){
	poison_counter += increment;
}
/// @author 류희재(20191587)
void ECSDB::set_gate_counter(int increment){
	gate_counter += increment;
}
/// @author 류희재(20191587)
int ECSDB::get_growth_qual() const{
	return growth_qual;
}
/// @author 류희재(20191587)
int ECSDB::get_poison_qual() const{
	return poison_qual;
}
/// @author 류희재(20191587)
int ECSDB::get_length_qual() const{
	return length_qual;
}
/// @author 류희재(20191587)
int ECSDB::get_gate_qual() const{
	return gate_qual;
}
/// @author 류희재(20191587)
int ECSDB::get_growth_counter() const{
	return growth_counter;
}
/// @author 류희재(20191587)
int ECSDB::get_poison_counter() const{
	return poison_counter;
}
/// @author 류희재(20191587)
int ECSDB::get_gate_counter() const{
	return gate_counter;
}
/// @author 육심현(20150803)
const std::vector<std::vector<char>>& ECSDB::get_snake_map() const{
	return snake_map;
}
/// @author 육심현(20150803)
std::vector<std::vector<char>>& ECSDB::get_mut_snake_map(){
	return snake_map;
}
/// @author 류희재(20191587)
bool ECSDB::get_gate_ok() const{
	return gate_ok;
}
/// @author 류희재(20191587)
bool ECSDB::get_growth_ok() const{
	return growth_ok;
}
/// @author 류희재(20191587)
bool ECSDB::get_poison_ok() const{
	return poison_ok;
}
/// @author 류희재(20191587)
bool ECSDB::get_length_ok() const{
	return length_ok;
}
/// @author 류희재(20191587)
int ECSDB::get_max_length() const{
	return max_length;
}
/// @author 류희재(20191587)
void ECSDB::set_screen(WINDOW* play, WINDOW* score,WINDOW* title){
	playboard = play;
	scoreboard = score;
	titleboard = title;
}
/// @author 류희재(20191587)
void ECSDB::set_gate_ok(bool value){gate_ok = value;}
/// @author 류희재(20191587)
void ECSDB::set_growth_ok(bool value){growth_ok = value;}
/// @author 류희재(20191587)
void ECSDB::set_poison_ok(bool value){poison_ok = value;}
/// @author 류희재(20191587)
void ECSDB::set_length_ok(bool value){length_ok = value;}
