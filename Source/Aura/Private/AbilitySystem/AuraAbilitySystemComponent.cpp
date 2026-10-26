// SixCatCompany.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

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
	BroadcastAssetTagToWidgetController.Broadcast(Container);
}
