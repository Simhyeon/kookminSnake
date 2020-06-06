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
ECSDB::~ECSDB(){
	delwin(playboard);
	delwin(scoreboard);
	endwin();
}
void ECSDB::Init(int width, int height, std::vector<std::vector<char>> snake_map, DIRECTION snake_direction, int growth_count, int poison_count, int gate_counter, int length) {

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
	gate_qual = gate_counter;
	growth_counter = 0;
	poison_counter = 0;
	gate_counter = 0;
	length_qual = length;

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

WINDOW* ECSDB::get_scoreboard() const{
	return scoreboard;
}
WINDOW* ECSDB::get_playboard() const{
	return playboard;
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

void ECSDB::set_gate_counter(int increment){
	gate_counter += increment;
}

int ECSDB::get_growth_qual() const{
	return growth_qual;
}
int ECSDB::get_poison_qual() const{
	return poison_qual;
}

int ECSDB::get_length_qual() const{
	return length_qual;
}

int ECSDB::get_gate_qual() const{
	return gate_qual;
}

int ECSDB::get_growth_counter() const{
	return growth_counter;
}

int ECSDB::get_poison_counter() const{
	return poison_counter;
}

int ECSDB::get_gate_counter() const{
	return gate_counter;
}
const std::vector<std::vector<char>>& ECSDB::get_snake_map() const{
	return snake_map;
}
std::vector<std::vector<char>>& ECSDB::get_mut_snake_map(){
	return snake_map;
}

bool ECSDB::get_gate_ok() const{
	return gate_ok;
}

bool ECSDB::get_growth_ok() const{
	return growth_ok;
}

bool ECSDB::get_poison_ok() const{
	return poison_ok;
}

bool ECSDB::get_length_ok() const{
	return length_ok;
}

void ECSDB::set_screen(WINDOW* play, WINDOW* score){
	scoreboard = score;
	playboard = play;
}
void ECSDB::set_gate_ok(bool value){gate_ok = value;}
void ECSDB::set_growth_ok(bool value){growth_ok = value;}
void ECSDB::set_poison_ok(bool value){poison_ok = value;}
void ECSDB::set_length_ok(bool value){length_ok = value;}
