#ifndef RENDERER_H 
#define RENDERER_H

#include <ncurses.h>
#include "commons.hpp"
#include "player.hpp"
#include "scoreboard.hpp"

class Renderer {
	public:
		// 포인터는 비효율 좀 더 좋은 방법을 찾아보자.
		void render_player(const PlayerBodySystem& body_system, WINDOW* window); 
		void render_score(const PlayerBodySystem& body_system, const ScoreBoard& scoreboard, WINDOW* window); 
};

#endif
