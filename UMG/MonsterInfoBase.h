/*
UserWidget 클래스를 상속받아 프로그래스바와 텍스트 블록의 값을 설정해 몬스터의 이름과 HP정보 등을 표현할 수 있도록 하는 클래스입니다. 
블루프린트로 파생 시, 일반 몬스터와 보스 몬스터의 UI 배치와 디자인에 차이를 두었습니다.
*/

#pragma once

#include <Components\ProgressBar.h>
#include <Components\TextBlock.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MonsterInfoBase.generated.h"

UCLASS()
class ASSASSIN_API UMonsterInfoBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UProgressBar* mHPBar;
	UTextBlock* mName;
	UTextBlock* mHPText;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DeltaTime);

public:
	void SetHP(float HPRatio);
	void SetName(FText Name);
	void SetText(FText Text);
};
