/*
BTTaskNode 클래스를 상속받아 바위거인 몬스터의 스킬을 실행하도록 구현한 클래스입니다.
역시 랜덤한 값과 조건에 따른 스킬을 선택해 실행합니다.
예정에 없던 보스를 추가하기 전이라, 이름을 적절하지 못하게 작성했습니다.
네이밍 역시 확장을 고려해야 함을 느꼈습니다.
*/
#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UseSkill.generated.h"

// Giant의 스킬
UCLASS()
class ASSASSIN_API UUseSkill : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UUseSkill();

private:
	ARockGiant* Boss;

	FTimerHandle LaunchTimer;

	FVector LaunchVelocity;

	int32 SkillNum;

	bool key;

	bool IsBerserk;

	class ADecal* Decal;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

public:
	void Launch();
};
