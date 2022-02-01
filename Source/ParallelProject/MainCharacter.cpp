// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->AddLocalRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = 1000.f;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->SetUsingAbsoluteRotation(true);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	// Don't rotate when the controller rotates
	// let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 840.f, 0.f); // ...at this rotation rate.

	YPoint = 1;
	XPoint = 0;
	XMove = 1;
	YMove = 0;

	bIsRolling = false;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Roll", EInputEvent::IE_Pressed, this, &AMainCharacter::Roll);


	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("PointForward", this, &AMainCharacter::PointForward);
	PlayerInputComponent->BindAxis("PointRight", this, &AMainCharacter::PointRight);
}

void AMainCharacter::MoveForward(float Value)
{
	if (!bIsRolling) XMove = Value;
	if ((!Controller) || (Value == 0.f) || (bIsRolling)) return;
	AddMovementInput(FVector(1.f, 0.f, 0.f), Value);
}

void AMainCharacter::MoveRight(float Value)
{
	if (!bIsRolling) YMove = Value;
	if ((!Controller) || (Value == 0.f) || (bIsRolling)) return;
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}

void AMainCharacter::PointForward(float Value)
{
	XPoint = Value;
	UpdateFaceDirection();
}

void AMainCharacter::PointRight(float Value)
{
	YPoint = Value;
	UpdateFaceDirection();
}

void AMainCharacter::Roll_Implementation()
{
	//bIsRolling = true;
	//FVector RollDirection = FVector(XMove, YMove, 0.f);
	//GetWorldTimerManager().SetTimer(RollDurationHandle, this, &AMainCharacter::StopRolling, 1.7f);
}

void AMainCharacter::UpdateRollLocation(float XLoc, float YLoc)
{
	FVector NewLocation = GetActorLocation();
	NewLocation.X += XLoc;
	NewLocation.Y += YLoc;
	SetActorLocation(NewLocation);
}

void AMainCharacter::UpdateFaceDirection()
{
	if (bIsRolling) return;
	if (XPoint == 0 && YPoint == 0) return;
	FVector point = FVector(XPoint, YPoint, 0.f);
	GetController()->SetControlRotation(point.Rotation());
}

