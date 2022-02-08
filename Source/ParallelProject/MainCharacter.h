// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class PARALLELPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mechanics)
	float SpawnXExtent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mechanics)
	float SpawnYExtent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mechanics)
		TSubclassOf<class AEnemy> EnemyClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mechanics)
	TArray<AActor*> ExistingEnemies;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
		void MakeProjectile();

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

private:
	FVector GetRandomLocationOnSpawnVolumePerimeter();
};
