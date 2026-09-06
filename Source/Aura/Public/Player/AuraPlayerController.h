// SixCatCompany.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,Category="MappingContext")
	TObjectPtr<UInputMappingContext> AuraMappingContext;
};
