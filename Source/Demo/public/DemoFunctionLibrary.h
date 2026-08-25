// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DemoFunctionLibrary.generated.h"

struct FGameplayTag;
class ADemoBaseCharacter;
class UPawnCombatComponentBase;

UENUM()
enum class EDemoConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EDemoValidType : uint8
{
	Valid,
	InValid
};
/**
 * 
 */
UCLASS()
class DEMO_API UDemoFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UPawnCombatComponentBase* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary",meta=(DisplayName="Get Pawn Combat Component",ExpandEnumAsExecs="OutValidType"))
	static UPawnCombatComponentBase* BP_GetUPawnCombatComponentFromActor(AActor* InActor,EDemoValidType& OutValidType);

	UFUNCTION(BlueprintCallable,Category = "FunctionLibrary")
	static void AddTagToActorIfNone(AActor* TargetActor,FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable,Category = "FunctionLibrary")
	static void RemoveGameplayFromActorIfFound(AActor* TargetActor,FGameplayTag TagToRemove);

	UFUNCTION(BlueprintPure,Category = "FunctionLibrary")
	static bool DoesActorHaveTag(AActor* Actor,FGameplayTag TagToCheck);

	//辅助函数，判断两个角色是否应该敌对
	UFUNCTION(BlueprintPure,Category = "FunctionLibrary")
	static  bool IsTargetPawnHostile(APawn* SelfPawn,APawn* TargetPawn) ;

	//辅助函数，通过点积运算判断攻击是否能被阻挡
	UFUNCTION(BlueprintPure,Category = "FunctionLibrary")
	static bool IsValidBlock(AActor* AttackActor,AActor* DefenderActor) ;
};
