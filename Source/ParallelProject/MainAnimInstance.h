// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class PARALLELPROJECT_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Movement)
		float MovementSpeed;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Movement)
		class APawn* Pawn;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Movement)
		bool bIsRolling;

public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)
		void UpdateAnimationProperties();

private:
	FORCEINLINE void CheckPawn() {
		if (!Pawn) Pawn = TryGetPawnOwner();
	};
};
