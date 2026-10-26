// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"
class UAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
//应用Effect枚举
UENUM(BlueprintType)
enum class EAuraApplyEffectOnOverlap: uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	NotOnApply
};
//移除Effect枚举
UENUM(BlueprintType)
enum class EAuraRemoveEffectOnOverlap : uint8
{
	RemoveOnEndOverlap,
	NotOnRemove
};

class UGameplayEffect;

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	TSubclassOf<UGameplayEffect> InstantEffectClassOf;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	EAuraApplyEffectOnOverlap InstantApplyEffectOnOverlap;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	TSubclassOf<UGameplayEffect> DurationEffectClassOf;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	EAuraApplyEffectOnOverlap DurationApplyEffectOnOverlap;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	TSubclassOf<UGameplayEffect> InfiniteEffectClassOf;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	EAuraApplyEffectOnOverlap InfiniteApplyEffectOnOverlap;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Effect")
	EAuraRemoveEffectOnOverlap InfiniteRemoveEffectOnOverlap;

protected:
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* Actor);
	
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* Actor);
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffect(AActor* TargetActor,TSubclassOf<UGameplayEffect> EffectClass);
	
	virtual void BeginPlay() override;
	
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveGameplayEffectMap;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="ActorLevel")
	float ActorLevel = 1.f;
};
