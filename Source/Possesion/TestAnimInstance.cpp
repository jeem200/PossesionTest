// Fill out your copyright notice in the Description page of Project Settings.


#include "TestAnimInstance.h"
#include "TestChar.h"
#include "Kismet/KismetMathLibrary.h"

void UTestAnimInstance::NativeInitializeAnimation()
{
	if (PlayerPawn == nullptr)
	{
		APawn* CurrentPawn = TryGetPawnOwner();

		PlayerPawn = Cast<ATestChar>(CurrentPawn);
	}
}

void UTestAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (PlayerPawn)
	{
		FVector Speed = PlayerPawn->GetVelocity();

		MoveSpeed = FVector(Speed.X, Speed.Y, 0.0f).Size();
	}
}
