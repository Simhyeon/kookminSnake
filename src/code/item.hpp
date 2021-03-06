/**
 * @file item.hpp
 *
 * @author 육심현(20150803)
 *
 */

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

/** \brief Item 정보를 저장하는 클래스
 *
 * @author 육심현(20150803)
 * 
 * Growth이건 Poison이건 구분하지 않고 Item으로 통일하여 저장한다.
 */
class Item{
private:
	/// 아이템이 생성된 시점을 저장하는 timestamp
	long timestamp;
	/// 아이템의 위치를 저장하는 좌표 정보
	Position pos;
public:
	/// @author 육심현(20150803)
	Item();
	/// @author 육심현(20150803)
	Item(Position);
	/// @author 육심현(20150803)
	long get_time();
	/// @author 육심현(20150803)
	Position get_pos();
	/// @author 육심현(20150803)
	bool operator==(const Item& rhs) const;
friend class ItemSystem;
};


#endif
