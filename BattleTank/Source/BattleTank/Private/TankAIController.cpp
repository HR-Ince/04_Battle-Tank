// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    
    auto PlayerTank = GetPlayerTank();
    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController cannot find Player."))
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController found Player at %s"), *PlayerTank->GetName())
    }

}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(GetPlayerTank())
    {
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
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
