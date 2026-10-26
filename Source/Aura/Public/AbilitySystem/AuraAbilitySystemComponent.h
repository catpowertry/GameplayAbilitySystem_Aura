// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FActiveEffectAssetTag,FGameplayTagContainer);
/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
protected:
	/*
	 * 默认只初始化一次
	 */
	bool bIsInitAbilityActorInfoSet = false;
public:
	void InitAbilityActorInfoSet();
	
	void EffectDeclare(UAbilitySystemComponent* SelfASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle);

	FActiveEffectAssetTag BroadcastAssetTagToWidgetController;
};
