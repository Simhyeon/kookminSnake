#include "inputmanager.hpp"
#include <curses.h>

void InputManager::process(ECSDB& db){
	switch (wgetch(db.get_playboard())) {
			case 'w' :
	        	db.set_last_direction(DIRECTION::UP);
			break;

	        
			case 'a' : 
	        	db.set_last_direction(DIRECTION::LEFT);
			break;

	        
			case 's' : 
	            db.set_last_direction(DIRECTION::DOWN);
			break;

	        
			case 'd' : 
	            db.set_last_direction(DIRECTION::RIGHT);
			break;
			
			default:
			   break;
		}
}
