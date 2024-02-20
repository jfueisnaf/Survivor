// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
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
	SetRootComponent(PaperSpriteComponent);
	PaperSpriteComponent->SetWorldScale3D(FVector(0.2,0.2,0.2));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	

	//初始化组件属性
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	ProjectileMovementComponent->InitialSpeed = 800;
	ProjectileMovementComponent->Velocity = FVector(0,0,1);
	ProjectileMovementComponent->Activate(true);

	//load PaperSprite Assets
	static ConstructorHelpers::FObjectFinder<UPaperSprite>Sprite(TEXT("PaperSprite'/Game/Sprites/images/Bullet.Bullet'"));
	if (Sprite.Object)
	{
		PaperSpriteComponent->SetSprite(Sprite.Object);
	}
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	

	const FLatentActionInfo LatentInfo(0, FMath::Rand(), TEXT("DestroyActor") , this); 
	UKismetSystemLibrary::Delay(this, 3.0f, LatentInfo);
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

	UE_LOG(LogTemp, Warning, TEXT("FStringFormatArg: %f"), GetActorLocation().Z);

	//模拟子弹效果
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 10));
}

