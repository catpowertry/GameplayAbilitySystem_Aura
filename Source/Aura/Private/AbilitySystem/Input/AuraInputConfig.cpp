// SixCatCompany.


#include "AbilitySystem/Input/AuraInputConfig.h"


/*
 *
 * 查找函数
 */
const UInputAction* UAuraInputConfig::InputActionFinder(const FGameplayTag& Tag , bool bLogNotFound) const 
{
	
	
	
	for (const auto &Pair : AuraInputConfigs)
	{
		if(Tag == Pair.InputTag)
		{
			return Pair.InputAction;
		}	
	}
	
	if (bLogNotFound)
	{
		
		UE_LOG(LogTemp,Warning,TEXT("Can't find AbilityInputAction for Tag [%s] ,on InputConfig [%s]"),*Tag.ToString(),*GetNameSafe(this))
    }
		return nullptr;
}
