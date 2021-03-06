// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
    UTankTrack();
    virtual void BeginPlay() override;
    
    void ApplySidewaysForce();
    void DriveTrack();
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
    float CurrentThrottle = 0;
    
public:
    UFUNCTION(BlueprintCallable, Category = input)
    void SetThrottle(float Throttle);
	
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 107280;
	
};
