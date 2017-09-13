// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
    LastFireTime = FPlatformTime::Seconds();
}

int32 UTankAimingComponent::GetAmmoCount() const
{
    return AmmoCount;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    if(GetAmmoCount() == 0)
    {
        FiringState = EFiringState::OutOfAmmo;
    } else if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
    {
        FiringState = EFiringState::Reloading;
    } else if(IsBarrelMoving())
    {
        FiringState = EFiringState::Aiming;
    } else
    {
        FiringState = EFiringState::Locked;
    }
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if(!ensure(Barrel)) { return; }
    
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    
    bool bAimingSolutionFound = UGameplayStatics::SuggestProjectileVelocity(
                                                    this,
                                                    OutLaunchVelocity,
                                                    StartLocation,
                                                    HitLocation,
                                                    LaunchSpeed,
                                                    false,
                                                    0,
                                                    0,
                                                    ESuggestProjVelocityTraceOption::DoNotTrace
                                                    );
    
    if(bAimingSolutionFound)
    {
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
    
}

void UTankAimingComponent::MoveBarrelTowards(FVector Aim)
{
    if(!ensure(Barrel && Turret)) { return; }
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = Aim.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    
    
    Barrel->Elevate(DeltaRotator.Pitch);
    if(FMath::Abs(DeltaRotator.Yaw) > 180)
    {
         Turret->Rotate(-DeltaRotator.Yaw);
    } else
    {
        Turret->Rotate(DeltaRotator.Yaw);
    }
}


void UTankAimingComponent::Fire()
{
    if(FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo)
    {
        if(!ensure(Barrel)) { return; }
        if(!ensure(ProjectileBP)) { return; }
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                                              ProjectileBP,
                                              Barrel->GetSocketLocation(FName("Projectile")),
                                              Barrel->GetSocketRotation(FName("Projectile"))
                                              );
        
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = FPlatformTime::Seconds();
        AmmoCount--;
    }
}
bool UTankAimingComponent::IsBarrelMoving()
{
    return !(Barrel->GetForwardVector().Equals(AimDirection, 0.01));
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}
