#ifndef RENDERER_H 
#define RENDERER_H

#include <ncurses.h>
#include "commons.hpp"
#include "ecsdb.hpp"
#include "scoreboard.hpp"
#include <iostream>

class Renderer {
private:
	void draw(ECSDB&);
	void printScore(ECSDB&);
public:
	Renderer();
	void init(ECSDB&);
	void process(ECSDB&);
	bool playAgain(ECSDB& db);
	void printTitle(ECSDB&);
};
#endif
