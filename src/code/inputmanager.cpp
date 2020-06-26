/**
 * @file inputmanager.cpp
 *
 * @author 류희재
 *
 */

#include "inputmanager.hpp"
#include <curses.h>

//switch문을 활용하여 playboard에 표준입력된 문자에 따라 뱀의 방향을 결정해준다
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

			//playboard에 표준입력된 문자가 'P'라면 게임을 일시정지 해준다.
			//scoreboard에 게임이 일시정지 되었다는 문구를 출력해준다
			//'P'가 다시 입력될때까지 게임을 계속 일지 중지시키고 'P'를 입력시키면 게임을 재개한다
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
