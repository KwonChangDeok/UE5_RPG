// Actor 클래스를 상속받아 특정 스킬 사용시, 검은색 그림자 잔상을 표현해주기 위한 클래스입니다.

#pragma once

#include "../../GameInfo.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Shadow.generated.h"

UCLASS()
class ASSASSIN_API AShadow : public AActor
{
	GENERATED_BODY()
	
public:	
	AShadow();

protected:
	// UPoseableMeshComponent를 이용해 캐릭터의 동작캡쳐
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UPoseableMeshComponent* mMesh;

	// 프레넬 노드를 이용해 구현한 머테리얼입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UMaterialInterface* mShadowMaterial;

	// 메쉬를 구성하는 머테리얼 목록을 저장할 배열
	TArray<UMaterialInstanceDynamic*> mMtrlArray;

protected:
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetMesh(USkeletalMesh* Mesh);
	void CopyAnimation(USkeletalMeshComponent* Com);
};
