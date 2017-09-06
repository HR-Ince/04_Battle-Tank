// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringState : uint8
{
    Aiming,
    Locked,
    Reloading
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Locked;

private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    void MoveBarrelTowards(FVector AimDirection);
    
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    double LastFireTime = 0;
    
    UPROPERTY(EditAnywhere, Category = "Firing")
    float LaunchSpeed = 100000;
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    TSubclassOf<AProjectile> ProjectileBP;
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;
    
public:
    void AimAt(FVector HitLocation);
    
    UFUNCTION(BlueprintCallable, Category = "Action")
    void Fire();
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    UPROPERTY(BlueprintReadOnly)
    bool IsReloaded = true;
};
