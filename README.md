DirectX2D (C++)

RedHood Adventure 2023 04 ~ 2023 05 작업

YouTube Link
(https://youtu.be/UKIUMnVwMYA?si=-beGDI6APLU8HxYu)

프로젝트명: RedHood Adventure (2023.04 – 2023.06)

장르: Adventure RPG
사용 엔진: DirectX(2D)
협업 유무 : X

[담당 구현 기술]

	물리현상을 담당하는 Component RigidBody 구현
: Character 헤더파일에 Default로 RigidBody를 등록하여 Floor 객체들과 Character간의 물리 충돌을 미리 감지하여 충돌 Floor 타입에 따라 행동에 제약 또는 추가적인 행동을 부여해주는 역할을 수행.

	Map Editor 구현
: 사용할 Floor들의 UV를 미리 등록한 PNG 파일을 UV좌표로 잘라내어 해당 Texture파일을 게임 맵 정보에 데이터로 저장하여 관리. Texture를 저장할 시 해당 데이터에 Actor Type(바닥, 몬스터, 오브젝트, 트리거 오브젝트 등)의 정보와 Floor 객체일 시 Collision Type, Visiable 여부 등을 가지고 있는 구조체로 넘겨주기 위해 함께 정보를 저장하도록 설정.

	몬스터 AI 설정
: 부모 Monster 헤더를 중심으로 각 개체들의 탐지 거리, 공격 사거리 등을 고려하여 플레이어를 추격 및 소지 중인 공격 함수들을 사용하여 다양한 공격 모션 및 메커니즘을 구현.

	플레이어 Animaition Script 제작
: Animation PNG를 설정한 UV좌표로 잘라내어 원하는 위치까지 저장시키는 Animation Frame을 제작하여 플레이어에게 저장한 뒤 플레이어의 State마다 특정 이동 코드와 함께 재생시켜 플레이어 Animation Script를 제작.

	벽타기 및 미끄러지기 구현
: Floor의 Collision Type이 Side일 경우 Isleft 또는 Isright를 활성화 시켜 해당 벽면으로 매달려 천천히 떨어지며 점프 시 해당 벽면의 반대편으로 점프하도록 구현.

	업그레이드 상점
: 업그레이드 NPC에게 다가가 E키를 누르면 업그레이드 창이 출력되고, 플레이어의 공격 연격기, 공격력 등을 강화할 수 있도록 UI를 설정.
