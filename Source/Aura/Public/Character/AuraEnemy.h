// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
	virtual void HighLightActor() override;
	virtual void UnhighLightActor() override;
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	UPROPERTY(VisibleAnywhere,ReplicatedUsing = OnRep_EnemyLevel)
    int32 EnemyLevel = 1;

public:
	AAuraEnemy();
	
	virtual void InitAbilityInfo() override;
	
	virtual int32 GetPlayerLevel() const override;
	
	UFUNCTION()
	void OnRep_EnemyLevel(int32 OldLevel);
};
