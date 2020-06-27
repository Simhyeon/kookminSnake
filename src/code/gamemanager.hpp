/**
 * @file gamemanager.hpp
 *
 * @author 류희재(20191587)
 *
 */

#ifndef MANAGER_H
#define MANAGER_H
#include <cstdlib>
#include "commons.hpp"
#include "playerbody.hpp"
#include "playersystem.hpp"
#include "ecsdb.hpp"
#include "renderer.hpp"
#include "collisionsystem.hpp"
#include "itemsystem.hpp"
#include "portalsystem.hpp"
#include "filemanager.hpp"
#include "scoreboard.hpp"
#include "inputmanager.hpp"

#include <iostream>

/** \brief 게임을 실행하는 시스템
 * 
 *  @author 류희재(20191587)
 * 
 */
class Manager{
	public:
		/** \brief Manager class 생성자
		 *
		 * @author 류희재(20191587)
		 *
		 */
		Manager() {}
		/** \brief 게임을 실행하는 함수
		 *
		 * @author 류희재(20191587)
		 *
		 */
		void start_game();
};

#endif
