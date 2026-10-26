// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

class UAuraWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly,Category="Widget")
	TObjectPtr<UObject> WidgetController;
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* WidgetControllerObject);
	
protected:
	//获取WidgetController，用于初始化AuraWidget内的子AuraWidget（每个Widget中可能存在多个Widget）
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
