// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionMesh =
    CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Component"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(false);
    
    LaunchBlast =
        CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->SetupAttachment(CollisionMesh);
    
    ImpactBlast =
        CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->SetupAttachment(CollisionMesh);
    ImpactBlast->bAutoActivate = false;
    
    ExplosiveForce =
        CreateDefaultSubobject<URadialForceComponent>(FName("Explosive Force"));
    ExplosiveForce->SetupAttachment(CollisionMesh);
    
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
    ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float Speed)
{
    ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    LaunchBlast->Deactivate();
    ImpactBlast->Activate();
    ExplosiveForce->FireImpulse();
    
    SetRootComponent(ImpactBlast);
    CollisionMesh->DestroyComponent();
    
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
    Destroy();
}
