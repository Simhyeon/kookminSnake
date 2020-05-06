#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include "commons.hpp"

class ItemSystem{
private:
	std::vector<Position> items;
public:
	bool at_item(int x, int y);
	void set_item(int x, int y);
	bool consume_item(int x, int y);
};

#endif
