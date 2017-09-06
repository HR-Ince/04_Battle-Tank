// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimComp);
    
private:
    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    bool GetLookDirection(FVector2D, FVector&) const;
    bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
    FVector GetWidgetLocation();
    FVector GetRange();
	
    UPROPERTY(EditAnywhere)
    float CrosshairXLocation = 0.5;
    UPROPERTY(EditAnywhere)
    float CrosshairYLocation = 0.33333;
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000;
    
public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
	
};
