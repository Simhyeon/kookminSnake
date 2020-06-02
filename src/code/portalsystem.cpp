#include "commons.hpp"
#include "ecsdb.hpp"
#include "playerbody.hpp"
#include "portal.hpp"
#include "portalsystem.hpp"
#include <algorithm>
#include <array>
#include <exception>

// 그저 게이트에 도달한 플레이어 노드(PlayerBody) 이동시키는 역할이다.
void PortalSystem::jump_snake(PlayerBody& body, Position destination) {
	body.set_pos(destination.get_x(), destination.get_y());
}

// 플레이어 노드가 어디로 어떤 방향을 가지고 이동되어야 하는가를 계산하는 함수다.
// 게이트의 위치가 지도의 끝에 있다면 정해진 값을 반환한다.
// 게이트의 위치가 지도의 중앙에 있다면 
// 정방향, 시계 방향, 역시계 방향, 역방향 순서로 비어있는 공간을 검색한 뒤
// 먼저 비어있는 공간을 찾으면 해당 공간과 그 공간으로의 방향을 같이 반환한다.
std::pair<Position, DIRECTION> PortalSystem::get_jump_result(Position destination,int body_nubmer, ECSDB& db){

	// 게이트가 지도 가장자리에 있는 경우엔 정해진 위치와 방향을 반환한다.
	if (destination.get_x() == 0) {
		return std::pair<Position,DIRECTION>(
				Util::get_modified_pos(destination, DIRECTION::RIGHT), 
				DIRECTION::RIGHT
				);
	} else if (destination.get_x() == db.get_width() -1) {
		return std::pair<Position,DIRECTION>(
				Util::get_modified_pos(destination, DIRECTION::LEFT), 
				DIRECTION::LEFT
				);
	} else if (destination.get_y() == 0) {
		return std::pair<Position,DIRECTION>(
				Util::get_modified_pos(destination, DIRECTION::DOWN), 
				DIRECTION::DOWN
				);
	} else if (destination.get_y() == db.get_height() - 1) {
		return std::pair<Position,DIRECTION>(
				Util::get_modified_pos(destination, DIRECTION::UP), 
				DIRECTION::UP
				);
	} 

	// TODO 코드가 난잡하다
	// 게이트가 지도 중앙에 경우엔 이동시킬 위치와 방향을 계산한다.
	PosVc walls = db.get_walls();
	walls.insert(walls.end(), db.get_iwalls().begin(), db.get_iwalls().end());
	DIRECTION last_dir = db.get_snake()[body_nubmer].get_last_dir();

	DIRECTION new_dir = db.get_snake()[body_nubmer].get_last_dir();
	Position new_pos =  Util::get_modified_pos(destination, new_dir);

	// 정방향
	if (std::find_if(walls.begin(), walls.end(), [&](const Position& wall){return wall == new_pos;}) == walls.end()){
		return std::pair<Position, DIRECTION>(new_pos, new_dir);
	}

	// 시계방향
	new_dir = Util::rotate_dir(last_dir, DIRECTION::LEFT);
	new_pos =  Util::get_modified_pos(destination, new_dir);

	if (std::find_if(walls.begin(), walls.end(), [&](const Position& wall){return wall == new_pos;}) == walls.end()){
		return std::pair<Position, DIRECTION>(new_pos, new_dir);
	}

	// 역시계방향
	new_dir = Util::rotate_dir(last_dir, DIRECTION::RIGHT);
	new_pos =  Util::get_modified_pos(destination, new_dir);

	if (std::find_if(walls.begin(), walls.end(), [&](const Position& wall){return wall == new_pos;}) == walls.end()){
		return std::pair<Position, DIRECTION>(new_pos, new_dir);
	}

	// 역방향
	new_dir = Util::get_reverse_dir(last_dir);
	new_pos = Util::get_modified_pos(destination, new_dir);

	if (std::find_if(walls.begin(), walls.end(), [&](const Position& wall){return wall == new_pos;}) == walls.end()){
		return std::pair<Position, DIRECTION>(new_pos, new_dir);
	}

	// This is logical error 
	// At least one side should be open if it is not w immune wall.
	throw std::exception();
}

// 새로운 위치에 게이트를 생성한다.
// 새로운 위치는 벽 중에서 무작위로 선정된다.
// 단 게이트의 엔트리 끼리는 최소한 3 이상의 맨해튼 거리를 가져야 한다.
// 2 이하인 경우에는 게이트를 통과하기가 힘들어 지는 경우가 발생한다.
// 
// e.g)
// O = 게이트, * = 벽 , @ = 머리, # = 몸통, ` = 비어있음
// 맨해튼 거리 = 2
// * O * *
// O ` @ #
// * ` ` `
//
// 위와 같은 경우에는 게이트를 탄 뒤에는 
// 플레이어가 살아남을 방도가 없다.
// 한편, 
// 맨해튼 거리 = 3
// * * O *
// O ` @ #
// * ` ` `
//
// 위와 같은 경우에는 게이트를 타는 방향에 따라서는
// 살 수 있다.
Portal PortalSystem::regen_portal(const Portal& portal, PosVc& walls) {
	int first, second;
	int wall_size = walls.size();
	Position first_pos, second_pos;
	first = Util::get_rand(0, walls.size() - 1);
	first_pos = Position(walls[first]);

	// 게이트를 생성할 위치를 가진 벽 컴포넌트를 
	// 마지막 인덱스 벽 컴포넌트와 스왑한 뒤
	// pop 하면 insert연산 없이 지울 수 있다.
	// 순서가 중요하지 않기 때문에 실질적으로 erase와 동일하다.
	std::swap(walls[first], walls[wall_size-1]);
	walls.pop_back();
	wall_size = walls.size();

	// 두번째 엔트리는 맨해튼 거리가 3이상일 때까지 뽑는다.
	second = Util::get_rand(0, walls.size() - 1);
	while (walls[first].get_manhattan(walls[second]) <= 2) {
		second = Util::get_rand(0, walls.size() - 1);
	}

	second_pos = Position(walls[second]);
	std::swap(walls[second], walls[wall_size-1]);
	walls.pop_back();

	// 기존의 포탈 엔트리가 차지하던 위치를
	// wall 배열에 집어넣는다. 
	if (portal.get_first_pos().get_x() != -1){
		walls.push_back(portal.get_first_pos());
		walls.push_back(portal.get_second_pos());
	}

	// TODO
	return Portal(first_pos, second_pos, DIRECTION::UP, DIRECTION::UP);
}

// 모든 플레이어 노드를 순회하면서 게이트와 동일한 위체 있는가를 검사한다.
// 게이트와 동일한 위치에 있다면(게이트와 상호작용 했다면)
// 반대편 게이트으 위치와 상호작용한 바디의 인덱스를 반환한다.
std::pair<Position, int> PortalSystem::check_portal_interaction(const std::vector<PlayerBody>& bodies, const Portal& portal){
	// TODO 
	int counter = 0;
	for (const PlayerBody& body : bodies){
		if (body.get_pos() == portal.get_first_pos()){
			return std::pair<Position, int>(portal.second_entry, counter);
		} else if (body.get_pos() == portal.get_second_pos()){
			return std::pair<Position, int>(portal.first_entry, counter);
		}
		counter++;
	}
	return std::pair<Position, int>(Position(-1,-1), -1);
}

void PortalSystem::process(ECSDB & db) {
	auto result = check_portal_interaction(db.get_snake(), db.get_portal());
	// 게이트와 부딪힌 플레이어 노드를 이동시킨다.
	if (result.second != -1){  
		std::pair<Position, DIRECTION> jump_for = get_jump_result(result.first, result.second, db);
		Position destination = Util::get_modified_pos(result.first, jump_for.second);
		jump_snake(db.get_mut_snake()[result.second], destination);
		db.set_empty(destination, FILL::FILL);
		db.set_last_direction(jump_for.second);

	} else { 
		if (Util::get_time() - db.get_portal().timestamp >= portal_time) {
			Portal portal = regen_portal(db.get_portal(), db.get_mut_walls());
			db.set_portal(portal);
		}
	}
}
