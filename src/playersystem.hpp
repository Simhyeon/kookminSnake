#ifndef PLAYER_H
#define PLAYER_H

#include "commons.hpp"
#include "ecsdb.hpp"
#include "playerbody.hpp"
/** \brief 아이템을 처리하는 시스템
 *
 * 아이템의 생성, 소멸과 아이템 효과의 적용을 처리하는 시스템
 */
class PlayerBodySystem {
private:

	const int min_length = 3;

	bool check_valid_direction(DIRECTION direction, PlayerBody& head);

	/** \brief 방향을 바꾸는 함수
	 * @param direction 머리에 설정할 방향값
	 * @param head 방향을 바꿀 머리
	 * @return 방향 전화에 실패한 경우 참을 리턴, 실패시의 페널티는 죽음
	 */
	// 변경된 queue로 수정하자. 
	void change_direction(DIRECTION direction, std::vector<PlayerBody>& bodies);

	/** \brief 플레이어를 이동시키는 함수
	 * @param bodies 이동할 모든 PlayerBody 값
	 */
	void move(std::vector<PlayerBody>& bodies);

	/** \brief 플레이어를 길이를 검사하는 함수
	 * @param size 검사할 길이
	 * @return 최소값 충족 여부
	 */
	bool check_length(int size);

	/** \brief 콘솔 입력을 가져오는 함수 : PLACEHOLDER
	 */
	std::pair<bool, DIRECTION> get_console_input(char);
public:	

	/** \brief 플레이어 바디 시스템의 역할을 작동시키는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
	void process(ECSDB&);
};

#endif
