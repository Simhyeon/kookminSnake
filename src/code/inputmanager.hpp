#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#include <ncurses.h>


class InputManager{
private:
    int input;
public:
    void process(ECSDB&);
};
#endif