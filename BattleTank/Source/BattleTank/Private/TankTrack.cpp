// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(),GetRightVector());
    auto CorrectiveAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectiveForce = (TankRoot->GetMass() * CorrectiveAcceleration) / 2;
    
    TankRoot->AddForce(CorrectiveForce);
}
void UTankTrack::SetThrottle(float Throttle)
{
    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}


