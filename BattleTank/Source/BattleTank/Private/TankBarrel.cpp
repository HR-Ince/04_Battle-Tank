// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    auto BarrelSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
    auto ElevationByFrame = BarrelSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto NewElevation = RelativeRotation.Roll + ElevationByFrame;
    auto Elevation = FMath::Clamp(
                                 NewElevation,
                                 MinElevationDegrees,
                                 MaxElevationDegrees);
    
    SetRelativeRotation(FRotator(0, 0, Elevation));
    }


