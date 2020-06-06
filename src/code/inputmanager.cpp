#include "inputmanager.hpp"
#include "ncurses.h"

void InputManager::process(ECSDB& db){
    input = getch();
    switch (input) {
			case 'w' :
            if(db.get_last_direction() != DIRECTION::UP){
                db.set_last_direction(DIRECTION::UP);
            }
			break;

            
			case 'a' : 
                if(db.get_last_direction() != DIRECTION::LEFT){
                    db.set_last_direction(DIRECTION::LEFT);
                }
			break;

            
			case 's' : 
				if(db.get_last_direction() != DIRECTION::DOWN){
                db.set_last_direction(DIRECTION::DOWN);
            }
			break;

            
			case 'd' : 
            if(db.get_last_direction() != DIRECTION::RIGHT){
                db.set_last_direction(DIRECTION::RIGHT);
            }
			break;
			
			default:
			   break;
		}
}