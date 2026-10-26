// SixCatCompany.


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AttributeSet.h"
#include "AuraGameplayTag.h"
#include "Net/UnrealNetwork.h"
UAuraAttributeSet::UAuraAttributeSet()
{
 const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	
	 const FAuraGameplayTags Tags = GameplayTags.Get();
	
	/*
	 *
	 * 将所有使用的GameplayAttributeMap添加到Map中
	 * PrimaryAttributeTag
	 */
	AttributeMap.Add(Tags.Attribute_Primary_Strength,GetStrengthAttribute);
	
	AttributeMap.Add(Tags.Attribute_Primary_Intelligence,GetIntelligenceAttribute);
	
	AttributeMap.Add(Tags.Attribute_Primary_Vigor,GetVigorAttribute);
	
	AttributeMap.Add(Tags.Attribute_Primary_Resilence,GetResilenceAttribute);
	
	/*
	 *SecondaryAttributeTag
	 * 
	 */
	
	AttributeMap.Add(Tags.Attribute_Secondary_Armor,GetArmorAttribute);
	
	AttributeMap.Add(Tags.Attribute_Secondary_BlockChance,GetBlockChanceAttribute);

	AttributeMap.Add(Tags.Attribute_Secondary_CriticalHitChance,GetCriticalHitChanceAttribute);
	
	AttributeMap.Add(Tags.Attribute_Secondary_CriticalHitDamage,GetCriticalHitDamageAttribute);

	AttributeMap.Add(Tags.Attribute_Secondary_CriticalHitResistance,GetCriticalHitResistanceAttribute);
	
	AttributeMap.Add(Tags.Attribute_Secondary_HealthRegeneration,GetHealthRegenerationAttribute);
	
    AttributeMap.Add(Tags.Attribute_Secondary_ManaRegeneration,GetManaRegenerationAttribute);
	
    AttributeMap.Add(Tags.Attribute_Secondary_MaxHealth,GetMaxHealthAttribute);
	
    AttributeMap.Add(Tags.Attribute_Secondary_MaxMana,GetMaxManaAttribute);
	
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//Replicate the attributes to everyone
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Health,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Mana,COND_None,REPNOTIFY_Always);
	
	/*
	 *VitalAttributes
	 *Primary Attribute
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Strength,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Intelligence,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Vigor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Resilence,COND_None,REPNOTIFY_Always);
	/*
	 *VitalAttributes
	 * Secondary Attributes
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,Armor,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ArmorPenetration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,BlockChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitChance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitDamage,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,CriticalHitResistance,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,HealthRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,ManaRegeneration,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHealth,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMana,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.f,GetMaxMana());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	/*
	 * 创建一个自己定义的ASC内部数据修改后需要记录的数据结构体的参数用于储存，方便后续逻辑执行（对这些信息进行UI提示）
	 */
	FEffectProperties Property;
	InitEffectProperty(Data,Property);
}

//This is a helper macro that can be used in RepNotify functions to handle attributes that will be predictively modified by clients.
void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Health,OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxHealth,OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Mana,OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,MaxMana,OldMaxMana);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Strength,OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Intelligence,OldIntelligence);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Vigor,OldVigor);
}

void UAuraAttributeSet::OnRep_Resilence(const FGameplayAttributeData& OldResilence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Resilence,OldResilence);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,Armor,OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ArmorPenetration,OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,BlockChance,OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitChance,OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitDamage,OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,CriticalHitResistance,OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,HealthRegeneration,OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,ManaRegeneration,OldManaRegeneration);
}

/*
 *Data：GAS属性发生改变时传递的回调数据（从PostGameplayEffectExecute传入）
 * Property（结构体保存上下文）
 * 即时类型属性触发这个回调（只有修改属性的基础值才会触发此回调）
 * 受击者ASC组件处理完之后属性扣除后，将数据打包成Data调用属性集自己的函数，从触发PostGameplayEffectExecute的函数将打包好的类型为FGameplayEffectModCallbackData类型的结构体传给函数作为参数使用
 */
void UAuraAttributeSet::InitEffectProperty(const struct FGameplayEffectModCallbackData& Data,
                                           FEffectProperties& Property)
    	{
			/*
			 *Data嵌入层级较深，主要是获取到一些属性游戏效果的相关信息，并存储在FEffectProperties中，避免冗余代码方便逻辑快速调用
			 * 将类型为FEffectProperties(自己封装好的结构体/这个结构体是为了处理一些属性修改后的一些数据)的Property结构体填充好
			 */
    		Property.SourceContextHandle = Data.EffectSpec.GetContext();
    		Property.AbilitySystemComponent = Property.SourceContextHandle.GetOriginalInstigatorAbilitySystemComponent();
    	
    		if (Property.AbilitySystemComponent && Property.AbilitySystemComponent->AbilityActorInfo && Property.AbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
    		{
    			/*
    			/*从AbilitySystemComponent的自带结构体AbilityActorInfo中获取Actor
    			/*从Actor中获取到PlayerController
    			 */
    			Property.AvatarActor = Property.AbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
    			Property.SourceController = Property.AbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
    			/*
    			 *
    			 * 可能存在有ASC组件的Actor不是玩家而是其他没有PlayerController的Actor所以从Pawn获取其他控制器（例如敌人的AIController）
    			 * 再从Controller拿到本体Character
    			 */
    			if (Property.SourceController == nullptr && Property.AvatarActor )
    			{
    				if (const APawn* TargetPawn = Cast<APawn>(Property.AvatarActor))
    				{
    					Property.SourceController = TargetPawn->GetController();
    				}
    			}
    			if (Property.SourceController)
    			{
    				Property.SourceCharacter = Cast<ACharacter>(Property.SourceController->GetPawn());
    			}
    		}
				/*
				   *
					 * 整理信息获取攻击方数据
				 */
    		if (Data.Target.AbilityActorInfo && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    		{
    			Property.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
    			Property.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
    			Property.TargetCharacter = Cast<ACharacter>(Property.TargetAvatarActor);
    			Property.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Property.TargetAvatarActor);
    		}
    	}
