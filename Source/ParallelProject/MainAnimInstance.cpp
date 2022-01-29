// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

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
}
