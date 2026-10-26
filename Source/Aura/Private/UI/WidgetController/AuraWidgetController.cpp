// SixCatCompany.


#include "UI/WidgetController/AuraWidgetController.h"
/*
 */
void UAuraWidgetController::BroadcastInitialValue()
{
	
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
	
}

void UAuraWidgetController::InitWidgetController(const FAuraWidgetControllerParam& Param)
{
	PlayerController = Param.PlayerController;
	PlayerState = Param.PlayerState;
	AbilitySystemComponent = Param.AbilitySystemComponent;
	AttributeSet = Param.AttributeSet;
}
