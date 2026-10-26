// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	AAuraPlayerState();
	
	
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
public:
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	inline UAttributeSet* GetAttributeSet() const
    {
        return AttributeSet;
    }
	
	inline int32 GetPlayerLevel() const{ return Level;}
	
protected:
	
	UPROPERTY(VisibleAnywhere,ReplicatedUsing = OnRep_PlayerLevel)
	int32 Level = 1;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UFUNCTION()
	void OnRep_PlayerLevel(int32 OldLevel);
	
	
};
