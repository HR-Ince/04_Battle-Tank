// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
    Super::BeginPlay();
    TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation)
{
    if(!ensure(TankAimingComponent)) { return; }
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
    return;
}

void ATank::Fire()
{
    if(!ensure(Barrel)) { return; }
    
    IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
    
    if(IsReloaded)
    {
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(Projectile_BP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
        
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
    }
}
