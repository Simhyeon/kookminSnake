[수행 단계]
1단계 - (구현 완료)
Map의 구현, 2차 char 배열을 통해서 렌더러 시스템이 직사각형 모양의 맵을 그릴 수 있도록 한다. 

2단계 - (구현 완료) 
Snake 표현 및 조작, 사용자가 입력한 방향값에 따라 뱀을 움직이고 각각의 뱀의 움직임이 독립적으로 작용하게 한다. 
벽이나 몸에 부딪힐 경우에는 그 상호작용에 따라 뱀을 죽게 한다. 

3단계 - (구현 완료) 
Item 요소의 구현, 뱀이 아이템과 부딪힐 경우 뱀의 크기가 늘어나거나 줄어들게 하고 아이템을 생성 및 소멸시킬 수 있게 한다. 

4단계 - (구현 완료) 
Gate 요소의 구현, 뱀이 Gate와 부딪힐 경우 뱀의 위치가 변할 수 있게 하고 주어진 규칙에 따라 뱀의 이동할 위치를 연산하여 정하도록 한다. 

5단계 - (구현 완료) 
점수 요소의 구현, DB에 저장된 정보를 토대로 하여 점수를 계산하고 그 점수를 렌더러가 화면에 표시한다. 

6단계 - (구현 완료) 
레벨을 파일로 저장, PPM 파일 경로와 레벨의 조건을 yaml 포맷으로 저장하여 프로그램이 읽을 수 있도록 한다. 

7단계 - (구현 완료) 
게임 매니저 구현, 게임 매니저를 통해서 각각의 시스템을 작동하고 게임의 흐름을 조절할 수 있도록 한다.

[기여도]
aliases.hpp         : 육심현
collisionsystem.cpp : 육심현
collisionsystem.hpp : 육심현
commons.cpp         : 육심현
commons.hpp         : 육심현
ecsdb.cpp           : 육심현, 류희재
ecsdb.hpp           : 육심현, 류희재
filemanager.cpp     : 육심현
filemanager.hpp     : 육심현
gamemanager.cpp     : 류희재
gamemanager.hpp     : 류희재
inputmanager.cpp    : 류희재
inputmanager.hpp    : 류희재
item.cpp            : 육심현
item.hpp            : 육심현
itemsystem.cpp      : 육심현
itemsystem.hpp      : 육심현
main.cpp            : 류희재
playerbody.cpp      : 육심현
playerbody.hpp      : 육심현
playersystem.cpp    : 육심현
playersystem.hpp    : 육심현
portal.cpp          : 육심현
portal.hpp          : 육심현
portalsystem.cpp    : 육심현
portalsystem.hpp    : 육심현
renderer.cpp        : 류희재
renderer.hpp        : 류희재
scoreboard.cpp      : 류희재
scoreboard.hpp      : 류희재
string.cpp          : 육심현
string.hpp          : 육심현