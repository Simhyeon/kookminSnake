#ifndef RENDERER_H 
#define RENDERER_H

#include <ncurses.h>
#include "commons.hpp"
#include "ecsdb.hpp"
#include "scoreboard.hpp"

class Renderer {
private:
	WINDOW *playboard;
	WINDOW *scoreboard;
public:
	Renderer();
	~Renderer();
	void process(ECSDB&);
	void draw(WINDOW* win,ECSDB& db,int height, int width);
	void printScore(WINDOW* win, int,int,int,int,int);
};
#endif
