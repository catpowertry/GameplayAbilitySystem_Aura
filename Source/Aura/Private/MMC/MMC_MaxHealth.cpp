// SixCatCompany.


#include "MMC/MMC_MaxHealth.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	/*
	 *
	 * 为Vigor提供相关Container，使Vigor对应值是正确的（存在Debuff，存在Buff）
	 */
	const FGameplayTagContainer* SourceContainer = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetContainer = Spec.CapturedTargetTags.GetAggregatedTags();
	/*
	 *
	 * 设置评估参数，获取Vigor对应的值
	 */
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceContainer;
	EvaluationParameters.TargetTags = TargetContainer;
	
	float VigorValue = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, VigorValue);
	VigorValue = FMath::Max<float>(VigorValue, 0.f);
	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();
	
	return 80.f + VigorValue * 2.f + PlayerLevel * 10.f;
}
