#ifndef COMMONS_H
#define COMMONS_H

#include <utility>
#include <vector>
#include <chrono>
#include <cstdlib>

/** \file 여러 곳에서 쓰이는 클래스, 함수들을 모아놓은 헤더 파일
 *
 */

/** \breif 유틸리티 클래스
 *	get_rand, get_time 
 */
class Util{
public:
	/** \breif 임의의 정수를 가져오는 함수
	 * 	아직 확실하게 정리된 것 X, Refactor 필요
	 *	@param min 최소 정수값	
	 *	@param min 최대 정수값	
	 *	@return 임의로 생성된 정수값
	 */
	static int get_rand(int min, int max);

	/** \brief 현재 시간을 초단위로 가져오는 함수
	 *
	 * 유닉스 기반의 epoch 시간이다.\n
	 * 실제 시간을 나타내지는 않으며 지난 시간을 계산하는 데 사용된다.
	 * @return epoch 시간값을 초로 나타낸것
	 */
	static long get_time();
};

/** \brief 방향값을 나타내는 열거형 
 *
 */
enum class DIRECTION{
	UP = 2,
	RIGHT = 1,
	DOWN = -2,
	LEFT = -1
};

// 2 -> 0, 1 : value/2(0) -> y, value %2(1) | -> x; -=value/2 , -=value%2 * 3 
// 1 -> 1, 0 value/2 -> y, value %2 		|-> x; -=value/2 , -=value%2 * 3
// -2 -> 0 -1
// -1 -> -1 0
enum class KEYINPUT{
	RIGHT = -1,
	LEFT = 1,
};

/** \brief 위치를 나타내는 클래스
 *
 * 오퍼레이터 오버로드 검증이 필요하다
 */
class Position{
	private:
		int x_pos;
		int y_pos;
	public:
		Position(int x = 0, int y = 0);

		std::pair<int, int> get_position();

		// Temporary 
		bool operator==(const Position& pos) const;
		const int get_x() const;
		const int get_y() const;
		void increment(int x, int y);};

// Aliases
using PosVc=std::vector<Position>;

#endif
