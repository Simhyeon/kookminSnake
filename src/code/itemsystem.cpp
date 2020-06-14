#include "itemsystem.hpp"
#include "commons.hpp"
#include "ecsdb.hpp"
#include "item.hpp"
#include "playerbody.hpp"
#include <algorithm>
#include <cstdio>
#include <vector>
#include <iostream>

// 아이템을 생성한다.
// 아이템은 최대 개수인 경우에는 생성하지 않는다.
// 아이템을 생성할 공간은 empty 배열에서 랜덤하게 인덱스를 설정한 뒤 
// 해당 인덱스에 해당하는 좌표값을 계산하여 정한다.
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

// spawn_growth 와 동일한 메커니즘이다. 
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

// 아이템을 순환하며 아이템의 지속시간이 다했는가를 검사한다.
// 지속시간이 지난 아이템은 삭제하고 삭제 여부를 리턴한다.
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

// remove_growth 와 동일한 메커니즘이다. 
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

// 아이템들을 순환하며 플레이어가 아이템을 먹었는지 확인한다.
// 플레이어와 아이템의 위치가 동일하다면 아이템을 먹은 것으로 한다.
// 아이템과 상호작용한 경우에는 상호작용의 종류를 리턴한다.
ITEMTYPE ItemSystem::check_item_interaction(const PlayerBody& head, ItmVc& growth, ItmVc& poison){
	// 증가 아이템을 검사한다.
	for(auto it = growth.begin(); it != growth.end(); it++){
		if((*it).pos == head.get_pos()){	
			growth.erase(it);
			return ITEMTYPE::INC;
		}
	}

	// 독 아이템을 검사한다.
	for(auto it = poison.begin(); it != poison.end(); it++){
		if((*it).pos == head.get_pos()){
			poison.erase(it);
			return ITEMTYPE::DEC;
		}
	}

	return ITEMTYPE::NONE;
};

// 아이템을 생성할 위치를 알아오는 함수로써 
// 플레이어의 꼬리 위치에서 꼬리의 마지막 방향으로 -1 만큼 이동한
// 좌표를 반환한다.
Position ItemSystem::get_following_position(const PlayerBody& parent) {
	int direction = static_cast<int>(parent.get_last_dir()) * -1;
	Position following(direction%2, -direction/2 );
	following += parent.get_pos();
	return following;
}

// 아이템 시스템의 모든 일을 트리거한다.
void ItemSystem::process(ECSDB& db){
	// 아이템 상호작용 여부를 검사하고
	ITEMTYPE result = check_item_interaction(db.get_head(), db.get_mut_growth(), db.get_mut_poison());
	// 상호작용 결과에 따라 크기를 늘이거나 줄어거나 
	// 아무것도 하지 않는다.
	switch (result) {
		case ITEMTYPE::DEC: {
			Position pos = db.get_snake().back().get_pos();
			db.set_empty(pos.get_x(), pos.get_y(), FILL::EMPTY);
			db.pop_snake();
			db.set_poison_counter(1);
			break;
		}

		// 크기가 늘어나는 경우에는 생성할 새로운 꼬리의
		// 위치와 방향 큐를 생성하여 할당한다.
		// 새로운 꼬리의 방향 큐는 이전의 꼬리의 큐를 복사한 뒤 
		// 이전의 꼬리의 이전 방향을 새로운 꼬리의 방향 큐의
		// 가장 앞으로 push 하여 구한다.
		// e.g) 
		// 만약 '좌'로 이동한 이전 꼬리의 방향 큐가 '좌, 상, 상' 이라면 
		// 새로운 꼬리의 방향 큐는 '좌, 상, 상'의 앞에 '좌' 를 넣어
		// 최종적으로는 '좌, 좌, 상, 상'이 된다.
		case ITEMTYPE::INC: {
			// if (db.get_max_length() <= db.get_snake().size()){
			// 	break;
			// }
			const PlayerBody& former_tail = db.get_tail();
			PlayerBody new_tail = PlayerBody(get_following_position(former_tail), former_tail.get_dir_queue());

			new_tail.push_direction_front(former_tail.get_last_dir());

			db.push_snake(new_tail);
			db.set_empty(new_tail.get_pos().get_x(), new_tail.get_pos().get_y(), FILL::FILL);
			db.set_growth_counter(1);
			break;
		}

		case ITEMTYPE::NONE:
			break;

		default:
			break;
	}
	
	// 생성된 아이템들이 지속시간이 지났는가를 검사한다.
	// 증가 아이템
	auto growth_result = remove_growth(db.get_mut_growth());
	if (growth_result.first){
		db.set_empty(growth_result.second, FILL::EMPTY);
	}

	// 독 아이템
	auto poison_result = remove_poison(db.get_mut_poison());
	if (poison_result.first){
		db.set_empty(poison_result.second, FILL::EMPTY);
	}

	// 새로이 아이템을 생성할 수 있는지를 검사하고 가능하다면 
	// 새로운 아이템을 생성한다.
	spawn_growth(db.get_mut_empty(), db.get_mut_growth(), db.get_measure().first, db.get_measure().second);
	spawn_poison(db.get_mut_empty(), db.get_mut_poison(), db.get_measure().first, db.get_measure().second);
};
