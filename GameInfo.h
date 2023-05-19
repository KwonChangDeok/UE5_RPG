/*
여러 클래스에서 사용할 것으로 예상되는 헤더파일을 include하고 
데이터테이블을 사용하기 위한 구조체들을 정의해 놓은 클래스입니다.
*/
#pragma once

#include <Blueprint\UserWidget.h>

#include "Engine.h"
#include "EngineGlobals.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TimerManager.h"
#include "Components/SplineComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"

// 추후 최적화에서 아래 정의한 구조체들은 배열에 저장해 이용할 시, 메모리를 적게 사용하기 위해선 포인터를 활용하도록 하고,
// 속도 향상을 위해 그 자체를 저장한다면 디폴트패딩 정보를 고려해, 더미데이터를 넣더라도 캐시라인의 배수 Byte크기로 맞춰주는 것이
// 바람직하다고 생각합니다.


// FPlayerInfo와 FPlayerTableInfo를 코드 내에서 사용할 구조체와 데이터테이블용 구조체로 나누어 정의하였으나
// 이는 좋지 못한 방법이었다고 생각합니다. 하나로 통일하는 것이 코드의 길이를 줄이고, 불필요한 메모리 추가 사용을 막을 수 있는 방법이라고
// 생각하기 때문입니다.

USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 LevelMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 SkillPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CooldownReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CriticalRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 SpecialPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Gold;
};

USTRUCT(BlueprintType)
struct FPlayerTableInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 MPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 LevelMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 SkillPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CooldownReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CriticalRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CriticalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 SpecialPoint;
};

// 플레이어와 같은 이유로 FMonsterTableInfo만 남기고 FMonsterInfo는 제거하는것이 좋다고 생각합니다.
// 또한 몬스터와 플레이어 간 공유하는 특성을 구조체로 정의한 후 상속받으면 코드의 길이는 줄일 수 있으나
// 이는 코드의 직관성을 떨어뜨릴 수 있으므로 협업 시 팀원들과의 의견 조율 후 결정해야합니다.
USTRUCT(BlueprintType)
struct FMonsterInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float TraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UAnimInstance>	MonsterAnimClass;
};

USTRUCT(BlueprintType)
struct FMonsterTableInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 HPMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 Gold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float TraceDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	USkeletalMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<UAnimInstance>	MonsterAnimClass;
};


// 아이템의 카테고리별로 구현해야 할 내용이 다를 수 있기 때문에 구현할 수 있다고 생각한 목록으로 나누었습니다.
// 실질적으로는 Blank, CONSUMABLE을 사용했으며, 해당 정보는 만약 장비창을 구현하게 된다면 특정 슬롯의 드롭 이벤트에 대한
// 유효성 처리를 할 때 편리하게 사용할 수 있을 것이라 생각합니다.
UENUM(BlueprintType)
enum class EITEM_TYPE : uint8
{
	Blank,
	CONSUMABLE,
	EQUIP_WEAPON,
	EQUIP_ARMOR,
	EQUIP_ACCESARY
};

// 아이템의 고유ID를 열거형 클래스로 구현했습니다. 이는 데이터테이블에서 아이템을 찾을때 RowName으로 활용됩니다.
UENUM(BlueprintType)
enum class EITEM_ID : uint8
{
	HP_POTION,
	MP_POTION,
	SP_POTION,
	
	DAGGER,
	ARMOR,
	NECKLACE,
	RING,

	Blank
};

// 아이템이 가지고있는 정보들입니다.
// 불필요한 정보도 모두 가지고 있기 때문에 메모리가 낭비됩니다.
// 경우에 따라 다르겠지만, 기획이 변하더라도 편리하게 아이템의 정보를 추가, 삭제할 수 있다는 점이 장점으로 느껴졌으며
// 쉽게 개발할 수 있기에 빠르게 프로토타입을 완성시킨 후 필요 시 최적화를 하는 형태로 사용해도 좋다고 생각합니다.
USTRUCT(Atomic, BlueprintType)
struct FItemDataInfo : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EITEM_ID ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EITEM_TYPE ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString	 ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString	Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	FString	IconPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 LimitLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 NumberOfItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	int32 ItemIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float HPHeal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MPHeal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float SPHeal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float ArmorPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CooldownReduction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CriticalRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CriticalDamage;
};

UCLASS()
class ASSASSIN_API UGameInfo : public UObject
{
	GENERATED_BODY()
};
