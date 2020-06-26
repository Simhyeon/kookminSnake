/**
 * @file ecsdb.hpp
 *
 * @author 육심현 류희재
 *
 */

#ifndef ECSDB_H
#define ECSDB_H

#include "commons.hpp"
#include "item.hpp"
#include "portal.hpp"
#include "playerbody.hpp"
#include <vector>
#include <queue>
#include <memory>
#include "aliases.hpp"
#include <ncurses.h>

/** \brief 게임에서 사용할 모든 정보를 저장하는 클래스
 *
 * ECS 패턴에서 Entity와 컴포넌트를 수정한 구조로 되어 있음.
 */
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

	WINDOW *playboard;
	WINDOW *scoreboard;
	WINDOW *titleboard;

	/** \brief 게임 화면의 크기
	 *	점수판의 크기와 너비와 동일하다.
	 */
	int height = 0;

	/// 플레이어의 죽음 여부를 저장하는 변수
	bool player_death = false;
	/// 플레이어의 성공 여부를 저장하는 변수
	bool player_success = false;

	/** \brief 렌더 정보를 담는 char 2차 배열
	 *
	 *	의미하는 char는 string.hpp 파일에 포함되어 있다.
	 */
	std::vector<std::vector<char>> snake_map;

	/** \brief 플레이어 몸체 컴포넌트
	 *	PlayerBody 벡터로 구성되며 가장 첫번째 PlayerBody가 head의 역할을 한다.
	 */
	std::vector<PlayerBody> snake;

	/// 벽 컴포넌트
	PosVc walls = PosVc{};

	/// 영구 벽 컴포넌트
	/// 할당 후 내용이 변하지 않는다. 단 레벨이 바뀌면 다시 할당된다.
	PosVc iwalls = PosVc{};

	/** \brief 빈 공간 컴포넌트
	 *
	 *	FILL::FILL인 경우는 아이템이나 플레이어가 해당 위치에 있는 경우이고\n
	 *	FILL::NEVER인 경우는 벽이나 영구 벽이 위치한 곳이다\n
	 *	FILL::EMPTY인 경우는 비어있는 공간이다.\n
	 */
	std::vector<FILL> empty;

	/// Portal 컴포넌트
	Portal portal;

	/// 크기 증가 아이템 컴포넌트 ( Item )
	ItmVc growth = ItmVc{};

	/// 크기 감소 아이템 컴포넌트 ( Item )
	ItmVc poison = ItmVc{};

	std::queue<char> console_inputs; // Placeholder

	/** \brief 마지막으로 입력된 방향 값을 저장하는 변수
	 *
	 * 새로운 입력이 없다면 이 변수를 재사용한다.
	 */
	DIRECTION last_direction; 

	///레벨에서 성공에 필요한 growth 아이템 개수
	int growth_qual = 3;

	/** \brief 획득한 growth 아이템 카운터
	 *
	 *	레벨 성공 여부를 결정한다.
	 */
	int growth_counter = 0;

	///레벨에서 성공에 필요한 poison 아이템 개수
	int poison_qual = 3;

	/** \brief 획득한 poison 아이템 카운터
	 *
	 *	레벨 성공 여부를 결정한다.
	 */
	int poison_counter = 0;

	///레벨에서 성공에 필요한 게이트 통과 회수
	int gate_qual = 3;

	/** \brief 획득한 poison 아이템 카운터
	 *
	 *	레벨 성공 여부를 결정한다.
	 */
	int gate_counter = 0;

	///레벨에서 성공에 필요한 뱀의 길이
	int length_qual = 0;

	bool gate_ok = false;
	bool growth_ok = false;
	bool poison_ok = false;
	bool length_ok = false;
	int max_length = 0;
public:


	/// 빈 생성자
	ECSDB();
	~ECSDB();
	/// 변수를 받는 생성자
	ECSDB(int width, int height, std::vector<std::vector<char>> snake_map, DIRECTION snake_direction);
	void Init(int width, int height, std::vector<std::vector<char>> snake_map, DIRECTION snake_direction, int growth_count, int poison_count, int gate_count, int length, int max_length);

	// Update snake_map, should be renderer function
	void update_snake_map();

	/// 시작한 시간을 리턴하는 함수
	const long get_time() const;

	const bool get_death() const;
	const bool get_success() const;

	/// width, height를 pair의 형태로 반환하는 함수
	const std::pair<int, int> get_measure() const;
	int get_width() const;
	int get_height() const;

	const std::vector<std::vector<char>>& get_snake_map() const;
	std::vector<std::vector<char>>& get_mut_snake_map();

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

	int get_growth_qual() const;
	int get_poison_qual() const;
	int get_gate_qual() const;
	int get_length_qual() const;

	int get_growth_counter() const;
	int get_poison_counter() const;
	int get_gate_counter() const;

	bool get_gate_ok() const;
	bool get_growth_ok() const;
	bool get_poison_ok() const;
	bool get_length_ok() const;
	int get_max_length() const;

	void push_snake(PlayerBody body);
	void pop_snake();

	WINDOW* get_scoreboard() const;
	WINDOW* get_playboard() const;
	WINDOW* get_titleboard() const;


	// setter
	void set_death(bool value);
	void set_sucess(bool value);
	void set_portal(Portal);
	void set_growth(Item);
	void set_poison(Item);
	void set_snake_map(Position, char);
	void set_empty(Position position, FILL value);
	void set_empty(int x, int y, FILL value);
	void set_last_direction(DIRECTION direction);
	void set_gate_counter(int increment);
	void set_growth_counter(int increment);
	void set_poison_counter(int increment);

	void set_screen(WINDOW*, WINDOW*,WINDOW*);

	void set_gate_ok(bool value);
	void set_growth_ok(bool value);
	void set_poison_ok(bool value);
	void set_length_ok(bool value);
};

#endif
