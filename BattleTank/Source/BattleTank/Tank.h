// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
    
    FTankDelegate OnTankDeath;
    
    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercent() const;
    
private:
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 200;
    
    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 CurrentHealth = StartingHealth;
};
