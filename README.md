UE5_RPG 클래스 개요





GameInfo : 여러 클래스에서 사용할 것으로 예상되는 헤더파일을 include하고 데이터테이블을 사용하기 위한 구조체들을 정의해 놓은 클래스입니다.

AssassinGameModeBase : GameModeBase 클래스를 상속받아 메인UI 객체 할당 및 디폴트 폰 클래스, 플레이어 컨트롤러 클래스를 지정해주는 기능을 추가로 수행합니다.

AssassinGameInstance : GameInstance 클래스를 상속받아 생성자에서 다양한 데이터 테이블을 로드하고,해당 테이블에서 특정 데이터를 검색하는 기능을 수행합니다. 각 데이터 테이블은 게임에서 사용되는 플레이어 정보, 몬스터 정보, 아이템 정보 등을 담고 있습니다.

Assassin : Assassin 게임 모듈을 정의하고 기본 게임 모듈 구현을 설정하는 역할을 수행합니다.






- Player 폴더

PlayerCharacter : Character 클래스를 상속받아 입력매핑 및 캐릭터의 이동 및 공격, 스킬사용 등을 구현한 클래스입니다.

AssassinCharacter : PlayerCharacter 클래스를 상속받아 생성자에서 다양한 메시들과 애니메이션 클래스를 로드 및 데이터테이블로 부터 값을 읽어오기 위한 Assassin캐릭터의 RowName 값을 할당해주는 기능 등을 구현한 클래스입니다.

MyPlayerController : PlayerController 클래스를 상속받아 마우스 커서의 보이기 설정과 마우스 커서가 화면의 좌, 우 끝단에 위치할 시 누적값을 PlayerCharacter의 카메라 회전 함수에 전달하는 역할을 합니다.

PlayerAnimInstance : AnimInstanc 클래스를 상속받아 애니메이션 블루프린트와 함께 작동하여 캐릭터의 애니메이션 시스템을 구성하는 클래스입니다. C++클래스에서 설정한 변수값을 이용해 적절한 애니메이션을 애니메이션블루프린트에서 재생하도록 구현하였으며 블루프린트에서 발생시키는 AnimNotify 이벤트를 처리해주는 역할을 수행합니다.

PlayerSkillProjectile : Actor 클래스를 상속받아 구현한 플레이어의 스킬 투사체 클래스입니다. 투사체의 형태와 움직임, 충돌처리, 소멸조건 등을 정의했습니다.






- Player - Skill 폴더

Decal : Actor 클래스를 상속받아 캐릭터의 스킬 범위를 표현해주기 위한 데칼을 구현한 클래스입니다.

DecalBoundary : Actor 클래스를 상속받아 원형 고리형태로 캐릭터의 스킬 시전가능 범위를 표현해주기 위한 클래스입니다.

Shadow : Actor 클래스를 상속받아 특정 스킬 사용시, 검은색 그림자 잔상을 표현해주기 위한 클래스입니다.







- Monster 폴더

MonsterBase : Character 클래스를 상속받아 모든 몬스터가 공유하는 기능들을 구현한 클래스입니다.

Monster : MonsterBase 클래스를 상속받아 일반 몬스터들이 공유하는 기능을 구현한 클래스입니다.

MonsterPatrolPoint : Actor 클래스를 상속받아 월드에 배치해 좌표값을 가질 수 있도록 구현한 클래스입니다.

MonsterSpawnPoint : Actor 클래스를 상속받아 월드에 배치된 지점에서 몬스터를 생성 및 리스폰하고, 특정 지점들을 패트롤 수 있도록 하는 기능을 구현한 클래스입니다. 에디터 상에서 소환할 몬스터와 리스폰간격, 정찰 지점들을 설정할 수 있도록 구현했습니다.

MonsterAnimInstance : AnimInstanc 클래스를 상속받아 애니메이션 블루프린트와 함께 작동하여 몬스터의 애니메이션 시스템을 구성하는 클래스입니다. C++클래스에서 설정한 변수값을 이용해 적절한 애니메이션을 애니메이션블루프린트에서 재생하도록 구현하였으며 블루프린트에서 발생시키는 AnimNotify 이벤트를 처리해주는 역할을 수행합니다.

Ranger : Monster 클래스를 상속받아 구현한 원거리 공격 몬스터입니다. LineTraceMultiByChannel 함수를 이용해 캐릭터와의 충돌을 검사하여 공격 성공, 실패여부를 판단할 수 있도록 구현했습니다. 이외의 정보들은 데이터테이블을 통해 편리하게 편집할 수 있도록 구현했습니다.

Sentinel : Monster 클래스를 상속받아 구현한 정찰 몬스터입니다. SweepMultiByChannel 함수를 이용해 캐릭터와의 충돌검사를 수행, 공격의 성공 여부를 판단할 수 있도록 구현했습니다. 이외의 정보들은 데이터테이블을 통해 관리되며 정찰병은 다른 몬스터보다 넓은 대플레이어 탐지범위를 갖는 특징을 갖도록 했습니다. 

Warrior : Monster 클래스를 상속받아 구현한 전사 몬스터입니다. Sentinel과 같은 로직으로 구현하되 공격력, 방어력, 애니메이션 및 메쉬설정 등의 요소들이 데이터테이블을 통해 다른값으로 관리됩니다.






- Monster - AI 폴더

MonsterAIController : AIController 클래스를 상속받아 몬스터 종류에 따른 비헤이비어트리와 블랙보드데이터를 로드하는 기능을 수행합니다.

TargetDetect : BTService 클래스를 상속받아 구현한 클래스입니다. 일정 범위안에 플레이어가 존재하는지 OverlapMultiByChannel 함수를 이용해 판단한 후 비헤이비어트리의 블랙보드에 탐지한 객체를 전달해주는 기능을 합니다.

TargetTrace : BTTaskNode 클래스를 상속받아 몬스터의 추적기능을 구현한 클래스입니다.몬스터는 인식한 플레이어를 추적하며, 공격 사정거리 안에 들어온다면 공격하고 탐지범위를 벗어난다면 원래의 로직을 수행하도록 하는 기능을 합니다.

CheckDistance : BTDecorator 클래스를 상속받아 몬스터와 플레이어 사이의 거리를 계산해 특정 범위 안에 플레이어의 존재여부를 반환하는 클래스입니다.

Attack : BTTaskNode 클래스를 상속받아 몬스터의 기본공격을 구현한 클래스입니다.

Patrol : BTTaskNode 클래스를 상속받아 몬스터의 정찰 기능을 구현한 클래스입니다.

PatrolWait : BTTaskNode 클래스를 상속받아 몬스터가 정찰 중 실정시간 Idle상태로 대기하는 기능을 구현한 클래스입니다.

BossWait :  BTTaskNode 클래스를 상속받아 보스몬스터의 대기 행동을 구현한 클래스입니다. 보스몬스터 종류별로 일정시간 Idle상태로 대기하도록 동작합니다.

SkillEnable : BTDecorator 클래스를 상속받아 보스몬스터가 현재 스킬을 사용가능한 상태인지 반환하는 기능을 수행합니다.

LichSkill : BTTaskNode 클래스를 상속받아 리치 몬스터의 스킬을 실행하도록 구현한 클래스입니다. 랜덤한 값과 조건들에 따른 스킬을 선택해 실행합니다.

UseSkill : BTTaskNode 클래스를 상속받아 바위거인 몬스터의 스킬을 실행하도록 구현한 클래스입니다. 역시 랜덤한 값과 조건에 따른 스킬을 선택해 실행합니다.






- BossMonster 폴더

BossMonster : MonsterBase 클래를 상속받아 보스몬스터가 공유하는 기능을 구현한 클래스입니다.

RockGiant : BossMonster 클래스를 상속받아 바위거인의 기본 공격 및 스킬, 기믹 등을 구현한 클래스입니다.

BossSkillProjectile : Actor 클래스를 상속받아 바위거인의 바위 투사체를 구현한 클래스입니다. 바위의 낙하지점을 예상하여 데칼로 표현해주는 기능을 포함합니다.

Lich : ABossMonster 클래스를 상속받아 리치의 기본공격 및 스킬, 기믹을 구현한 클래스입니다.

LichSkill3Object : Actor 클래스를 상속받아 리치 스킬의 충돌판정을 구현한 클래스입니다. 생성 후 0.5초 뒤 범위 내 플레이어가 있다면 데미지를 가합니다.

SkillSoundActor : Actor 클래스를 상속받아 리치의 0.5초 뒤 폭발하는 스킬 사운드 재생을 담당하는 클래스입니다.





- Trigger 폴더

BoxTriggerBase : Actor 클래스를 상속받아 플레이어와 오버랩 이벤트 발생 시 이벤트 처리 함수를 바인딩 하는 기능을 수행합니다.

PotalTrigger : BoxTriggerBase를 상속받아 오버랩시 레벨전환을 구현한 클래스입니다. 에디터상에서 파티클시스템과 이동할 레벨명을 설정할 수 있도록 구현했습니다.

RockGiantIntro : BoxTriggerBase를 상속받아 바위거인 맵에서 오버랩시 인트로 시네마틱을 재생하도록 구현했으며, 시네마틱 종료 후 플레이어와 보스를 적절한 위치로 이동시킵니다. 레벨시퀀스와 플레이백세팅을 에디터상에서 설정할 수 있도록 구현했습니다.

LichIntro : BoxTriggerBase를 상속받아 리치 맵에서 오버랩시 인트로 시네마틱을 재생하도록 구현했으며, 시네마틱 종료 후 플레이어와 보스를 적절한 위치로 이동시킵니다.

LichFire : BoxTriggerBase를 상속받아 리치 맵에서 오버랩시 초당 플레이어의 HP가 1씩 감소하도록 구현했으며, 기믹 파훼를 위한 도구로 활용할 수 있습니다.

LichGimmick : BoxTriggerBase를 상속받아 리치의 HP가 0일때, 30초 내에 플레이어가 체력 1인 상태로 오버랩 이벤트를 발생시키면 아웃트로 영상을 재생하며 리치가 소멸되도록 동작합니다.





- UMG 폴더





