/**
 * @file portal.hpp
 *
 * @author 육심현
 *
 */

#ifndef PORTAL_H
#define PORTAL_H

#include "commons.hpp"

/** \brief 게이트 정보를 저장하는 클래스. 
 *
 *  게이트의 진행 방향은 게이트 클래스에 저장되지 않는다. 
 */
class Portal{
private:
	/// 게이트가 생성된 시점을 저장하는 변수
	long timestamp;
	/// 게이트의 첫 번째 위치 
	Position first_entry;
	/// 게이트의 두 번째 위치 
	Position second_entry;
public:
	Portal();
	Portal(const Position& first,const Position& second, const DIRECTION first_dir, DIRECTION second_dir);
	Portal(const Portal&);
	Portal& operator=(Portal&);
	Position get_first_pos() const;
	Position get_second_pos() const;

friend class PortalSystem;
};

#endif
