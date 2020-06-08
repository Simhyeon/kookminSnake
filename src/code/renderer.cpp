#include "renderer.hpp"
#include <cstring>
#include <curses.h>
#include <iostream>
#include <string>

Renderer::Renderer(){}

void Renderer::init(ECSDB& ecsdb){

	initscr();
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK); //map_color
	init_pair(2, COLOR_GREEN,COLOR_BLACK); //boundary_color
	init_pair(3, COLOR_YELLOW,COLOR_BLACK); //growth_Color
	init_pair(4, COLOR_RED, COLOR_BLACK);  //poison_color
	init_pair(5, COLOR_WHITE , COLOR_BLACK); //portal_Color

	noecho(); //no echo for the key pressed
	cbreak();
	curs_set(1);  //no cursor show

	int width = ecsdb.get_width();
	int height = ecsdb.get_height();
	ecsdb.set_screen(
			newwin(height*2,width*2,0,0),
			newwin(height,30,0,width*2)
			); //height,width,starty,startx	
	nodelay(ecsdb.get_playboard(),true); //if there wasn't any key pressed don't wait for keypress
}

void Renderer::process(ECSDB & ecsdb){ //STARTGAME
	refresh();
	wrefresh(ecsdb.get_playboard());
	wrefresh(ecsdb.get_scoreboard());

	draw(ecsdb);
	printScore(ecsdb);
}

void Renderer::draw(ECSDB& db){
	
	WINDOW* win = db.get_playboard();
	werase(win);
	//box(win,0,0);
	int ch;
	auto snake_map = db.get_snake_map();
	for (int i =0; i< db.get_width(); i++){
		for (int j =0; j< db.get_height(); j++){
			ch = snake_map[j][i];
			switch(ch){
				case '*':
				mvwaddch(win, i*2, j*2, ch | COLOR_PAIR(2));
				break;

				case 'P':
				mvwaddch(win, i*2, j*2, ch | COLOR_PAIR(3));
				break;

				case 'X':
				mvwaddch(win, i*2, j*2, ch | COLOR_PAIR(4));
				break;

				case 'O':
				mvwaddch(win, i*2, j*2, ch | COLOR_PAIR(5));
				break;
				

				default:
				mvwaddch(win, i*2, j*2, ch | COLOR_PAIR(1));
				break;
			}
			
		}
	}
	wrefresh(win);
}


void Renderer::printScore(ECSDB& db){
	WINDOW* score = db.get_scoreboard();
	
	werase(score);
	//mvwprintw(score, 0, 0,  "Time: %ld", Util::get_time());
	mvwprintw(score, 1, 1,  "length: %d/%d (%c)", 
			db.get_snake().size(), 
			db.get_length_qual(),
			db.get_length_ok() ? 'O' : 'X'
			);
	mvwprintw(score, 2, 1,  "growth: %d/%d (%c)", 
			db.get_growth_counter(),
			db.get_growth_qual(),
			db.get_growth_ok() ? 'O' : 'X'
			);
	mvwprintw(score, 3, 1,  "poison: %d/%d (%c)", 
			db.get_poison_counter(), 
			db.get_poison_qual(),
			db.get_poison_ok() ? 'O' : 'X'
			);
	mvwprintw(score, 4, 1,  "gate: %d/%d (%c)", 
			db.get_gate_counter(), 
			db.get_gate_qual(),
			db.get_gate_ok() ? 'O' : 'X'
			);
	//mvwprintw(score, 4,0,  "Time : %ld", Util::get_time());
	//mvwprintw(score, 5,0,  "Last input : %d", db.get_last_direction());
	wborder(score, '#','#','#','#','#','#','#','#');
	wrefresh(score);
}



