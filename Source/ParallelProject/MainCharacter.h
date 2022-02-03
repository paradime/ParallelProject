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

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	//	bool bIsRolling;

	//FTimerHandle RollDurationHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		float YMove;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
		float XMove;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//float YPoint;
	//float XPoint;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	//void PointForward(float Value);
	//void PointRight(float Value);

	//UFUNCTION(BlueprintNativeEvent)
	//	void Roll();

	//UFUNCTION(BluePrintCallable)
	//	void UpdateRollLocation(float XLoc, float YLoc);

	//FORCEINLINE void StopRolling() {
	//	bIsRolling = false;
	//}
private:
	//void UpdateFaceDirection();
};
