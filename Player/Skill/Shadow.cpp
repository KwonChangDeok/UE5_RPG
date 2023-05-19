// Fill out your copyright notice in the Description page of Project Settings.


#include "Shadow.h"

// Sets default values
AShadow::AShadow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMesh = CreateDefaultSubobject<UPoseableMeshComponent>(_T("Mesh"));

	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Mtrl(_T("Material'/Game/Collections/MTGhost.MTGhost'"));

	if (Mtrl.Succeeded())
	{
		mShadowMaterial = Mtrl.Object;
	}
}

// Called when the game starts or when spawned
void AShadow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
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

