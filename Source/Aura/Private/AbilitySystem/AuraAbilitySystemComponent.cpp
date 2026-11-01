// SixCatCompany.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystem/GameplayAbility/AuraGameplayAbility.h"

void UAuraAbilitySystemComponent::InitAbilityActorInfoSet()
{
	/** 默认未进行初始化，直接执行而不是返回
	 * 执行后再次执行这次函数在第一步判断直接返回不继续执行
	 */
	if (bIsInitAbilityActorInfoSet) return;
	/*
	 *绑定委托在玩家ASC组件接收到GameplayEffectTag时触发
	 * 
	 */
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::EffectDeclare);
	bIsInitAbilityActorInfoSet = true;
}

void UAuraAbilitySystemComponent::AddStartGameplayAbility(const TArray<TSubclassOf<UGameplayAbility>>& StartGameplayAbility)
{
	/*
	 *
	 * 添加游戏能力(在Character中进行添加，GAS中只负责处理有关数据不负责处理)
	 */
	for (const TSubclassOf<UGameplayAbility>& StartGA : StartGameplayAbility)
	{
		FGameplayAbilitySpec StartAbilitySpec = FGameplayAbilitySpec(StartGA,1);
		if (UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(StartAbilitySpec.Ability))
		{
			
			/*
			 *
			 * Optional ability tags that are replicated.  These tags are also captured as source tags by applied gameplay effects. 			
			 */
			StartAbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartGameplayTag);
			GiveAbility(StartAbilitySpec);
		}
		// GiveAbility(StartAbilitySpec);
		GiveAbilityAndActivateOnce(StartAbilitySpec);
	}
}

/*
 *
 * 玩家ASC组件接收到GameplayEffectTag时触发函数
 * 函数功能：将GameplayEffectTag广播
 */
void UAuraAbilitySystemComponent::EffectDeclare(UAbilitySystemComponent* SelfASC, const FGameplayEffectSpec& EffectSpec,
                                                FActiveGameplayEffectHandle EffectHandle)
{
	FGameplayTagContainer Container;
	EffectSpec.GetAllAssetTags(Container);
	FActiveTagDelegate.Broadcast(Container);
}

void UAuraAbilitySystemComponent::AbilityInputTagPressed(FGameplayTag& Tag)
{
	for (FGameplayAbilitySpec & AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if ((!AbilitySpec.IsActive()))
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
	
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(FGameplayTag& Tag)
{
	
	for (FGameplayAbilitySpec & AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag))
		{
			AbilitySpecInputReleased(AbilitySpec);
			if ((!AbilitySpec.IsActive()))
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
	
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag& Tag)
{
	
	for (FGameplayAbilitySpec & AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if ((!AbilitySpec.IsActive()))
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
			
		}
	}
	
}
