#include "itemsystem.hpp"
#include "item.hpp"
#include "playerbody.hpp"
#include <algorithm>

void ItemSystem::spawn_growth(PosVc& empty, ItmVc& growth){
	int idx = Util::get_rand(0, empty.size() -1);
	growth.push_back(Item(empty[idx]));
	empty.erase(empty.begin() + idx);
}

void ItemSystem::spawn_poison(PosVc& empty, ItmVc& poison){
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
	Position following(static_cast<int>(parent.get_direction())%2,- static_cast<int>(parent.get_direction())/2 );
	//following += parent.get_pos();
	return following;
}

void ItemSystem::process(ECSDB& db){
	ITEMTYPE result = check_item_interaction(db.get_snake()[0], db.get_growth(), db.get_posion());

	switch (result) {
		case ITEMTYPE::DEC: {
			db.get_snake().pop_back();
			break;
		}

		case ITEMTYPE::INC: {
			// Make sure former_tail is referenced
			PlayerBody& former_tail = db.get_snake().back();
			PlayerBody new_tail = PlayerBody(former_tail.get_direction() ,get_following_position(former_tail));
			db.get_snake().push_back(new_tail);
			break;
		}

		case ITEMTYPE::NONE:
			break;

		default:
			break;
	}
};
