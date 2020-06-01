#ifndef ECSDB_H
#define ECSDB_H

#include "commons.hpp"
#include "item.hpp"
#include "portal.hpp"
#include "playerbody.hpp"
#include <vector>
#include <queue>
#include <memory>

class ECSDB{
private:
	/** \breif 게임을 시작한 시간을 저장한 값
	 *
	 * Readable한 시간으로 나타나진 않으며 지나간 시간을 검사하는데 쓰인다.
	 */
	long start_time;
	/** \brief 게임 화면의 너비
	 *	점수판의 크기와 너비와 동일하다.
	 */
	int width = 0;

	/** \brief 게임 화면의 크기
	 *	점수판의 크기와 너비와 동일하다.
	 */
	int height = 0;

	/** \brief 플레이어의 죽음 여부를 저장하는 변수
	 *	
	 */
	bool player_death = false;
	bool player_success = false;

	/** \brief 플레이어 몸체 컴포넌트
	 *	
	 */
	std::vector<PlayerBody> snake;

	/** \brief 벽 컴포넌트
	 *	
	 */
	PosVc walls = PosVc{};

	/** \brief 영구 벽 컴포넌트
	 *	
	 */
	PosVc iwalls = PosVc{};

	/** \brief 빈 공간 컴포넌트
	 *	
	 */
	std::vector<FILL> empty;

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

	DIRECTION last_direction; 

	/** \brief 획득한 growth 아이템 카운터
	 *	
	 */
	int growth_counter = 0;

	/** \brief 획득한 poison 아이템 카운터
	 *	
	 */
	int poison_counter = 0;
public:

	/** \brief 렌더 정보를 담는 char 2차 배열
	 *	
	 */
	char** snake_map;

	// 나중에 private로 옮겨야 한다.

	//Constructor
	ECSDB();
	ECSDB(int width, int height, char** snake_map, DIRECTION snake_direction);
	void Init(int width, int height, char** snake_map, DIRECTION snake_direction);

	// Update snake_map, should be renderer function
	void update_snake_map();

	// Get time
	const long get_time() const;

	// Get Death
	const bool get_death() const;
	const bool get_success() const;

	// Get measurement
	const std::pair<int, int> get_measure() const;
	int get_width() const;
	int get_height() const;

	// Get Player body or snake
	const std::vector<PlayerBody>& get_snake() const;
	std::vector<PlayerBody>& get_mut_snake();
	const PlayerBody& get_head() const;
	const PlayerBody& get_tail() const;
	const PosVc& get_walls() const;
	PosVc& get_mut_walls();

	const PosVc& get_iwalls() const;

	const Portal& get_portal() const;

	const ItmVc& get_growth() const;
	ItmVc& get_mut_growth();

	const ItmVc& get_poison() const;
	ItmVc& get_mut_poison();

	const std::vector<FILL>& get_empty() const;
	const FILL get_empty(int x, int y) const;
	const FILL get_empty(Position pos) const;
	std::vector<FILL>& get_mut_empty();

	DIRECTION get_last_direction() const;
	const std::pair<int, int> get_item_counter() const;

	const std::queue<char> get_inputs(); // Placeholder

	void set_death(bool value);
	void set_sucess(bool value);
	void push_snake(PlayerBody body);
	void pop_snake();
	void set_portal(Portal);
	void set_growth(Item);
	void set_poison(Item);
	void set_snake_map(Position, char);
	void set_empty(Position position, FILL value);
	void set_empty(int x, int y, FILL value);

	void set_input(char input); // Placeholder

	void set_last_direction(DIRECTION direction);
	void set_growth_counter(int increment);
	void set_poison_counter(int increment);
};

#endif
