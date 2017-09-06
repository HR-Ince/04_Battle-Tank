// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ThisTank = Cast<ATank>(GetPawn());
    
    if(ensure(PlayerTank))
    {
        MoveToActor(PlayerTank, AcceptanceRadius);
        
        ThisTank->AimAt(PlayerTank->GetActorLocation());
        
        //ThisTank->Fire();
    }
}
