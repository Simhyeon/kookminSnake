#ifndef RENDERER_H 
#define RENDERER_H

#include <ncurses.h>
#include "commons.hpp"
#include "ecsdb.hpp"
#include "scoreboard.hpp"

class Renderer {
	public:
		void process(ECSDB&);
};

#endif
