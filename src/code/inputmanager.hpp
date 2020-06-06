#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <ncurses.h>
#include "ecsdb.hpp"

class InputManager{
public:
    void process(ECSDB&);
};
#endif
