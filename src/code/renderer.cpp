#include "renderer.hpp"
#include <cstring>
#include <curses.h>
#include <iostream>
#include <string>

Renderer::Renderer(){}

void Renderer::init(ECSDB& ecsdb){

	initscr();
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK); ///map_color 색상 지정
	init_pair(2, COLOR_GREEN,COLOR_BLACK); ///boundary_color 색상 지정
	init_pair(3, COLOR_YELLOW,COLOR_BLACK); ///growth_Color 색상 지정
	init_pair(4, COLOR_RED, COLOR_BLACK);  ///poison_color 색상 지정
	init_pair(5, COLOR_WHITE , COLOR_BLACK); ///portal_Color 색상 지정
	init_pair(6, COLOR_MAGENTA , COLOR_BLACK); ///tail_Color 색상 지정
	init_pair(7, COLOR_CYAN , COLOR_BLACK); ///head_Color 색상 지정

	///no echo for the key pressed
	noecho();
	cbreak();
	///커서를 보여주지 않는다
	curs_set(0);  

	int width = ecsdb.get_width();
	int height = ecsdb.get_height();

	///playboard,scoreboard,titleboard 순으로 window의 위치와 크기를 지정해준다
	ecsdb.set_screen(
			newwin(height*2 + 1,width*2 + 2,9,30),
			newwin(height,30,9,width*2+40),
			newwin(7,width*2+40,0,30)
			); //height,width,starty,startx	
	nodelay(ecsdb.get_playboard(),true); ///if there wasn't any key pressed don't wait for keypress
}

	
void Renderer::process(ECSDB & ecsdb){ 
	refresh();
	wrefresh(ecsdb.get_playboard());
	wrefresh(ecsdb.get_scoreboard());
	draw(ecsdb);
	printScore(ecsdb);
	printTitle(ecsdb);
	
}

void Renderer::draw(ECSDB& db){
	
	WINDOW* win = db.get_playboard();
	werase(win);
	///playboard의 테두리를 만들어준다
	box(win,0,0);
	int ch;
	auto snake_map = db.get_snake_map();
	///snake_map에 좌표에 지정된 문자를 채워준다 
	for (int i =0; i< db.get_width(); i++){
		for (int j =0; j< db.get_height(); j++){
			ch = snake_map[j][i];

			///switch문을 사용하여 문자별로 각각의 위치와 색상을 지정하여 출력해준다
			switch(ch){
				case '*':
				mvwaddch(win, i*2+1, j*2+1, ch | COLOR_PAIR(2));
				break;

				case 'P':
				mvwaddch(win, i*2+1, j*2+1, ch | COLOR_PAIR(3));
				break;

				case 'X':
				mvwaddch(win, i*2+1, j*2+1, ch | COLOR_PAIR(4));
				break;

				case 'O':
				mvwaddch(win, i*2+1, j*2+1, ch | COLOR_PAIR(5));
				break;
				
				case '#':
				mvwaddch(win, i*2+1, j*2+1, ch | COLOR_PAIR(6));
				break;

				case '@':
				mvwaddch(win, i*2+1, j*2+1, ch | COLOR_PAIR(7));
				break;

				default:
				mvwaddch(win, i*2+1, j*2+1, ch | COLOR_PAIR(1));
				break;
			}
			
		}
	}
	wrefresh(win);
}	

void Renderer::printTitle(ECSDB& db){
	WINDOW* title = db.get_titleboard();

	///ASCII Generator을 사용하여 제목 디자인을 제작했다
	mvwprintw(title,1,1,"   _________                 __            	   _________    _____   ____  ");
	mvwprintw(title,2,1," /   _____/  ____  _____   |  | __  ____  	  / ___\\__  \\  /     \\_/ __ \\ ");
	mvwprintw(title,3,1," \\_____  \\  /    \\ \\__  \\  |  |/ /_/ __ \\ 	 / /_/  > __ \\|  Y Y  \\  ___/ ");
	mvwprintw(title,4,1," /        \\|   |  \\ / __ \\_|    < \\  ___/ 	 \\___  (____  /__|_|  /\\___  >");
	mvwprintw(title,5,1,"/_______  /|___|  /(____  /|__|_ \\ \\___>	/_____/     \\/      \\/     \\/ ");
	


	///titleboard에 테투리를 만들어준다
	box(title,0,0);
	wrefresh(title);

}
void Renderer::printScore(ECSDB& db){
	WINDOW* score = db.get_scoreboard();
	
	werase(score);
	///뱀의 현재 길이, 뱀의 미션 충족 길이, 충족 여부를 순서대로 출력해준다
	mvwprintw(score, 1, 1,  "length: \t%d/%d (%c)", 
			db.get_snake().size(), 
			db.get_length_qual(),
			db.get_length_ok() ? 'O' : 'X'
			);
	
	///현재까지 얻은 growth item 갯수, 미션 충족 growth item 갯수, 충족 여부를 순서대로 출력해준다
	mvwprintw(score, 2, 1,  "growth: \t%d/%d (%c)", 
			db.get_growth_counter(),
			db.get_growth_qual(),
			db.get_growth_ok() ? 'O' : 'X'
			);

	///현재까지 얻은 poison item 갯수, 미션 충족 poison item 갯수, 충족 여부를 순서대로 출력해준다
	mvwprintw(score, 3, 1,  "poison: \t%d/%d (%c)", 
			db.get_poison_counter(), 
			db.get_poison_qual(),
			db.get_poison_ok() ? 'O' : 'X'
			);
	
	///현재까지 얻은 gate item 갯수, 미션 충족 gate item 갯수, 충족 여부를 순서대로 출력해준다
	mvwprintw(score, 4, 1,  "gate: \t\t%d/%d (%c)", 
			db.get_gate_counter(), 
			db.get_gate_qual(),
			db.get_gate_ok() ? 'O' : 'X'
			);
	///게임 시간을 출력해준다
	mvwprintw(score, 5,1,  "Time past: \t%ld", (Util::get_time() - db.get_time()) / 1000);
	
	///최장길이를 출력해준다
	mvwprintw(score, 7,1,  "Max snake length : %d", db.get_max_length());
	box(score,0,0);
	wrefresh(score);
}


bool Renderer::playAgain(ECSDB& db ){
	///'q'를 누르면 나갈 수 있고, space/enter 키를 누르면 다시 게임을 할 수 있음을 알리는 window을 만든다
	WINDOW* endwin = newwin(2,COLS, LINES-2, 0);
	keypad(endwin, TRUE);
	mvwprintw(endwin, 0, 0, "Press [Spacebar]/[Enter] to play again.");
	mvwprintw(endwin, 1, 0, "Press [q] to quit.");
	int c;
	///q,space,enter키가 입력될때 endwin을 지워준다
	do{
		c = wgetch(endwin);
	}while(c!=10 && c!=' ' && c!='q' && c!='Q');
	werase(endwin);
	wrefresh(endwin);
	delwin(endwin);

	///만약 q가 입력되면 게임을 종료한다
	if (c == 'q' || c == 'Q'){
		return false;
	}
	///만약 enter나 spacebar가 입력되면 set_death를 true로 변형하고 게임판을 다시 업데이트 해준다
	else if (c == ' ' || c == 10){
		db.set_death(true);
		db.update_snake_map();
		return true;
	}
}

bool Renderer::victory(){
	///'q'를 누르면 나갈 수 있고, R키를 누르면 다음 스테이지 게임을 할 수 있음을 알리는 window을 만든다
	WINDOW* endwin = newwin(2,COLS, LINES-2, 0);
	keypad(endwin, TRUE);
	mvwprintw(endwin, 0, 0, "Congratulations you won!");
	mvwprintw(endwin, 1, 0, "Press [q] to quit. or [R] to restart from start.");
	int c;
	///q,space,enter키가 입력될때 endwin을 지워준다
	do{
		c = wgetch(endwin);
	}while(c!='q' && c!='Q' && c!='r' && c!='R');
	if (c == 'R' || c == 'r'){
		/// Restart == true
		werase(endwin);
		wrefresh(endwin);
		delwin(endwin);
		return true;
	}else if (c == 'q' || c == 'Q'){
		/// Restart == false
		werase(endwin);
		wrefresh(endwin);
		delwin(endwin);
		return false;
	}
}