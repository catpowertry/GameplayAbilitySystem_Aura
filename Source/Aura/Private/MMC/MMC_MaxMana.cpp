// SixCatCompany.


#include "MMC/MMC_MaxMana.h"

#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceContainer = Spec.CapturedSourceTags.GetAggregatedTags(); 
	const FGameplayTagContainer* TargetContainer = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceContainer;
	EvaluationParameters.TargetTags = TargetContainer;
	
	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef,Spec,EvaluationParameters,Intelligence);
	Intelligence = FMath::Max<float>(Intelligence,0.f);
	
	const ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetEffectContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	
	return 20.f + Intelligence*2 + PlayerLevel*5.f;
}
