#ifndef ECSDB_H
#define ECSDB_H

#include "commons.hpp"
#include "item.hpp"
#include "portal.hpp"
#include "playerbody.hpp"
#include <vector>
#include <queue>

class ECSDB{
private:
	/** \breif 게임을 시작한 시간을 저장한 값
	 *
	 * Readable한 시간으로 나타나진 않으며 지나간 시간을 검사하는데 쓰인다.
	 */
	const long start_time;
	/** \brief 게임 화면의 너비
	 *	점수판의 크기와 너비와 동일하다.
	 */
	const int width;

	/** \brief 게임 화면의 크기
	 *	점수판의 크기와 너비와 동일하다.
	 */
	const int height;

	/** \brief 플레이어의 죽음 여부를 저장하는 변수
	 *	
	 */
	bool player_death;

	/** \brief 플레이어 몸체 컴포넌트
	 *	
	 */
	std::vector<PlayerBody> snake;

	/** \brief 벽 컴포넌트
	 *	
	 */
	PosVc walls;

	/** \brief 빈 공간 컴포넌트
	 *	
	 */
	PosVc empty;

	/** \brief 포탈 컴포넌트
	 *	
	 */
	Portal portal;

	/** \brief 크기 증가 아이템 컴포넌트
	 *	
	 */
	ItmVc growth;

	/** \brief 크기 감소 아이템 컴포넌트
	 *	
	 */
	ItmVc poison;

	std::queue<char> console_inputs; // Placeholder
public:
	ECSDB();

	const long get_time() const;
	const std::pair<int, int> get_measure() const;
	std::vector<PlayerBody>& get_snake();
	PlayerBody& get_head();
	const bool get_death() const;
	const PosVc& get_walls() const;
	const Portal& get_portal() const;
	ItmVc& get_growth();
	ItmVc& get_posion();

	const std::queue<char> get_inputs(); // Placeholder

	void set_death(bool value);
	void set_snake(bool increment);
	void set_portal(Position first, Position second);
	void set_growth(Position);
	void set_poison(Position);

	void set_input(char input); // Placeholder
};

#endif
