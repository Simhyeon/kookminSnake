#include "renderer.hpp"
#include <iostream>
Renderer::Renderer(){
	initscr();
	
  	noecho(); //no echo for the key pressed
	cbreak();
	int x,y;
	getmaxyx(stdscr, y, x);
  	curs_set(1);  //no cursor show
}
Renderer::~Renderer(){
	delwin(playboard);
	delwin(scoreboard);
	endwin();
}

void Renderer::process(ECSDB & ecsdb){ //STARTGAME
	//scoreboard
	int length =  ecsdb.get_snake().size();
	int growth_counter =  ecsdb.get_growth_counter(); 
	int growth_qual = ecsdb.get_growth_qual();
	int poison_counter = ecsdb.get_poison_counter();
	int poison_qual = ecsdb.get_poison_qual();
	//int gate_counter = ecsdb.get_gate_counter();
	//int gate_qual = ecsdb.get_gate_qual();

	//playboard
	int width = ecsdb.get_measure().first;
	int height = ecsdb.get_measure().first;
	this->playboard = newwin(height,width,0,0);//height,width,starty,startx	
	nodelay(playboard,true); //if there wasn't any key pressed don't wait for keypress
 	keypad(playboard,true);  //turn on keypad pressed
	this->scoreboard = newwin(height/2,width + 10,0,width + 3);//height,width,starty,startx
	refresh();
	wrefresh(playboard);
		
	while(!ecsdb.get_death()){
			draw(playboard,ecsdb,height,width);
			printScore(scoreboard,length,growth_counter,growth_qual,poison_counter,poison_qual);
			if(ecsdb.get_death()) break;
		}
}

void Renderer::draw(WINDOW* win,ECSDB& db,int height, int width){
	werase(win);
	box(win,0,0);
	int ch;
	auto snake_map = db.get_snake_map();
	for (int i =0; i< width; i++){
		for (int j =0; j< height; j++){
			ch = snake_map[j][i];
			mvwaddch(win, j, i , ch);
		}
	}
	wrefresh(win);
}


void Renderer::printScore(WINDOW* score, int length, int growth_counter, int growth_qual, int poison_counter,int poison_qual){
	werase(score);
	mvwprintw(score, 0, 0,  "length: %d", length);
	mvwprintw(score, 1, 0,  "growth: %d", growth_counter);
	mvwprintw(score, 1, 10, "/ %d", growth_qual);
	mvwprintw(score, 2, 0,  "poison: %d", poison_counter);
	mvwprintw(score, 2, 10, "/ %d", poison_qual);
	wrefresh(score);
}



