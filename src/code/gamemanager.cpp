/**
 * @file gamemanager.cpp
 *
 * @author 류희재(20191587)
 *
 */

#include "gamemanager.hpp"
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

/// @author 류희재(20191587)
void Manager::start_game(){
	int level_count = 1;
	int max_level = 4;
	// Init
	ECSDB ecsdb;
	Renderer rend;
	PlayerBodySystem pbs;
	CollisionSystem cos;
	ItemSystem its;
	PortalSystem pos;
	FileManager fpp;
	ScoreSystem sss;
	InputManager im;

	/// Init
	fpp.process(level_count, ecsdb);
	rend.init(ecsdb);
	ecsdb.update_snake_map();
	rend.process(ecsdb);
	srand(time(NULL));

	/// Main Loop
		long time_delay = Util::get_time();
		while (!ecsdb.get_death()){

			im.process(ecsdb);

			// 바로 이전의 호출 시점보다 0.5초 이후에 다시 호출함. 
			// 숫자 단위는 밀리세컨드 500밀리초 = 0.5초
			if (Util::get_time() - time_delay >= 500){
				time_delay = Util::get_time();

				pbs.process(ecsdb);
				its.process(ecsdb);
				pos.process(ecsdb);
				cos.process(ecsdb);
				sss.process(ecsdb);
				ecsdb.update_snake_map();

				
				if (ecsdb.get_death()){
					if(rend.playAgain(ecsdb)){
						ecsdb.set_death(false);
						fpp.process(level_count, ecsdb);
						rend.init(ecsdb);
						ecsdb.update_snake_map();
						rend.process(ecsdb);
						long time_delay = Util::get_time();
						 
					}else{
						break;
					}
				}
				
				rend.process(ecsdb);

				if (ecsdb.get_success()){
					if (level_count != max_level){
						level_count++;
						fpp.process(level_count, ecsdb);
						ecsdb.update_snake_map();
					} else {
						if (rend.victory()){
							level_count = 1;
							fpp.process(level_count, ecsdb);
							ecsdb.update_snake_map();
						} else {
							return;
						}
					}
				}

			}
		}
	
}
	