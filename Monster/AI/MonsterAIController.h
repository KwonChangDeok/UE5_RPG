// AIController 클래스를 상속받아 몬스터 종류에 따른 비헤이비어트리와 블랙보드데이터를 로드하는 기능을 수행합니다.

// 몬스터 AI를 구현할 때, 몬스터 한마리로 테스트 시 정상적으로 동작하나, 다수의 몬스터를 배치하면 문제를 겪었습니다.
// 이는 모든 몬스터가 같은 테스크노드를 공유하기 때문에(주소를 출력한 결과 동일했습니다.) 발생한 문제였고
// 이를 통해 멤버변수를 함수로 사용해선 안된다는 것과 객체별로 관리해야 할 변수는 블랙보드를 이용해야 한다는 것을 느꼈습니다.
// 또한 정확한 이해 없이 무턱대로 구현만 하려다 겪은 문제라고 생각해, 천천히 침착하게 가는 길이 더욱 빠를수 있다는 것을 느꼈습니다.

#pragma once

#include "../../GameInfo.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

UCLASS()
class ASSASSIN_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIController();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBehaviorTree* mBehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBlackboardData* mBlackboardData;

protected:
	virtual void OnPossess(APawn* aPawn) override;

public:
	void SetBehaviorTree(const FString& Path);
	void SetBlackboard(const FString& Path);
};
