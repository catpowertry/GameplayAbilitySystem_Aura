// SixCatCompany.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTag.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAttributeMenuWidgetController::BroadcastInitialValue()
 {
 	Super::BroadcastInitialValue();
	
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
    	/*
    	 * 获取Attribute利用广播初始化AttributeMenu数据
    	 * 再利用获取到的AttributeSet初始化真实数据
    	 * 最后再投送数据
    	 */
	check(AttributeInfo);
	
	/*
	 *
	 * 遍历查找，蓝图中自动适配初始化属性值
	 */
	for (auto &Pair : AS->AttributeMap)
	{
		BroadcastInfo(Pair,AS);
	}
 }
 
 /*
  *
  * 绑定数据委托
  */
 void UAttributeMenuWidgetController::BindCallbacksToDependencies()
 {
 	Super::BindCallbacksToDependencies();
	
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	for (auto &Pair : AS->AttributeMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[Pair,this,AS](const FOnAttributeChangeData& Data)
			{
			BroadcastInfo(Pair,AS);
			}
			);
	}
 }
