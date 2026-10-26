// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraWidgetController.generated.h"
USTRUCT(BlueprintType)
struct FAuraWidgetControllerParam
{
	
	GENERATED_BODY()
	
	FAuraWidgetControllerParam(){};
	FAuraWidgetControllerParam(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS):
	 PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS)
	{
	}
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TObjectPtr<APlayerController> PlayerController = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TObjectPtr<APlayerState> PlayerState = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};
/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly,Category="Widget")
	TObjectPtr<APlayerController> PlayerController;
	
	UPROPERTY(BlueprintReadOnly,Category="Widget")
	TObjectPtr<APlayerState> PlayerState;
	
	UPROPERTY(BlueprintReadOnly,Category="Widget")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly,Category="Widget")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	/*
	 * BroadcastInitialValue：初始化，在UI加载的瞬间绑定初始数据
	 * BindCallbacksToDependencies：订阅GAS属性变更依赖，做好数据监听
	 */
	virtual void BroadcastInitialValue();
	
    virtual void BindCallbacksToDependencies();
	
	void InitWidgetController(const FAuraWidgetControllerParam& Param);
};
