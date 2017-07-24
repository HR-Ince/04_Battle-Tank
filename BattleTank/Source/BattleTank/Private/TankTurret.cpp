// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    auto TurretSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
    auto RotationChange = TurretSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto Rotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, Rotation, 0));
}
