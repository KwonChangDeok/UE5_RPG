/*
BoxTriggerBase Ŭ������ ��ӹ޾� ��ġ�� HP�� 0�϶�, 30�� ���� �÷��̾ ü�� 1�� ���·� ������ �̺�Ʈ�� �߻���Ű�� 
�ƿ�Ʈ�� ������ ����ϸ� ��ġ�� �Ҹ�ǵ��� �����մϴ�.
*/

#pragma once

#include "BoxTriggerBase.h"
#include "LichGimmick.generated.h"

UCLASS()
class ASSASSIN_API ALichGimmick : public ABoxTriggerBase
{
	GENERATED_BODY()
public:
	ALichGimmick();

public:
	virtual void TriggerBegin(const FHitResult& SweepResult);
};
