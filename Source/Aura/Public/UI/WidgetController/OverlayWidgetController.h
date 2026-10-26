// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"
class UAuraUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetTable : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "WidgetTable")
	FGameplayTag EffectTag = FGameplayTag();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "WidgetTable")
	FText Message = FText();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "WidgetTable")
	UTexture2D* Texture;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "WidgetTable")
	TSubclassOf<UAuraUserWidget> UserWidget;
};
struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetTable,WidgetAssetMessage);
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "EffectAssetTabel")
	TObjectPtr<UDataTable> DataTable;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangeSignature OnHealthChange;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangeSignature OnMaxHealthChange;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangeSignature OnManaChange;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangeSignature OnMaxManaChange;
	
	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FMessageWidgetRowSignature MessageWidgetRow;
	
	virtual void BroadcastInitialValue() override;
    	
    virtual void BindCallbacksToDependencies() override;
	
	//用于查询获取到某个效果后从效果中查询为其配置好的结构体方便UI显示
	template<typename T>
	T* FindTableRow(UDataTable* Table,const FGameplayTag Tag)
	{
		return Table->FindRow<T>(Tag.GetTagName(),TEXT(" "));
	}
};
