#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <ncurses.h>
#include "ecsdb.hpp"


/** \brief 표준 입력을 처리하는 시스템
	 *
	 *	뱀의 이동 및 게임의 흐름을 제어하는 시스템
	 */
class InputManager{
public:
/** \brief 표준 입력 시스템의 역할을 작동시키는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
    void process(ECSDB&);
};
#endif
