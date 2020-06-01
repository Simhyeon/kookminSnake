#ifndef ITEMSYS_H
#define ITEMSYS_H

#include <vector>
#include "ecsdb.hpp"
#include "commons.hpp"
#include "playerbody.hpp"

// 아이템을 먹는 순간엔 증가하지 않는 문제가 있다. 


/** \brief 아이템을 처리하는 시스템
 *
 * 아이템의 생성, 소멸과 아이템 효과의 적용을 처리하는 시스템
 */
class ItemSystem{
private:

	/** \brief 최대 아이템 개수 
	 *
	 */
	const int item_size = 3;

	/** \brief 아이템의 지속시간  
	 *
	 */
	const double item_time = 5;

	/** \brief 플레이어 몸체를 늘려주는 아이템을 생성하는 함수
	 *
	 * @param empty growth을 생성할 위치를 저장한 변수
	 * @param growth 생성된 growth 위치를 저장할 변수
	 */
	void spawn_growth(std::vector<enum FILL>&, ItmVc& growth, int width, int height);

	/** \brief 플레이어 몸체를 줄여주는 아이템을 생성하는 함수
	 *
	 * @param empty poison을 생성할 위치를 저장한 변수
	 * @param poison 생성된 poison 위치를 저장할 변수
	 */
	void spawn_poison(std::vector<enum FILL>&, ItmVc& poison, int width, int height);

	/** \brief 시간이 지난 growth 아이템을 지우는 함수
	 *
	 * @param growth 검사할 아이템 벡터
	 */
	std::pair<bool, Position> remove_growth(ItmVc& growth);

	/** \brief 시간이 지난 poison 아이템을 지우는 함수
	 * 
	 * @param poison 검사할 아이템 벡터
	 */
	std::pair<bool, Position> remove_poison(ItmVc& poison);

	/** \brief 플레이어와 아이템의 상호작용을 검사하는 함수
	 *
	 * @param head PlayerBody 인스턴스 중에서 머리에 해당하는 인스턴스
	 * @param growth growth 아이템이 저장되어 있는 벡터
	 * @param poison poison 아이템이 저장되어 있는 벡터
	 * @return 상호작용한 아이템의 타입. 만약 없다면 NONE을 리턴한다.
	 */
	ITEMTYPE check_item_interaction(const PlayerBody& head, ItmVc& growth, ItmVc& poison);

	/** \brief 아이템을 적용하면서 플레이어 꼬리를 생성할 포지션을 계산하는 함수
	 *
	 * @param parent 아이템을 적용하기 전의 꼬리 인스턴스
	 * @return 새로 계산한 위치 인스턴스
	 */
	Position get_following_position(const PlayerBody& parent);
public:
	/** \brief 아이템 시스템의 역할을 작동시키는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
	void process(ECSDB& db);
};

#endif
