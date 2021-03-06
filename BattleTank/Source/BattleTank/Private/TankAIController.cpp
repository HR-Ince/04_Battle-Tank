// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    
    if(InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank)) { return; }
        
        PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}

void ATankAIController::OnPossessedTankDeath()
{
    if(!GetPawn) { return; }
    GetPawn()->DetachFromControllerPendingDestroy();
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
        
        if(AimingComponent->GetFiringState() == EFiringState::Locked)
        {
            AimingComponent->Fire();
        }
    }
}
