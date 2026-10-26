// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AuraDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeIntroduction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura|Attribute")
	FText AttributeName;

	UPROPERTY(BlueprintReadOnly, Category = "Aura|Attribute")
	float AttributeValue;
};
/**
 * 
 */
UCLASS()
class AURA_API UAuraDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AuraAttributesList;
	
	UFUNCTION(BlueprintCallable)
	FAuraAttributeInfo AttributeInfo(FGameplayTag AttributeTag,bool bLogNotFound);
};
