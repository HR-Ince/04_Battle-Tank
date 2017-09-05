// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
    UPROPERTY(BlueprintReadOnly)
    UTankAimingComponent* TankAimingComponent = nullptr;
    UPROPERTY(BlueprintReadOnly)
    UTankMovementComponent* TankMovementComponent;

public:
    UFUNCTION(BlueprintCallable, Category = Action)
    void Fire();
    
    UPROPERTY(BlueprintReadOnly)
    bool IsReloaded = true;
    
    
    void AimAt(FVector HitLocation);
    
private:
    UTankBarrel* Barrel = nullptr;
    
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 100000;
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    TSubclassOf<AProjectile> Projectile_BP;
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float ReloadTimeInSeconds = 3;
    
    double LastFireTime = 0;
};
