#ifndef ITEMSYS_H
#define ITEMSYS_H

#include <vector>
#include "ecsdb.hpp"
#include "commons.hpp"
#include "playerbody.hpp"

/** \file itemsystem.hpp
 * \brief 아이템 시스템의 헤더 파일
 *
 * 아이템 시스템과 아이템타입 열거형을 정의한 헤더 파일
 */


/** \brief 아이템을 처리하는 시스템
 *
 * 아이템의 생성, 소멸과 아이템 효과의 적용을 처리하는 시스템
 */
class ItemSystem{
private:
	/** \brief 플레이어 몸체를 늘려주는 아이템을 생성하는 함수
	 *
	 * @param empty goodies을 생성할 위치를 저장한 변수
	 * @param goodies 생성된 goodies 위치를 저장할 변수
	 */
	void spawn_goodies(PosVc& empty, ItmVc& goodies);

	/** \brief 플레이어 몸체를 줄여주는 아이템을 생성하는 함수
	 *
	 * @param empty poison을 생성할 위치를 저장한 변수
	 * @param poison 생성된 poison 위치를 저장할 변수
	 */
	void spawn_poison(PosVc& empty, ItmVc& poison);

	/** \brief 시간이 지난 goodies 아이템을 지우는 함수
	 *
	 * @param entity_index 지울 goodies 아이템의 인덱스
	 */
	void remove_goodies(int entity_index);

	/** \brief 시간이 지난 poison 아이템을 지우는 함수
	 * 
	 * @param entity_index 지울 poison 아이템의 인덱스
	 */
	void remove_poison(int entity_index);

	/** \brief 플레이어와 아이템의 상호작용을 검사하는 함수
	 *
	 * @param head PlayerBody 인스턴스 중에서 머리에 해당하는 인스턴스
	 * @param goodies goodies 아이템이 저장되어 있는 벡터
	 * @param poison poison 아이템이 저장되어 있는 벡터
	 * @return 상호작용한 아이템의 타입. 만약 없다면 NONE을 리턴한다.
	 */
	ITEMTYPE check_item_interaction(PlayerBody& head, const ItmVc& goodies, const ItmVc& poison);

	/** \brief 아이템을 적용하면서 플레이어 꼬리를 생성할 포지션을 계산하는 함수
	 *
	 * @param parent 아이템을 적용하기 전의 꼬리 인스턴스
	 * @return 새로 계산한 위치 인스턴스
	 */
	Position get_following_position(PlayerBody& parent);
public:
	/** \brief 아이템 시스템의 역할을 작동시키는 함수
	 *
	 * @param db ECS 데이터베이스의 참조값
	 */
	void process(ECSDB& db);
};

#endif
