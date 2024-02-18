// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "PaperSpriteComponent.h"
#include "SurvivorCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values 
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("PaperSprite");
	PaperSpriteComponent->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	const FLatentActionInfo LatentInfo(0, FMath::Rand(), TEXT("Destroy") , this); 
	UKismetSystemLibrary::Delay(this, 3.0f, LatentInfo);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBeginOverlapEvent);

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Orange, TEXT("Spawn Bullet"));
}

void ABullet::DestroyActor()
{
	Destroy();
}

void ABullet::OnBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ASurvivorCharacter>(OtherActor))
	{
		this->DestroyActor();
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

