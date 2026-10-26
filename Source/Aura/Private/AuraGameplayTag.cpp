// SixCatCompany.


#include "AuraGameplayTag.h"

#include "GameplayTagsManager.h"
FAuraGameplayTag FAuraGameplayTag::AuraGameplayTag;

void FAuraGameplayTag::InitActiveAuraGameplayTag()
{
	/*
	 *Primary Attributes
	 */
	AuraGameplayTag.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Strength"),FString("Promote Strength"));
	AuraGameplayTag.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Intelligence"),FString("Promote Intelligence"));
	AuraGameplayTag.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Vigor"),FString("Promote Vigor"));
	AuraGameplayTag.Attribute_Primary_Resilence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Resilence"),FString("Promote Resilence"));
	
	/*
	 *SecondaryAttribute
	 */
	AuraGameplayTag.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.Armor"),FString("Promote Resilence"));
	AuraGameplayTag.Attribute_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ArmorPenetration"),FString("Promote CriticalHitDamage and CriticalHitChance"));
	AuraGameplayTag.Attribute_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.BlockChance"),FString("Decrease Enemy's Damage"));
	AuraGameplayTag.Attribute_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitChance"),FString("Promote CriticalDamage Chance"));
	AuraGameplayTag.Attribute_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitDamage"),FString("Promote Damage"));
	AuraGameplayTag.Attribute_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitResistance"),FString("Decrease Enemy's CriticalHitChance and CriticalHitDamage"));
	AuraGameplayTag.Attribute_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.HealthRegeneration"),FString("Promote Health Regeneration Rate"));
	AuraGameplayTag.Attribute_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ManaRegeneration"),FString("Promote Mana Regeneration Rate"));
	AuraGameplayTag.Attribute_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"),FString("Promote MaxHealth"));
	AuraGameplayTag.Attribute_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"),FString("Promote MaxMana"));
	

}
