/*
#include "gamemanager.hpp"
#include <iostream>
void Mananger::start_game(){
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
	fpp.process(*level_it, ecsdb);

	int count;
	char flag;
	std::cin >> flag;
	std::cin >> count;
	ecsdb.update_snake_map();
}

void Manager::main_loop(){
    while (true){
		if (flag == 'c'){
			system("clear");
		}
		rend.process(ecsdb);
		im.process(ecsdb);
		pbs.process(ecsdb);
		its.process(ecsdb);
		pos.process(ecsdb);
		cos.process(ecsdb);
		sss.process(ecsdb);
		ecsdb.update_snake_map();

		if (ecsdb.get_death()){
			std::cout << "Player died\n";
			return 1;
		}
		if (ecsdb.get_success()){
			std::cout << "Player success!\n";
			if (++level_it != levels.end()){
				fpp.process(*level_it, ecsdb);
				ecsdb.update_snake_map();
			} else {
				return 1;
			}
		}
	}

}

void Manager::end_game(){
    rend.~Renderer();
}
*/