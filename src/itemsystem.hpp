#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include "ecsdb.hpp"
#include "commons.hpp"
#include "playerbody.hpp"

enum class ITEMTYPE{
	NONE = 0,
	INC = 1,
	DEC =-1,
};

class ItemSystem{
private:
	void spawn_goodies(PosVc& empty, PosVc& goodies);
	void spawn_poison(PosVc& empty, PosVc& poison);
	void remove_goodies(int entity_index);
	void remove_poison(int entity_index);

	ITEMTYPE check_item_interaction(PlayerBody& head, const PosVc& goodies, const PosVc& poison);
	Position get_following_position(PlayerBody& parent);
public:
	void process(ECSDB&);
};

#endif
