// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

	AAuraCharacter();
protected:
	virtual void PossessedBy(AController* PlayerController) override;
	
	virtual void OnRep_PlayerState() override;
	
	virtual int32 GetPlayerLevel() const override;
public:
	UFUNCTION()
	//初始化角色的一些组件或者信息
	virtual void InitAbilityInfo() override;
	
	/*
	 *在角色出生时初始化角色属性（Primary，Secondary，Vital）
	 */
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass,float Level)  const;
	
};
