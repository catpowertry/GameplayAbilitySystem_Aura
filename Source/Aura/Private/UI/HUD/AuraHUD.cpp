// SixCatCompany.


#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

/*
 *
 * 因为HUD作为总控应该拥有所有覆层或者Widget的WidgetController所以应该需要一个Get函数获取，为了防止为空需要判定是否拥有并进行创建
 */
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

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FAuraWidgetControllerParam& Param)
{
	
	if (!AttributeMenuController)
	{
		AttributeMenuController = NewObject<UAttributeMenuWidgetController>(this,AttributeMenuControllerClass);
		AttributeMenuController->InitWidgetController(Param);
		AttributeMenuController->BindCallbacksToDependencies();
		return AttributeMenuController;
	}
	
	return AttributeMenuController;
	
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("Overlay Widget Class uninitialized,Please fill out BP_AuraHUD"))
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass uninitialized,Please fill out BP_AuraHUD"))
	
	UUserWidget* Widget=CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget=Cast<UAuraUserWidget>(Widget);
	
	//Get OverlayWidgetController needs and init it
	const FAuraWidgetControllerParam Param(PC,PS,ASC,AS);
	UOverlayWidgetController* OverlayController = GetOverlayWidgetController(Param);
	//init WidgetController in Widget
	OverlayWidget->SetWidgetController(OverlayController);
	//init InitialValue progress in Widget
	OverlayController->BroadcastInitialValue();

	//work out all Initial things start Add to Viewport
    	Widget->AddToViewport();
}
