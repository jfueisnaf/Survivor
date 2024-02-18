// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurvivorPlane.generated.h"

UCLASS()
class SURVIVOR_API ASurvivorPlane : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASurvivorPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MovementToX(float Value);
	void FireAction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperSpriteComponent* PaperSpriteComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float movementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minMovement;

private:
	class ABullet* Bullet;
};
