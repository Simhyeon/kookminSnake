#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include "commons.hpp"

enum class ITEMTYPE{
	NONE,
	GOODIES,
	POISON,
};

class ItemSystem{
private:
	std::vector<Position> goodies;
	std::vector<Position> poison;

	void consume_item(int x, int y);
public:
	ITEMTYPE peak_item(int x, int y);
	void set_item(int x, int y, ITEMTYPE);
};

#endif
