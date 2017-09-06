// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if(ensure(PlayerTank))
    {
        MoveToActor(PlayerTank, AcceptanceRadius);
        
        GetPawn()->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());
        
        //ThisTank->Fire();
    }
}
