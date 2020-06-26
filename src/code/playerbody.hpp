/**
 * @file playerbody.hpp
 *
 * @author 육심현
 *
 */

#ifndef PLAYERBODY_H
#define PLAYERBODY_H

#include "commons.hpp"
#include <queue>

/// 플레이어의(뱀)의 노드 정보를 저장하는 클래스
class PlayerBody{
private:
	/** \brief 노드가 이동할 방향을 저장하는 Queue
	 *
	 * Queue의 크기는 head가 가장 작고 뒤로 갈수록 1씩 커진다.\n
	 * 플레이어 시스템이 각각의 Node를 이동시킬 때 Queue의 front를 이동시킨다.
	 */
	std::deque<DIRECTION> dir_queue;
	/// 노드의 위치
	Position pos;
	/** \brief 노드가 움직였던 마지막 방향
	 *
	 * 아이템 효과를 적용하여 새로운 위치에 노드를 생성하기 위해서 사용된다.
	 */ 
	DIRECTION last_direction;
public:
	PlayerBody();
	PlayerBody(Position, DIRECTION direction, unsigned int body_size);
	PlayerBody(Position, std::deque<DIRECTION> copy);
	/// 가장 첫번째 방향 정보를 반환한다.
	const DIRECTION get_direction() const;
	/// 첫번째 방향 정보를 리턴하고 queue에서 Pop한다.
	DIRECTION pop_direction();
	/// 방향 정보를 queue의 뒤에 저장한다.
	void push_direction(DIRECTION);
	/// 방향 정보를 queue의 앞에 저장한다.
	void push_direction_front(DIRECTION dir);
	const Position get_pos() const;
	void increment_pos(int x, int y);
	void set_pos(const Position);
	void set_pos(int x, int y);
	DIRECTION get_last_dir() const;
	void set_last_dir(DIRECTION);

	const std::deque<DIRECTION>& get_dir_queue() const;
};

#endif
