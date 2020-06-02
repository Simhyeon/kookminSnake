#ifndef PORTALSYS_H
#define PORTALSYS_H

#include "ecsdb.hpp"
#include "commons.hpp"
#include "playerbody.hpp"
#include <vector>

/** \brief 포탈을 처리하는 시스템
 *
 * 포탈의 생성, 소멸과 포탈 효과의 적용을 처리하는 시스템\n
 * 포탈의 검사는 포탈의 검사만을 하기 때문에 벽의 검사보다 먼저 이루어저야 한다.
 */
class PortalSystem{
private:
	/// 포탈의 지속시간
	const long portal_time = 5000;

	/** \brief 포탈의 위치에 따라 플레이어의 방향을 결정하는 함수
	 * @param destination 방향을 정해야 하는 포탈 위치
	 * @param body_number 위치를 이동시켜야 하는 플레이어 노드의 인덱스
	 * @return 방향에 따라 플레이어를 이동시켜야 할 Position과 그 방향값
	 */
	std::pair<Position, DIRECTION> get_jump_result(Position destination,int body_number, ECSDB& db);

	/** \brief 포탈의 다음 위치로 플레이어를 이동시키는 함수
	 * @param head 이동시킬 플레이어 노드
	 * @param destination 이동시킬 포탈의 위치
	 */
	void jump_snake(PlayerBody& body, Position destination);

	/** \brief 포탈을 재생성하는 함수
	 * @param walls 포탈을 생설할 벽의 위치를 참조할 변수
	 * @return 생성한 포탈의 인스턴스
	 */
	Portal regen_portal(const Portal& portal, PosVc& walls);

	/** \brief 포탈 상호작용을 검사하는 함수
	 * @param bodies 포탈 상호작용을 검사할 플레이어 노드 벡터
	 * @param portal 검사할 포탈 컴포넌트
	 * @return 상호작용 여부와 함계 상호작용했다면 그 반대 엔트리 위치 값을 가지는 pair 값
	 */
	std::pair<Position, int> check_portal_interaction(const std::vector<PlayerBody>& bodies, const Portal& portal);
public:	
	/** \brief 포탈 시스템을 작동시키는 함수
	 *
	 * @param db ECS 데이터베이스
	 */
	void process(ECSDB&);
};

#endif
