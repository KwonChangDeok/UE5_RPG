#include "Shadow.h"

AShadow::AShadow()
{
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UPoseableMeshComponent>(_T("Mesh"));

	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Mtrl(_T("Material'/Game/Collections/MTGhost.MTGhost'"));

	if (Mtrl.Succeeded())
	{
		mShadowMaterial = Mtrl.Object;
	}
}

void AShadow::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShadow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShadow::SetMesh(USkeletalMesh* Mesh)
{
	if (!IsValid(Mesh))
		return;

	mMesh->SetSkeletalMesh(Mesh);

	if (mShadowMaterial)
	{
		int32	Count = mMesh->GetNumMaterials();

		for (int32 i = 0; i < Count; ++i)
		{
			UMaterialInstanceDynamic* Mtrl =
				mMesh->CreateDynamicMaterialInstance(i, mShadowMaterial);

			mMtrlArray.Add(Mtrl);
		}
	}
}

void AShadow::CopyAnimation(USkeletalMeshComponent* Com)
{
	mMesh->CopyPoseFromSkeletalComponent(Com);
}

