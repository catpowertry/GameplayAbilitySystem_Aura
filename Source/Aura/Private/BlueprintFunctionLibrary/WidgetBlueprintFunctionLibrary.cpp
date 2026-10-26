// SixCatCompany.


#include "BlueprintFunctionLibrary/WidgetBlueprintFunctionLibrary.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "Aura/Public/UI/WidgetController/AuraWidgetController.h"
#include "UI/HUD/AuraHUD.h"


UOverlayWidgetController* UWidgetBlueprintFunctionLibrary::GetOverlayWidgetController(UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0);
	if (PC)
	{
		if (AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState* PS = Cast<AAuraPlayerState>(PC->PlayerState);
				if (PS)
				{
					UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
					UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(PS->GetAttributeSet());
					const FAuraWidgetControllerParam Params(PC,PS,ASC,AS);
					return HUD->GetOverlayWidgetController(Params);
				}
		}
	}
	 
	return nullptr;
			
}
