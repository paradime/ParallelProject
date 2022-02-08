// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->AddLocalRotation(FRotator(-80.f, 0.f, 0.f));
	SpringArmComponent->TargetArmLength = 1000.f;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->SetUsingAbsoluteRotation(true);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->SetupAttachment(GetRootComponent());
	SpawnVolume->SetBoxExtent(FVector(750.f, 1350.f, 32.f));

	// Don't rotate when the controller rotates
	// let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.f, 840.f, 0.f); // ...at this rotation rate.

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMainCharacter::MakeProjectile, 2.f);
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


	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
}

void AMainCharacter::MoveForward(float Value)
{
	if ((!Controller) || (Value == 0.f)) return;
	AddMovementInput(FVector(1.f, 0.f, 0.f), Value);
}

void AMainCharacter::MoveRight(float Value)
{
	if ((!Controller) || (Value == 0.f)) return;
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}

void AMainCharacter::MakeProjectile()
{
	if (!Projectile) return;

	FTimerHandle TimerHandle;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	auto Proj = GetWorld()->SpawnActor<AProjectile>(Projectile, GetActorLocation(), GetActorRotation(), SpawnParams);
	if (Proj) {
		Proj->SetDirection(GetActorRotation().Vector());
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMainCharacter::MakeProjectile, 2.f);
	}

}

void AMainCharacter::SpawnEnemy()
{
	if (!EnemyClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO ENEMY"));
		return;
	}

	const FRotator Rotation(0.f);
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor<AEnemy>(EnemyClass, GetRandomLocationOnSpawnVolumePerimeter(), Rotation, SpawnParameters);
}

FVector AMainCharacter::GetRandomLocationOnSpawnVolumePerimeter()
{
	const auto VolumeExtent = SpawnVolume->GetScaledBoxExtent();
	const auto CurrentLocation = GetActorLocation();
	float XLoc = CurrentLocation.X;
	float YLoc = CurrentLocation.Y;
	// location logic
	switch (FMath::RandRange(0,3))
	{
	case 0: // left side
		XLoc = FMath::FRandRange(CurrentLocation.X-VolumeExtent.X,CurrentLocation.X+VolumeExtent.X);
		YLoc = CurrentLocation.Y + VolumeExtent.Y;
		break;
	case 1: // South Side
		XLoc = CurrentLocation.X - VolumeExtent.X;
		YLoc = FMath::FRandRange(CurrentLocation.Y-VolumeExtent.Y,CurrentLocation.Y+VolumeExtent.Y);
		break;
	case 2: // right side
		XLoc = FMath::FRandRange(CurrentLocation.X-VolumeExtent.X,CurrentLocation.X+VolumeExtent.X);
		YLoc = CurrentLocation.Y - VolumeExtent.Y;
		break;
	case 3: // north side
		XLoc = CurrentLocation.X + VolumeExtent.X;
		YLoc = FMath::FRandRange(CurrentLocation.Y-VolumeExtent.Y,CurrentLocation.Y+VolumeExtent.Y);
		break;
	default:
		break;
	}
	return FVector(XLoc, YLoc, CurrentLocation.Z);
}

