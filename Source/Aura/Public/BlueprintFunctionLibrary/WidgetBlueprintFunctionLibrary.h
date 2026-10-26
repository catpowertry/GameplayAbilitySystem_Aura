// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetBlueprintFunctionLibrary.generated.h"

class UOverlayWidgetController;
class UAuraWidgetController;
/**
 * 
 */
UCLASS()
class AURA_API UWidgetBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	/*
	 *1.BlueprintPure让这个蓝图不是一个运行节点只负责输入数据计算输出数据
	 * 2.一定是静态函数（因为不需要任何前后文就可以直接调用函数获取数据）
	 */
	UFUNCTION(BlueprintPure,Category = "BlueprintLibrary")
	static UOverlayWidgetController* GetOverlayWidgetController(UObject* WorldContextObject);
};
