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
    
    if(Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        Cast<ATank>(GetPawn())->AimAt((GetWorld()->GetFirstPlayerController()->GetPawn())->GetActorLocation());
        
        //Cast<ATank>(GetPawn())->Fire();
    }
}
