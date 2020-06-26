/**
 * @file renderer.hpp
 *
 * @author 류희재
 *
 */

#ifndef RENDERER_H 
#define RENDERER_H

#include <ncurses.h>
#include "commons.hpp"
#include "ecsdb.hpp"
#include "scoreboard.hpp"
#include <iostream>

class Renderer {
private:
	/** \brief playboard를 출력해주는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
	void draw(ECSDB&);

	/** \brief scoreboard를 출력해주는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
	void printScore(ECSDB&);

	/** \brief titleboard를 그려주는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
	void printTitle(ECSDB&);

public:

	/** \brief Renderer 클래스 생성자
	 *
	 * 
	 */
	Renderer();

	/** \brief playboard를 그려주는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
	void init(ECSDB&);

	/** \brief 랜더링 시스템을 처리하는 시스템
	 *
	 * @param db ECS 데이터베이스
	 */
	void process(ECSDB&);

	/** \brief 죽었을때 게임을 다시 시작할 수 있는지 선택하는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
	bool playAgain(ECSDB& db);


	/** \brief 이겼을 때 다음 스테이지로 넘어가는 함수
	 *
	 * 
	 */
	bool victory();

	
};
#endif
