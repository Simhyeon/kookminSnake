#include "itemsystem.hpp"
#include "commons.hpp"
#include "ecsdb.hpp"
#include "item.hpp"
#include "playerbody.hpp"
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>

// 현재 스폰 구조는 3개를 무조건 꽉꽉 채우는 구조다. 
// 그것도 한번에 지운뒤 한 번씩 차례차례 추가한다. 
// 3개가 아니면 무조건 칸을 채운다.
void ItemSystem::spawn_growth(std::vector<FILL>& empty, ItmVc& growth, int width, int height){
	if (growth.size() >= item_size){return;}
	int idx = Util::get_rand(0, empty.size() -1);
	auto it = empty.begin();
	while (*(it+idx) != FILL::EMPTY){
		idx = Util::get_rand(0, empty.size() -1);
	}
	growth.push_back(Item(Position(idx / width,idx % width)));
	empty[idx] = FILL::FILL;
}

void ItemSystem::spawn_poison(std::vector<FILL>& empty, ItmVc& poison, int width, int height){
	if (poison.size() >= item_size){return;}
	int idx = Util::get_rand(0, empty.size() -1);
	auto it = empty.begin();
	while (*(it+idx) != FILL::EMPTY){
		idx = Util::get_rand(0, empty.size() -1);
	}
	poison.push_back(Item(Position(idx / width,idx % width)));
	empty[idx] = FILL::FILL;
}

std::pair<bool, Position> ItemSystem::remove_growth(ItmVc& growth){
	for(auto it = growth.begin(); it != growth.end(); it++){
		if (Util::get_time() - (*it).timestamp >= item_time){
			Position cache(it->get_pos());
			growth.erase(it);
			return std::pair<bool,Position>(true, cache);
		}
	}
	return std::pair<bool,Position>(false, Position(-1,-1));
};

std::pair<bool, Position> ItemSystem::remove_poison(ItmVc& poison){
	for(auto it = poison.begin(); it != poison.end(); it++){
		if (Util::get_time() - (*it).timestamp >= item_time){
			Position cache(it->get_pos());
			poison.erase(it);
			return std::pair<bool,Position>(true, cache);
		}
	}
	return std::pair<bool,Position>(false, Position(-1,-1));
};

ITEMTYPE ItemSystem::check_item_interaction(const PlayerBody& head, ItmVc& growth, ItmVc& poison){
	for(auto it = growth.begin(); it != growth.end(); it++){
		if((*it).pos == head.get_pos()){	
			growth.erase(it);
			return ITEMTYPE::INC;
		}
	}

	for(auto it = poison.begin(); it != poison.end(); it++){
		if((*it).pos == head.get_pos()){
			poison.erase(it);
			return ITEMTYPE::DEC;
		}
	}

	return ITEMTYPE::NONE;
};

Position ItemSystem::get_following_position(const PlayerBody& parent) {
	int direction = static_cast<int>(parent.get_direction()) * -1;
	Position following(direction%2, -direction/2 );
	following += parent.get_pos();
	return following;
}

void ItemSystem::process(ECSDB& db){
	ITEMTYPE result = check_item_interaction(db.get_head(), db.get_mut_growth(), db.get_mut_poison());

	switch (result) {
		case ITEMTYPE::DEC: {
			Position pos = db.get_snake().back().get_pos();
			db.set_empty(pos.get_x(), pos.get_y(), FILL::EMPTY);
			db.pop_snake();
			break;
		}

		case ITEMTYPE::INC: {
			const PlayerBody& former_tail = db.get_tail();
			PlayerBody new_tail = PlayerBody(get_following_position(former_tail), former_tail.get_dir_queue());

			new_tail.push_direction_front(former_tail.get_direction());

			db.push_snake(new_tail);
			db.set_empty(new_tail.get_pos().get_x(), new_tail.get_pos().get_y(), FILL::FILL);
			break;
		}

		case ITEMTYPE::NONE:
			break;

		default:
			break;
	}
	
	// Check existing items
	auto growth_result = remove_growth(db.get_mut_growth());
	if (growth_result.first){
		db.set_empty(growth_result.second, FILL::EMPTY);
	}

	auto poison_result = remove_poison(db.get_mut_poison());
	if (poison_result.first){
		db.set_empty(poison_result.second, FILL::EMPTY);
	}

	// Set_item을 안 쓰는 구조다. 
	spawn_growth(db.get_mut_empty(), db.get_mut_growth(), db.get_measure().first, db.get_measure().second);
	spawn_poison(db.get_mut_empty(), db.get_mut_poison(), db.get_measure().first, db.get_measure().second);
};
