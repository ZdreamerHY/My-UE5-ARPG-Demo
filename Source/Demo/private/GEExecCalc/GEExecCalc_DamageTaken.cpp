// Fill out your copyright notice in the Description page of Project Settings.


#include "GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/DemoGameplayTags.h"
#include "AbilitySystem/DemoAttributeSet.h"

struct FDemoDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	FDemoDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDemoAttributeSet,AttackPower,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDemoAttributeSet,DefensePower,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UDemoAttributeSet,DamageTaken,Target,false);
	}
};

static const FDemoDamageCapture& GetDemoDamageCapture()
{
	static FDemoDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetDemoDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetDemoDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetDemoDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	FAggregatorEvaluateParameters EvaluationParameters;
	FGameplayEffectSpec EffectSpec= ExecutionParams.GetOwningSpec();
	EvaluationParameters.SourceTags=EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluationParameters.TargetTags=EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower=0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDemoDamageCapture().AttackPowerDef,EvaluationParameters,SourceAttackPower);

	float TargetDefensePower=0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDemoDamageCapture().DefensePowerDef,EvaluationParameters,TargetDefensePower);

	float WeaponBaseDamage=0.0f;
	for (const TPair<FGameplayTag,float>& TagMagnitude: EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(DemoGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			WeaponBaseDamage=TagMagnitude.Value;
		}
	}

	const float FinalDamage=WeaponBaseDamage+SourceAttackPower-TargetDefensePower;

	if (FinalDamage>0)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData( GetDemoDamageCapture().DamageTakenProperty,EGameplayModOp::Override,FinalDamage
				)
			);
	}
}

