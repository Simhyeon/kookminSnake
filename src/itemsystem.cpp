#include "itemsystem.hpp"
#include "commons.hpp"
#include "item.hpp"
#include "playerbody.hpp"
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>

// 현재 스폰 구조는 3개를 무조건 꽉꽉 채우는 구조다. 
// 그것도 한번에 지운뒤 한 번씩 차례차례 추가한다. 
// 3개가 아니면 무조건 칸을 채운다.
void ItemSystem::spawn_growth(PosVc& empty, ItmVc& growth){
	if (growth.size() >= item_size){return;}
	int idx = Util::get_rand(0, empty.size() -1);
	growth.push_back(Item(empty[idx]));
	empty.erase(empty.begin() + idx);
}

void ItemSystem::spawn_poison(PosVc& empty, ItmVc& poison){
	if (poison.size() >= item_size){return;}
	int idx = Util::get_rand(0, empty.size() -1);
	poison.push_back(Item(empty[idx]));
	empty.erase(empty.begin() + idx);
}

void ItemSystem::remove_growth(ItmVc& growth){
	growth.erase(std::remove_if(growth.begin(), growth.end(), [this](Item& item) { return Util::get_time() - item.timestamp >= item_time; }), growth.end());
};

void ItemSystem::remove_poison(ItmVc& poison){
	poison.erase(std::remove_if(poison.begin(), poison.end(), [this](Item& item) { return Util::get_time() - item.timestamp >= item_time; }), poison.end());
};

ITEMTYPE ItemSystem::check_item_interaction(PlayerBody& head, ItmVc& growth, ItmVc& poison){
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

Position ItemSystem::get_following_position(PlayerBody& parent) {
	int direction = static_cast<int>(parent.get_direction()) * -1;
	Position following(direction%2, -direction/2 );
	following += parent.get_pos();
	return following;
}

void ItemSystem::process(ECSDB& db){
	ITEMTYPE result = check_item_interaction(db.get_snake()[0], db.get_growth(), db.get_poison());

	switch (result) {
		case ITEMTYPE::DEC: {
			db.get_empty().push_back(db.get_head().get_pos());
			db.get_snake().pop_back();
			break;
		}

		case ITEMTYPE::INC: {
			PlayerBody& former_tail = db.get_snake().back();
			PlayerBody new_tail = PlayerBody(get_following_position(former_tail), former_tail.get_queue());

			new_tail.push_direction_front(former_tail.get_direction());

			db.get_snake().push_back(new_tail);
			db.remove_empty(new_tail.get_pos());
			break;
		}

		case ITEMTYPE::NONE:
			break;

		default:
			break;
	}
	
	// Check existing items
	ItmVc& growth = db.get_growth();
	growth.erase(std::remove_if(growth.begin(), growth.end(), [](Item& item){return Util::get_time() - item.get_time() >= 5;}), growth.end());

	ItmVc& poison = db.get_poison();
	poison.erase(std::remove_if(poison.begin(), poison.end(), [](Item& item){return Util::get_time() - item.get_time() >= 5;}), poison.end());

	// Set_item을 안 쓰는 구조다. 
	spawn_growth(db.get_empty(), growth);
	spawn_poison(db.get_empty(), poison);
};
