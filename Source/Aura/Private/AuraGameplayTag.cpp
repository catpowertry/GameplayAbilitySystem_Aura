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
	
	/*
	 *InputActionTag 
	 */
	Tags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),FString("InputTag for ActionLMB"));
	Tags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString("InputTag for ActionRMB"));
	Tags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),FString("InputTag for Action1"));
	Tags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"),FString("InputTag for Action2"));
	Tags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"),FString("InputTag for Action3"));
	Tags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"),FString("InputTag for Action4"));
}
