/**
 * @file playersystem.hpp
 *
 * @author 육심현(20150803)
 *
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "commons.hpp"
#include "ecsdb.hpp"
#include "playerbody.hpp"
/** \brief 플레이어 행동을 처리하는 시스템
 *
 * @author 육심현(20150803)
 * 
 * 플레이어의 움직임, 방향설정을 처리하는 시스템
 */
class PlayerBodySystem {
private:

	/// 플레이어가 유지해야 하는 최소 길이, 이보다 짧아질 경우에는 죽는다.
	const int min_length = 3;

	/** \brief 플레이어 노드들의 방향을 바꾸는 함수
	 * 
	 * @author 육심현(20150803)
	 * 
	 * @param direction 설정할 방향값
	 * @param bodies 방향을 설정할 플레이어 노드들
	 */
	void change_direction(DIRECTION direction, std::vector<PlayerBody>& bodies);

	/** \brief 플레이어를 이동시키는 함수
	 * 
	 * @author 육심현(20150803)
	 * 
	 * @param bodies 이동할 모든 PlayerBody 값
	 */
	void move(std::vector<PlayerBody>& bodies);

	/** \brief 플레이어를 길이를 검사하는 함수
	 * 
	 * @author 육심현(20150803)
	 * 
	 * @param size 검사할 길이
	 * @return 최소값 충족 여부
	 */
	bool check_length(int size);

	std::pair<bool, DIRECTION> get_console_input(char);
public:	

	/** \brief 플레이어 바디 시스템의 역할을 작동시키는 함수
	 *
	 * @author 육심현(20150803)
	 * 
	 * @param db ECS 데이터베이스
	 */
	void process(ECSDB&);
};

#endif
