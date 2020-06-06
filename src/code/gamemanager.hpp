#ifndef MANAGER_H
#define MANAGER_H
#include <cstdlib>
#include <ncurses.h>
#include "commons.hpp"
#include "playerbody.hpp"
#include "playersystem.hpp"
#include "ecsdb.hpp"
#include "renderer.hpp"
#include "collisionsystem.hpp"
#include "itemsystem.hpp"
#include "portalsystem.hpp"
#include "filemanager.hpp"
#include "scoreboard.hpp"
#include "inputmanager.hpp"

class Manager{
	public:
		void start_game();
		void main_loop();
		void pause();
		void end_game();
};

#endif
