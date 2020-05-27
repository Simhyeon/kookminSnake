#include <cstdlib>
#include <ncurses.h>
#include "commons.hpp"
#include "playerbody.hpp"
#include "playersystem.hpp"
#include "ecsdb.hpp"
#include "renderer.hpp"
#include "collisionsystem.hpp"
#include "itemsystem.hpp"
#include "portalsystem.hpp"

#include <iostream>

int main(void) {

	// Init
	ECSDB ecsdb;
	Renderer rend;	
	PlayerBodySystem pbs;
	CollisionSystem cos;
	ItemSystem its;
	PortalSystem pos;

	int count;
	char flag;
	std::cin >> flag;
	std::cin >> count;
	for (int i = count; i > 0; i--){
		ecsdb.get_snake().push_back(PlayerBody(DIRECTION::DOWN, Position(5, i)));
	}
	ecsdb.update_snake_map();

	// Main Loop
	char input;
	while (true){
		if (flag == 'c'){
			system("clear");
		}
		rend.process(ecsdb);

		std::cin >> input;	
		switch (input) {
			case 'w' : {
				ecsdb.get_snake()[0].set_direction(DIRECTION::UP);
				break;
			}

			case 'a' : {
				ecsdb.get_snake()[0].set_direction(DIRECTION::LEFT);
				break;
			}

			case 's' : {
				ecsdb.get_snake()[0].set_direction(DIRECTION::DOWN);
				break;
			}

			case 'd' : {
				ecsdb.get_snake()[0].set_direction(DIRECTION::RIGHT);
				break;
			}
			default:
			   break;
		}

		pbs.process(ecsdb);
		its.process(ecsdb);
		pos.process(ecsdb);
		cos.Process(ecsdb);
		ecsdb.update_snake_map();

		if (ecsdb.get_death()){
			std::cout << "Player died\n";
			return 1;
		}
	}

	//initscr();
	//noecho();
	//cbreak();

	//while (false) {
		//// if player input is valid start game
	//}
	//// Create two windows each for player screen and score board

	//endwin();
}
