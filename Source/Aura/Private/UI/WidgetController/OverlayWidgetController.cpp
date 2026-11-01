 // SixCatCompany.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

 void UOverlayWidgetController::BroadcastInitialValue()
 {
 	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
 	OnHealthChange.Broadcast(AuraAttributeSet->GetHealth());
 	OnMaxHealthChange.Broadcast(AuraAttributeSet->GetMaxHealth());
 	
 	OnManaChange.Broadcast( AuraAttributeSet->GetMana());
 	OnMaxManaChange.Broadcast( AuraAttributeSet->GetMaxMana());
 }

//绑定委托用于数据改变时实时投放数据
 void UOverlayWidgetController::BindCallbacksToDependencies()
 {
 	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
 	//使用匿名函数绑定变化的属性委托并进行数据投放
 	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda([AuraAttributeSet,this](const FOnAttributeChangeData& Data)
 	{
 		OnHealthChange.Broadcast(Data.NewValue);
 	}
 	);
 	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda([AuraAttributeSet,this](const FOnAttributeChangeData& Data)
	 {
		 OnMaxHealthChange.Broadcast(Data.NewValue);
	 }
	 );
 	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda([AuraAttributeSet,this](const FOnAttributeChangeData& Data)
	 {
		 OnManaChange.Broadcast(Data.NewValue);
	 }
	 );
 	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda([AuraAttributeSet,this](const FOnAttributeChangeData& Data)
	 {
		 OnMaxManaChange.Broadcast(Data.NewValue);
	 }
	 );
 	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->FActiveTagDelegate.AddLambda(
 	[this] (const FGameplayTagContainer& Container)
 	{
 		if (DataTable == nullptr) return;
 		for(const FGameplayTag& Tag : Container)
 		{
 			//"A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
 			FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
 			if (Tag.MatchesTag(MessageTag))
 			{
 				const FUIWidgetTable* WidgetTable = FindTableRow<FUIWidgetTable>(DataTable,Tag);
 				if (WidgetTable == nullptr) return;
 				MessageWidgetRow.Broadcast(*WidgetTable);
 			}
 		}
 	}
 	);
 }


