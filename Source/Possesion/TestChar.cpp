// Fill out your copyright notice in the Description page of Project Settings.


#include "TestChar.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
ATestChar::ATestChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward",this,&ATestChar::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ATestChar::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &ATestChar::PressSpace);

}

void ATestChar::InitializeDefault()
{
	//spring arm setup
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	///camera setup
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;

	//movement component setup

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ATestChar::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{


		const FRotator YawRotattion(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotattion).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction * Value);
	}
}

void ATestChar::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{


		const FRotator YawRotattion(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotattion).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction * Value);
	}
}

void ATestChar::PressSpace()
{
	if (GetVelocity().Size() > 0.f)
	{
		Dodge();
	}
}

void ATestChar::Dodge()
{

	UAnimInstance* AttachedAinmInstance = GetMesh()->GetAnimInstance();



	FRotator DesiredRotation = UKismetMathLibrary::MakeRotFromX(GetLastMovementInputVector());

	SetActorRotation(DesiredRotation);

	if (AttachedAinmInstance != nullptr && DodgeMontage)
	{


		if (!AttachedAinmInstance->Montage_IsPlaying(DodgeMontage))
		{
			AttachedAinmInstance->Montage_Play(DodgeMontage, 1.0f);
			AttachedAinmInstance->Montage_JumpToSection(FName("Roll"), DodgeMontage);
		}



	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::White, TEXT("No AnimInstance"));
	}
}

