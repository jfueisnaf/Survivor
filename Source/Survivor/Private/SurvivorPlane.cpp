// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor/Public/SurvivorPlane.h"

#include "Bullet.h"
#include "PaperSpriteComponent.h"


// Sets default values
ASurvivorPlane::ASurvivorPlane()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("PaperSprite");
	PaperSpriteComponent->SetupAttachment(RootComponent);

	movementSpeed = 1.f;
}

// Called when the game starts or when spawned
void ASurvivorPlane::BeginPlay()
{
	Super::BeginPlay();
}

void ASurvivorPlane::MovementToX(float Value)
{
	float movementValue = Value + GetActorLocation().Y;
	FVector NewLocationVector = FVector(GetActorLocation().X, movementValue, GetActorLocation().Z);
	SetActorLocation(NewLocationVector * movementSpeed);
}

void ASurvivorPlane::FireAction()
{
	GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), GetActorLocation(), GetActorRotation());
}

// Called every frame
void ASurvivorPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

