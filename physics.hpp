#ifndef PHYSICS_H
#define PHYSICS_H

#include <utility>
#include "commons.hpp"
#include "wall.hpp"
#include "item.hpp"

class Collision{
private:
	ITEMTYPE item_type;
	WALLTYPE wall_type;
	Position new_pos;
public:
	Collision(ITEMTYPE, WALLTYPE, Position);

friend class PlayerBodySystem;
};

// How about including Collision inside of Physics class?
// Physics is kinda hard to cope with pure ecs 
// Because shared data is needed and How should I cope with shared data?
// 아무리 생각해도 시스템이 다른 시스템에 의존하는 것은 절대 좋은 것이 아니다. 
// 최소한 Shared Data를 사용하는 것이 필요한데 아니면 Physics의 권능ㄹ moveable을 리턴하는 것으로 한정하는 것도
// 방법이다. 
// 지금 생각하건대 플레이어 시스템과 컴포넌트가 결합되어 있기 때문에 생기는 문제란걸 깨달았다. 
// 이 간단한 걸 생각을 못하다니 
// 내가 봤던 예제는 너무 간단한 것이라서 ECS Database가 필요가 없었지만 
// 이 경우에는 데이터를 공유해야 하므로, 컴포넌트를 시스템 밖으로 꺼내는 것이 당연하다. 멍청하긴
class Physics{
public:
	Collision DetectCollision(Position, const WallSystem&, const ItemSystem& item_system) const;
};

#endif
