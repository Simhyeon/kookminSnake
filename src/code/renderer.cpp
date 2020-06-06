#include "renderer.hpp"
#include <cstring>
#include <curses.h>
#include <iostream>
#include <string>

Renderer::Renderer(){}

void Renderer::init(ECSDB& ecsdb){

	initscr();
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
			mvwaddch(win, i*2, j*2, ch);
		}
	}
	wrefresh(win);
}


void Renderer::printScore(ECSDB& db){
	WINDOW* score = db.get_scoreboard();
	werase(score);
	//mvwprintw(score, 0, 0,  "Time: %ld", Util::get_time());
	mvwprintw(score, 0, 0,  "length: %d/%d (%c)", 
			db.get_snake().size(), 
			db.get_length_qual(),
			db.get_length_ok() ? 'O' : 'X'
			);
	mvwprintw(score, 1, 0,  "growth: %d/%d (%c)", 
			db.get_growth_counter(),
			db.get_growth_qual(),
			db.get_growth_ok() ? 'O' : 'X'
			);
	mvwprintw(score, 2, 0,  "poison: %d/%d (%c)", 
			db.get_poison_counter(), 
			db.get_poison_qual(),
			db.get_poison_ok() ? 'O' : 'X'
			);
	mvwprintw(score, 3, 0,  "gate: %d/%d (%c)", 
			db.get_gate_counter(), 
			db.get_gate_qual(),
			db.get_gate_ok() ? 'O' : 'X'
			);
	mvwprintw(score, 4,0,  "Time : %ld", Util::get_time());
	mvwprintw(score, 5,0,  "Last input : %d", db.get_last_direction());
	wrefresh(score);
}



