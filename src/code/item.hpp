#ifndef ITEM_H
#define ITEM_H

#include "commons.hpp"

/** \brief 아이템 효과를 보여주는 아이템 타입
 *
 * 증가하는 경우에는 INC(1),\n 감소하는 경우에는 DEC(-1)\n 아무것도 없다면 NONE(0)이다.
 */
enum class ITEMTYPE{
	NONE	= 0,
	INC		= 1,
	DEC 	=-1,
};

class Item{
private:
	long timestamp;
	Position pos;
public:
	Item();
	Item(Position);
	long get_time();
	Position get_pos();
	bool operator==(const Item& rhs) const;
friend class ItemSystem;
};

// Aliases
using ItmVc=std::vector<Item>;

#endif
