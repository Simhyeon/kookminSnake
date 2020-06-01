#ifndef PHYSICS_H
#define PHYSICS_H

#include "commons.hpp"
#include "ecsdb.hpp"
#include "playerbody.hpp"

/** \brief 충돌을 처리하는 시스템
 *
 * 플레이어 몸체나 벽과의 충돌을 감지하는 시스템
 */
class CollisionSystem{
private:

	/** \brief 충돌을 감지하는 함수
	 *
	 * walls 만 받아오고 iwalls를 받아오지 않는 이유는 iwalls는 player가 접근할 수 없는 위치에만 있기 때문이다. 
	 * @param walls 검사할 벽 정보
	 * @param bodies 검사할 몸체 정보
	 * @return 충돌 여부를 표시하는 boolean값
	 */
	bool detect_collision(const PosVc& walls, const std::vector<PlayerBody>& bodies);
public:
	/** 충돌 시스템의 역할을 작동시키는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
	void process(ECSDB&);
};

#endif
