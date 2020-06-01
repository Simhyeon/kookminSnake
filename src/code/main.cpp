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
#include "filemanager.hpp"

#include <iostream>

int main(void) {

	// Init
	ECSDB ecsdb;
	Renderer rend;	
	PlayerBodySystem pbs;
	CollisionSystem cos;
	ItemSystem its;
	PortalSystem pos;
	FileManager fpp;
	fpp.process(1, ecsdb);

	int count;
	char flag;
	std::cin >> flag;
	std::cin >> count;
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
				ecsdb.set_last_direction(DIRECTION::UP);
				break;

			case 'a' : 
				ecsdb.set_last_direction(DIRECTION::LEFT);
				break;

			case 's' : 
				ecsdb.set_last_direction(DIRECTION::DOWN);
				break;

			case 'd' : 
				ecsdb.set_last_direction(DIRECTION::RIGHT);
				break;
			
			default:
			   break;
		}
		pbs.process(ecsdb);
		//its.process(ecsdb);
		pos.process(ecsdb);
		//cos.Process(ecsdb);
		ecsdb.update_snake_map();

		if (ecsdb.get_death()){
			std::cout << "Player died\n";
			return 1;
		}
	}
}
