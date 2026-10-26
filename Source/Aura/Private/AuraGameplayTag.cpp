// SixCatCompany.


#include "AuraGameplayTag.h"

#include "GameplayTagsManager.h"
FAuraGameplayTags FAuraGameplayTags::Tags;

void FAuraGameplayTags::InitActiveAuraGameplayTag()
{
	/*
	 *Primary Attributes
	 */
	Tags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Strength"),FString("Promote Strength"));
	Tags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Intelligence"),FString("Promote Intelligence"));
	Tags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Vigor"),FString("Promote Vigor"));
	Tags.Attribute_Primary_Resilence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Primary.Resilence"),FString("Promote Resilence"));
	
	/*
	 *SecondaryAttribute
	 */
	Tags.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.Armor"),FString("Promote Resilence"));
	Tags.Attribute_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ArmorPenetration"),FString("Promote CriticalHitDamage and CriticalHitChance"));
	Tags.Attribute_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.BlockChance"),FString("Decrease Enemy's Damage"));
	Tags.Attribute_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitChance"),FString("Promote CriticalDamage Chance"));
	Tags.Attribute_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitDamage"),FString("Promote Damage"));
	Tags.Attribute_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.CriticalHitResistance"),FString("Decrease Enemy's CriticalHitChance and CriticalHitDamage"));
	Tags.Attribute_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.HealthRegeneration"),FString("Promote Health Regeneration Rate"));
	Tags.Attribute_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.ManaRegeneration"),FString("Promote Mana Regeneration Rate"));
	Tags.Attribute_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxHealth"),FString("Promote MaxHealth"));
	Tags.Attribute_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Secondary.MaxMana"),FString("Promote MaxMana"));
	

}
