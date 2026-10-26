// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UAuraWidgetController;
class UOverlayWidgetController;
class UAuraUserWidget;
struct FAuraWidgetControllerParam;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:	
	/*
	 *用于储存转化后的Widget源为OverlayWidgetClass
	 */
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> UserWidget;
	
	//判断Controller是否有问题选择重新创建或者直接返回OverlayWidgetController
	UOverlayWidgetController* GetOverlayWidgetController(const FAuraWidgetControllerParam& Param);
	
	UFUNCTION()
	void InitOverlay(APlayerController* PC,APlayerState* PS,UAbilitySystemComponent* ASC,UAttributeSet* AS);
private:
	/*
     *HUD上的Widget，用于初始化此WidgetController的WidgetController初始化不是由Widget自己进行的，而是以HUD进行总数据管理，利用数据发放进行初始化，防止数据散落
     * 
     */
	UPROPERTY(EditAnywhere)
TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	const TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
