// SixCatCompany.


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent")));
}

void AAuraEffectActor::ApplyEffect(AActor* TargetActor,TSubclassOf<UGameplayEffect> EffectClass)
{
	//获取到使用该Effect物品的Actor的ASC组件
	UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!TargetASC) return;
	
	check(EffectClass)
	//创建Effect上下文用于记录Effect应用信息
	FGameplayEffectContextHandle EffectContextHandle=TargetASC->MakeEffectContext();
	//添加影响源
	EffectContextHandle.AddSourceObject(this);
	//创建Effect并给其添加参数用于应用于角色Effect
	const FGameplayEffectSpecHandle EffectSpec=TargetASC->MakeOutgoingSpec(EffectClass,ActorLevel,EffectContextHandle);
	//应用Effect
	const FActiveGameplayEffectHandle EffectHandle=TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
	const bool bIsInfinite=EffectSpec.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteRemoveEffectOnOverlap == EAuraRemoveEffectOnOverlap::RemoveOnEndOverlap)
	{
		ActiveGameplayEffectMap.Add(EffectHandle,TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* Actor)
{
	if (InstantApplyEffectOnOverlap == EAuraApplyEffectOnOverlap::ApplyOnOverlap)
	{
		ApplyEffect(Actor,InstantEffectClassOf);
	}
	if (DurationApplyEffectOnOverlap == EAuraApplyEffectOnOverlap::ApplyOnOverlap)
	{
		ApplyEffect(Actor,DurationEffectClassOf);
	}
	if (InfiniteApplyEffectOnOverlap == EAuraApplyEffectOnOverlap::ApplyOnOverlap)
	{
		ApplyEffect(Actor,InfiniteEffectClassOf);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* Actor)
{
	if (InstantApplyEffectOnOverlap == EAuraApplyEffectOnOverlap::ApplyOnEndOverlap)
	{
		ApplyEffect(Actor,InstantEffectClassOf);
	}
	if (DurationApplyEffectOnOverlap == EAuraApplyEffectOnOverlap::ApplyOnEndOverlap)
	{
		ApplyEffect(Actor,DurationEffectClassOf);
	}
	if (InfiniteApplyEffectOnOverlap == EAuraApplyEffectOnOverlap::ApplyOnEndOverlap)
	{
		ApplyEffect(Actor,InfiniteEffectClassOf);
	}
	if (InfiniteRemoveEffectOnOverlap == EAuraRemoveEffectOnOverlap::RemoveOnEndOverlap)
	{
		const UAbilitySystemComponent* TargetASC=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
		
		TArray<FActiveGameplayEffectHandle> Handles;
		
		for (const auto& Pair : ActiveGameplayEffectMap)
		{
			if (IsValid(Pair.Value))
			{
				if (Pair.Value == TargetASC)
				{
					Pair.Value->RemoveActiveGameplayEffect(Pair.Key,1);
					Handles.Add(Pair.Key);
				}
			}
		}
		for (const auto& Handle : Handles)
		{
			ActiveGameplayEffectMap.Remove(Handle);
		}
	}
}


