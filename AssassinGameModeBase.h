/*
GameModeBase 클래스를 상속받아 메인UI 객체 할당 및 디폴트 폰 클래스, 
플레이어 컨트롤러 클래스를 지정해주는 기능을 추가로 수행합니다.
*/

#pragma once

#include "GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "AssassinGameModeBase.generated.h"

// 게임모드는 월드 당 하나만 존재함으로, 여기서 게임의 메인UI를 생성하고 뷰포트에 추가하도록 구현했습니다.
// 만약 추후에 미니게임을 추가해 메인 UI가 변경되어야 할 필요가 있다면 해당 레벨에 다른 게임모드를 사용하여 개발에 차질이 없는 방법일 것이라
// 판단했습니다.

UCLASS()
class ASSASSIN_API AAssassinGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AAssassinGameModeBase();

private:
	TSubclassOf<UUserWidget> mMainUIClass;
	// 전방 선언을 이용해 헤더파일에서의 타 헤더파일 Include를 피함으로써, 순환참조가 발생하지 않도록 했습니다.
	class UMainUIBase* mMainUI;

public:
	virtual void BeginPlay()	override;

public:
	// Getter, Setter함수 등 간단한 함수는 헤더파일에 구현했는데, 이는 추후 협업시, 팀에 맞춰 작성하도록 하겠습니다.
	UMainUIBase* GetMainUI()
	{
		return mMainUI;
	}
};
