// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController not possessing tank"));
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s"), *ControlledTank->GetName());
    }
    auto PlayerTank = GetPlayerTank();
    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController cannot find Player."))
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController found Player at %s"), *PlayerTank->GetName())
    }

}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

