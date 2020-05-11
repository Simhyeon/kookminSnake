# 국민대학교 C++ 프로그래밍 기말 프로젝트
![C/C++ CI](https://github.com/Simhyeon/kookminSnake/workflows/C/C++%20CI/badge.svg)

### 참여인 
- 20150803 사법학과 육심현
- 20191587          류희재

### 맡은 역할

육심현
- 플레이어, 벽, 아이템, 물리 

류희재
- 사용자 입력, 점수판, 렌더러, 게임 매니저

### 작업 환경
- POP\_OS 20.04 (Ubuntu 기반)
- ...
- CI : Ubuntu 가상 머신 + ncurses 라이브러리

### 빌드방법

```
// 의존 라이브러리 설치 필요
sudo apt-get install -y libncurses5-dev libncursesw5-dev
// clone 또는 tarball 이용
git clone https://github.com/Simhyeon/kookminSnake
cd kookminSnake
make
```

### 기본 로직

#### 데이터 지향 디자인(ECS)
- Component는 데이터만을 저장
- Entity는 프로젝트 크기 고려하여 생략
- System은 로직을 담당

### Readme 수정 필요
