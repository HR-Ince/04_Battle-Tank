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
    
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::SetReferences(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    TankAimingComponent->SetBarrelReference(BarrelToSet);
    TankAimingComponent->SetTurretReference(TurretToSet);
    Barrel = BarrelToSet;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void ATank::AimAt(FVector HitLocation)
{
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
    return;
}

void ATank::Fire()
{
    UE_LOG(LogTemp, Error, TEXT("Firing!"));
    
    if(!Barrel) { return; }
    
    
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    FRotator StartRotation = Barrel->GetSocketRotation(FName("Projectile"));
    GetWorld()->SpawnActor<AProjectile>(Projectile_BP, StartLocation, StartRotation);
}
