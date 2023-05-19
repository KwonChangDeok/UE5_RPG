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
