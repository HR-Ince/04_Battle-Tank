// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
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
        
        auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
        AimingComponent->AimAt(PlayerTank->GetActorLocation());
        
        //AimingComponent->Fire();
    }
}
