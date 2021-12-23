// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TestAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class POSSESION_API UTestAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	UPROPERTY(EditAnywhere, BluePrintReadonly, Category = "Movement")
	class ATestChar* PlayerPawn;

	UPROPERTY(EditAnywhere, BluePrintReadonly, Category = "Movement")
	float MoveSpeed;
	
};
