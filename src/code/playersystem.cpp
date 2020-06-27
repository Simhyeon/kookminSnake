/**
 * @file playersystem.cpp
 *
 * @author 육심현(20150803)
 *
 */

#include "playersystem.hpp"
#include "commons.hpp"
#include "playerbody.hpp"

// 플레이어 노드(PlayerBody)들의 방향을 바꾸는 함수
// 노드들을 순회하며 각각의 큐에 방향 값을 뒤에 넣는다. 
/// @author 육심현(20150803)
void PlayerBodySystem::change_direction(DIRECTION direction, std::vector<PlayerBody>& bodies){
	for(PlayerBody& item: bodies){
  		item.push_direction(direction);
    }
}

// 플레이어 노드 길이를 검사하는 함수
// 특정 길이를 만족하지 못한다면 false를 반환한다.
/// @author 육심현(20150803)
bool PlayerBodySystem::check_length(int size) {
	if (size < min_length) {
		return true;
	} else {
		return false;
	}
}

// 플레이어 바디 시스템의 역할을 트리거하는 함수
/// @author 육심현(20150803)
void PlayerBodySystem::process(ECSDB& db) {
	// 길이가 부족하다면 다른 연산을 실행하지 않는다.
	// 그리고 플레이어를 죽은 것으로 한다.
	if (check_length(db.get_snake().size())){
		db.set_death(true);
		return;
	}

	// 가장 마지막으로 입력된 방향을 설정한다. 
	// 사용자가 아무런 입력을 주지 않았다면 이전의 방향을 그대로 사용한다.
	// 그리고 입력 방향을 모든 플레이어 노드에 설정한다.
	DIRECTION next = db.get_last_direction();
	change_direction(next, db.get_mut_snake());

	// process 함수에서는 플레이어 노드들이 1번씩 움직이므로 
	// 이동 후에는 이전의 꼬리의 위치가 비게 되고 
	// 현재 머리의 위치가 차게 된다
	// 그에 따라 db의 empty 지도를 설정한다.
	Position last_pos = db.get_snake()[db.get_snake().size() -1].get_pos(); 
	db.set_empty(last_pos.get_x(), last_pos.get_y(), FILL::EMPTY);
	move(db.get_mut_snake());
	db.set_empty(db.get_snake()[0].get_pos().get_x(), db.get_snake()[0].get_pos().get_y(), FILL::FILL);
}

// 플레이어 노드들을 방향에 따라 한 번 씩 움직이게 한다.
// 이동 후에는 자기 인덱스와 동일한 크기의 방향 큐를 가지게 된다.
// e.g)
//			    [0]       [1]      [2]        [3]
// ------------------------------------------------------
// 방향 설정전: '  '	'상	   ' '우,상   '	'상,우,상   '
// ------------------------------------------------------
// 방향 이동전: '좌'	'상, 좌' '우,상,좌'	'상,우,상,좌'
// ------------------------------------------------------
// 방향 이동후: '  '	'좌	   ' '상,좌   '	'우,상,좌   '
// ------------------------------------------------------
//
// 노드가 이동할 위치를 부모 노드에 의존하지 않고 
// 독자적인 큐 데이터를 통해서 구현할 경우
// 노드 (컴포넌트)들은 시스템에 의해서 독립 실행 연산의 
// 대상이 될 수 있다. 즉 DOD에 더 적합한 구현이다.
/// @author 육심현(20150803)
void PlayerBodySystem::move(std::vector<PlayerBody>& bodies){
	for (PlayerBody& body : bodies){
		int dirct = static_cast<int>(body.pop_direction());
		body.increment_pos(dirct%2, -dirct/2);
		body.set_last_dir(static_cast<DIRECTION>(dirct));
	}
}
