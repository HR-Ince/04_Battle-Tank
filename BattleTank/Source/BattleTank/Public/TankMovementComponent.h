// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrack;
/**
 * Responsible for driving the tank tracks.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
private:
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
    
    UTankTrack* RightTrack = nullptr;
    UTankTrack* LeftTrack = nullptr;
    
public:
    UFUNCTION(BlueprintCallable)
    void IntendMoveForward(float Throw);
    UFUNCTION(BlueprintCallable)
    void IntendTurnRight(float Throw);
    UFUNCTION(BlueprintCallable)
    void Initialise(UTankTrack* LeftTracktoSet, UTankTrack* RightTracktoSet);
	
	
};
