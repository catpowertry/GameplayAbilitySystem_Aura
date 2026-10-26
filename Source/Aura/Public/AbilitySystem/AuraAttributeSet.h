#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
class UGameplayEffectType;

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadOnly)
	AActor* AvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	AController* SourceController = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	ACharacter* SourceCharacter = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	AActor* TargetAvatarActor = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	AController* TargetController = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	ACharacter* TargetCharacter = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayEffectContextHandle SourceContextHandle;
};
/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
public:
	UAuraAttributeSet();
	/*
	*Vital Attributes
	*/
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Strength,Category="Vital Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Strength,Category="Vital Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Strength,Category="Vital Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Strength,Category="Vital Attributes")
	FGameplayAttributeData Resilence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilence)
	
	
	/*
	/Base Attributes
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health,Category="Base Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Mana,Category="Base Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana)
	
	/*
	 *SecondaryAttributes
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Armor,Category="Base Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Armor)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ArmorPenetration,Category="Base Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_BlockChance,Category="Base Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitChance,Category="Base Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitChance)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitDamage,Category="Base Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitDamage)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_CriticalHitResistance,Category="Base Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitResistance)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_HealthRegeneration,Category="Base Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HealthRegeneration)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_ManaRegeneration,Category="Base Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ManaRegeneration)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHealth,Category="Base Attributes")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMana,Category="Base Attributes")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana)
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const ;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const ;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const ;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const ;
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const ;
	
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const ;
	
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const ;
	
	UFUNCTION()
	void OnRep_Resilence(const FGameplayAttributeData& OldResilence) const;
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const ;
	
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const ;
	
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const ;
	
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const ;
	
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const ;
	
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;	
	
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const ;
	
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	
	
	
	/*
	 * 在GameplayEffectModCallbackData中获取到一些属性游戏效果的相关信息，并存储在FEffectProperties中
	 */
	void InitEffectProperty(const FGameplayEffectModCallbackData& Data,FEffectProperties& Property);
};
