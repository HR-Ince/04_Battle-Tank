// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Classes/PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class URadialForceComponent;
class UStaticMeshComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* CollisionMesh = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* LaunchBlast = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UParticleSystemComponent* ImpactBlast = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    URadialForceComponent* ExplosiveForce = nullptr;
    
    UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

private:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    void OnTimerExpire();
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float DestroyDelay = 10;
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ProjectileDamage = 20;
    
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    void LaunchProjectile(float Speed);
	
    
};
