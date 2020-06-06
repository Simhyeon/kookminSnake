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

int main(void) {

	std::vector<int> levels = {1,2,3,4,5};
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
	std::vector<int>::iterator level_it = levels.begin();

	/// Init
	fpp.process(*level_it, ecsdb);
	rend.init(ecsdb);
	ecsdb.update_snake_map();
	rend.process(ecsdb);

	/// Main Loop
	long time_delay = Util::get_time();
	while (true){

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
				return 1;
			}

			if (ecsdb.get_success()){
				// 왜 막아 두었는가 하면 현재 코드는 width, height가 변하지 않는 것을 가정하고 있다.
				// 그런데 현재 ppm 맵들은 크기가 제각각이다.
				return 0;
				//if (++level_it != levels.end()){
					//fpp.process(*level_it, ecsdb);
					//ecsdb.update_snake_map();
				//} else {
					//return 1;
				//}
			}

			rend.process(ecsdb);
		}
	}
}
