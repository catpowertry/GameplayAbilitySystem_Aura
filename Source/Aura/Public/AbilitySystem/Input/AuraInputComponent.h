// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

class UAuraInputConfig;
/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	template<class UserClass , typename PressedFuncType , typename ReleasedFuncType ,typename HeldFuncType >
	void BindAbilityActions(const UAuraInputConfig* Config, UserClass* Object, PressedFuncType PressedFunc ,ReleasedFuncType ReleasedFunc,HeldFuncType HeldFunc);
	
	
}
;

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* Config, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{

	check(Config)
	for (const FAuraInputAction& Action : Config->AuraInputConfigs)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Completed,Object,ReleasedFunc,Action.InputTag);
			}
			if (PressedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started,Object,PressedFunc,Action.InputTag);
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,Action.InputTag);
			}
		}
	}



}
