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
	static constexpr int width = 10;

	/** \brief 게임 화면의 크기
	 *	점수판의 크기와 너비와 동일하다.
	 */
	static constexpr int height = 10;

	/** \brief 플레이어의 죽음 여부를 저장하는 변수
	 *	
	 */
	bool player_death= false;

	/** \brief 플레이어 몸체 컴포넌트
	 *	
	 */
	std::vector<PlayerBody> snake;

	/** \brief 벽 컴포넌트
	 *	
	 */
	PosVc walls = PosVc{};

	/** \brief 빈 공간 컴포넌트
	 *	
	 */
	PosVc empty = PosVc{};

	/** \brief 포탈 컴포넌트
	 *	
	 */
	Portal portal;

	/** \brief 크기 증가 아이템 컴포넌트
	 *	
	 */
	ItmVc growth = ItmVc{};

	/** \brief 크기 감소 아이템 컴포넌트
	 *	
	 */
	ItmVc poison = ItmVc{};

	std::queue<char> console_inputs; // Placeholder
public:

	/** \brief 렌더 정보를 담는 char 2차 배열
	 *	2차원 배열이 아닌 다른 걸로 구현하는 것이 더 편하고 빠르다.
	 */
	char snake_map[width][height];

	ECSDB();

	const long get_time() const;
	const std::pair<int, int> get_measure();
	//const char** get_snakemap() const;
	void update_snake_map();
	std::vector<PlayerBody>& get_snake();
	PlayerBody& get_head();
	const bool get_death() const;
	const PosVc& get_walls() const;
	const Portal& get_portal() const;
	ItmVc& get_growth();
	ItmVc& get_poison();
	PosVc& get_empty();

	const std::queue<char> get_inputs(); // Placeholder

	void set_death(bool value);
	void set_snake(bool increment);
	void set_portal(Portal);
	void set_growth(Position);
	void set_poison(Position);
	void set_snake_map(Position, char);
	void remove_empty(Position);

	void set_input(char input); // Placeholder
};

#endif
