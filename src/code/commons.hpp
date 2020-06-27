/**
 * @file commons.hpp
 *
 * @author 육심현(20150803)
 *
 */

#ifndef COMMONS_H
#define COMMONS_H

#include <algorithm>
#include <exception>
#include <utility>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <array>

/** \file 여러 곳에서 쓰이는 클래스, 함수들을 모아놓은 헤더 파일
 *
 */

/** \brief 방향값을 나타내는 열거형 
 *
 */
enum class DIRECTION{
	UP = 2,
	RIGHT = 1,
	DOWN = -2,
	LEFT = -1
};

/** \brief Empty Map에서 Empty 여부를 표시하는 열거형
 *
 */
enum class FILL{
	FILL = 1,
	EMPTY = 0,
	NEVER = 2,
};

/** \brief Filemanager에서 ppm 파일을 읽어오는 단위 클래스
 * 
 * @author 육심현(20150803)
 * 
 */
class RGB{
	unsigned char r,g,b;
public:
	/// @author 육심현(20150803)
	RGB(unsigned char r,unsigned char g,unsigned char b);
	/// @author 육심현(20150803)
	operator char();
/// @author 육심현(20150803)
friend std::ostream& operator<<(std::ostream&, RGB&);
/// @author 육심현(20150803)
friend bool operator==(RGB& lhs, RGB& rhs);
};


/** \brief 좌표를 나타내는 클래스
 * 
 * @author 육심현(20150803)
 * 
 */
class Position{
	private:
		int x_pos;
		int y_pos;
	public:
		/// @author 육심현(20150803)
		Position(int x = -1, int y = -1);
		/// @author 육심현(20150803)
		Position(const Position&);
		/// @author 육심현(20150803)
		std::pair<int, int> get_position();

		// Temporary 
		/// @author 육심현(20150803)
		Position& operator=(const Position& lhs);
		/// @author 육심현(20150803)
		bool operator==(const Position& pos) const;
		/// @author 육심현(20150803)
		Position& operator+=(const Position& pos);
		/// @author 육심현(20150803)
		int get_x() const;
		/// @author 육심현(20150803)
		int get_y() const;

		/** \brief 주어진 좌표값만큼 증가시키는 함수
		 *
		 * @author 육심현(20150803)
		 * 
		 * @param x x값
		 * @param x y값
		 */
		void increment(int x, int y);
		/** \brief 주어진 좌표와의 맨해탄 거리를 계산하는 함수
		 *
		 * @author 육심현(20150803)
		 * 
		 * @param position 거리를 계산할 좌표
		 */
		int get_manhattan(const Position& position) const;
	/// @author 육심현(20150803)
	friend std::ostream& operator<<(std::ostream&, const Position&);
};

/** \brief 유틸리티 클래스
 *
 * @author 육심현(20150803)
 * 	
 */
class Util{
public:

	/** \brief rotate_dir에서 사용하는 방향 배열
	 *
	 */
	static std::array<int, 4> dir_array;

	/** \brief 임의의 정수를 가져오는 함수
	 *
	 * @author 육심현(20150803)
	 * 
	 * 	현재 새로운 시드를 할당하지 않고 있기 때문에 같은 값이 나온다.
	 *	@param min 최소 정수값	
	 *	@param min 최대 정수값	
	 *	@return 임의로 생성된 정수값
	 */
	static int get_rand(int min, int max);

	/** \brief 현재 시간을 초단위로 가져오는 함수
	 *
	 * @author 육심현(20150803)
	 * 
	 * 유닉스 기반의 epoch 시간이다.\n
	 * 실제 시간을 나타내지는 않으며 지난 시간을 계산하는 데 사용된다.
	 * @return epoch 시간값을 초로 나타낸것
	 */
	static long get_time();

	/** \brief DIRECTION 열거형을 정수로 바꿔주는 유틸리티 함수
	 *
	 * @author 육심현(20150803)
	 * 
	 * @param dir 바꾸고자 하는 방향 정보
	 * @return 변환된 정수값
	 */
	static int get_dir_int(DIRECTION dir);

	/** \brief 주어진 DIRECTION 값의 반대 값을 반환하는 함수
	 *
	 * @author 육심현(20150803)
	 * 
	 * @param direction 바꾸고자 하는 방향 정보
	 * @return 변환된 방향값
	 */
	static DIRECTION get_reverse_dir(DIRECTION direction);

	/** \brief 주어진 좌표에서 주어진 방향으로 진행한 좌표값를 반환하는 함수
	 *
	 * @author 육심현(20150803)
	 * 
	 * @param position 주어진 좌표
	 * @param direction 진행하고자 하는 방향
	 * @return 계산한 좌표값
	 */
	static Position get_modified_pos(Position position, DIRECTION direction);

	/** \brief 주어진 방향에서 좌우로 회전한 후의 방향값을 반환하는 함수
	 *
	 * @author 육심현(20150803)
	 * 
	 * e.g)\n
	 * DIRECTION::DOWN에서 오른쪽으로 회전시, DIRECTION::LEFT를 반환한다.\n
	 * DIRECTION::RIGHT에서 왼쪽으로 회전시, DIRECTION::UP를 반환한다.
	 * @param position 주어진 좌표
	 * @param direction 회전하는 방향
	 * @return 계산한 방향값
	 */
	static DIRECTION rotate_dir(DIRECTION origin, DIRECTION rotation = DIRECTION::LEFT);
};


// 2 -> 0, 1 : value/2(0) -> y, value %2(1) | -> x; -=value/2 , -=value%2 * 3 
// 1 -> 1, 0 value/2 -> y, value %2 		|-> x; -=value/2 , -=value%2 * 3
// -2 -> 0 -1
// -1 -> -1 0
enum class KEYINPUT{
	RIGHT = -1,
	LEFT = 1,
};

#endif
