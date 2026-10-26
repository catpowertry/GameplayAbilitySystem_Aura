// SixCatCompany.


#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widget/AuraUserWidget.h"
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FAuraWidgetControllerParam& Param)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->InitWidgetController(Param);
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("Overlay Widget Class uninitialized,Please fill out BP_AuraHUD"))
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass uninitialized,Please fill out BP_AuraHUD"))
	
	UUserWidget* Widget=CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	UserWidget=Cast<UAuraUserWidget>(Widget);
	
	//Get OverlayWidgetController needs and init it
	const FAuraWidgetControllerParam Param(PC,PS,ASC,AS);
	UOverlayWidgetController* OverlayController = GetOverlayWidgetController(Param);
	//init WidgetController in Widget
	UserWidget->SetWidgetController(OverlayController);
	//init InitialValue progress in Widget
	OverlayController->BroadcastInitialValue();

	//work out all Initial things start Add to Viewport
    	Widget->AddToViewport();
}
