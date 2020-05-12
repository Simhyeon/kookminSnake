#include "itemsystem.hpp"
#include "commons.hpp"
#include "playerbody.hpp"

void ItemSystem::spawn_goodies(PosVc& empty, PosVc& goodies){
	// Get random number from size of empty
	// Add goodies to area and add to vector and remove from empty
}

void ItemSystem::spawn_poison(PosVc& empty, PosVc& poison){
	// Get random number from size of empty
	// Add poision to area and add to vector and remove from empty
}

void ItemSystem::remove_goodies(int entity_index){

};

void ItemSystem::remove_poison(int entity_index){

};

ITEMTYPE ItemSystem::check_item_interaction(PlayerBody& head, const PosVc& goodies, const PosVc& poison){
	for(Position pos: goodies){
		if(pos == head.get_pos()){
			return ITEMTYPE::INC;			
		}
	}

	for (Position pos: poison){
		if(pos == head.get_pos()){
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
	ITEMTYPE item_type = check_item_interaction(db.get_snake()[0], db.get_goodies(), db.get_posions());

	switch (item_type) {
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
