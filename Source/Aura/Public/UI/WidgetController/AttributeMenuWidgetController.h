// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "Aura/Data/AuraDataAsset.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeMenuInfoSignature,const FAuraAttributeInfo&,InfoName);
/**
 * 
 */
UCLASS()
class AURA_API UAttributeMenuWidgetController : public UOverlayWidgetController
{
	GENERATED_BODY()
public:
	/*
	 * 只用于初始化投送一些数据
	 */
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValue() override;
	
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable)
	FAttributeMenuInfoSignature AttributeMenuInfoDelegate;
	
	/*
	 * 获取到数据源方便获取到对应GameplayTag
	 */
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UAuraDataAsset> AttributeInfo;
	
	void BroadcastInfo(const TPair<FGameplayTag, FGameplayAttribute(*)()>& Pair,const UAttributeSet* AS ) const 
	{
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfo(Pair.Key,false);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeMenuInfoDelegate.Broadcast(Info);
	}
};
