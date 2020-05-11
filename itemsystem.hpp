#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include "ecsdb.hpp"
#include "commons.hpp"

class ItemSystem{
private:
	void spawn_goodies();
	void spawn_poison();
	void remove_goodies(int entity_index);
	void remove_poison(int entity_index);

	void check_item_interaction(ECSDB&);
public:
	void process(ECSDB&);
};

#endif
