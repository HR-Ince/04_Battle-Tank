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
    Reloading,
    OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds methods for aiming and firing
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Aiming;

private:
    // Sets default values for this component's properties
    UTankAimingComponent();
    
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    void MoveBarrelTowards(FVector AimDirection);
    bool IsBarrelMoving();
    
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    double LastFireTime = 0;
    FVector AimDirection;
    
    UPROPERTY(EditAnywhere, Category = "Firing")
    float LaunchSpeed = 100000;
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    TSubclassOf<AProjectile> ProjectileBP;
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3;
    
public:
    void AimAt(FVector HitLocation);
    EFiringState GetFiringState() const;
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    UFUNCTION(BlueprintCallable, Category = "Firing")
    int32 GetAmmoCount() const;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 AmmoCount = 3;
};
