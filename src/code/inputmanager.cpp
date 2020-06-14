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

			case 'P':
			case 'p': 
			char c;
			wattron(db.get_scoreboard(), A_BOLD);
			mvwprintw(db.get_scoreboard(), db.get_height()/2, db.get_width()/2, "PAUSE");
			wattroff(db.get_scoreboard(), A_BOLD);
			nodelay(db.get_scoreboard(), FALSE);
			do{
				c = wgetch(db.get_scoreboard());
			}while(c!='p' && c!='P');
			nodelay(db.get_scoreboard(), TRUE);
			break;
			
			default:
			   break;
		}
}
