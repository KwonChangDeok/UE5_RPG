// UserWidget 클래스를 상속받아 데미지를 나타낼 텍스트 블록의 내용과 색상을 설정하여, 
// 데미지량과 크리티컬 여부를 파악할 수 있도록 하는 클래스입니다.

#pragma once

#include <Components\TextBlock.h>

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MonsterDamageBase.generated.h"

UCLASS()
class ASSASSIN_API UMonsterDamageBase : public UUserWidget
{
	GENERATED_BODY()
private:
	UTextBlock* mDamage;
	float mPositionX;
	float mPositionY;

public:
	virtual void NativeConstruct() override;

public:
	void SetDamage(FText Damage);
	void SetCriticalDamage(FText Damage);
};
