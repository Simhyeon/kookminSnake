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
		unsigned int size = ecsdb.get_snake().size();
		std::cout << "Assigning size with " << size << "\n" ;
		ecsdb.get_snake().push_back(PlayerBody( Position(5, i), DIRECTION::DOWN, size));
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
			case 'w' : 
				ecsdb.last_direction = DIRECTION::UP;
				break;

			case 'a' : 
				ecsdb.last_direction = DIRECTION::LEFT;
				break;

			case 's' : 
				ecsdb.last_direction = DIRECTION::DOWN;
				break;

			case 'd' : 
				ecsdb.last_direction = DIRECTION::RIGHT;
				break;
			
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
