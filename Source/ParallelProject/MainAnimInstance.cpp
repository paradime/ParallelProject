// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "MainCharacter.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	CheckPawn();
}

void UMainAnimInstance::UpdateAnimationProperties()
{
	CheckPawn();
	if (!Pawn) return;
	FVector Speed = Pawn->GetVelocity();
	MovementSpeed = FVector(Speed.X, Speed.Y, 0.f).Size();
	AMainCharacter* Main = Cast<AMainCharacter>(Pawn);
	//if (Main) {
	//	bIsRolling = Main->bIsRolling;
	//}

}
