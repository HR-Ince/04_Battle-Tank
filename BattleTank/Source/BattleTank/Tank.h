// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    UTankAimingComponent* TankAimingComponent = nullptr;

public:
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetReferences(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = Action)
    void Fire();
    
    void AimAt(FVector HitLocation);
    
private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UTankBarrel* Barrel = nullptr;
    
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 100000;
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    TSubclassOf<AProjectile> Projectile_BP;
    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float ReloadTimeInSeconds = 3;
    
    double LastFireTime = 0;
};
