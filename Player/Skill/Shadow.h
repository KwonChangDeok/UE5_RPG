// Actor Ŭ������ ��ӹ޾� Ư�� ��ų ����, ������ �׸��� �ܻ��� ǥ�����ֱ� ���� Ŭ�����Դϴ�.

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
	// UPoseableMeshComponent�� �̿��� ĳ������ ����ĸ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UPoseableMeshComponent* mMesh;

	// ������ ��带 �̿��� ������ ���׸����Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UMaterialInterface* mShadowMaterial;

	// �޽��� �����ϴ� ���׸��� ����� ������ �迭
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
