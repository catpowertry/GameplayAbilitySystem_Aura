// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AttributeSet.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitAbilityInfo();
		
	virtual int32 GetPlayerLevel() const;
	
	virtual void AddCharacterAbilities();
protected:
	virtual void BeginPlay() override;
	
	inline UAttributeSet* GetAttributeSet() const
	{
		return AttributeSet;
	}
	
	UPROPERTY(EditAnywhere,Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	TSubclassOf<UGameplayEffect> DefaultPrimaryEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effects")
	TSubclassOf<UGameplayEffect> DefaultVitalEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effects")
	TSubclassOf<UGameplayEffect> DefaultSecondaryEffect;
	
	UPROPERTY(EditAnywhere,Category = "GameplayAbility")
	TArray<TSubclassOf<UGameplayAbility>> StartGameplayAbilities;
};
