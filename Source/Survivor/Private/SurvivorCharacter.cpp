// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor/Public/SurvivorCharacter.h"

#include "Bullet.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Survivor/Public/SurvivorPlane.h"


// Sets default values
ASurvivorCharacter::ASurvivorCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	//initial property
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	GetCharacterMovement()->GravityScale = 0;
}

// Called when the game starts or when spawned
void ASurvivorCharacter::BeginPlay()
{
	Super::BeginPlay();

	AActor* PlayerStart = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerStart::StaticClass());
	if (PlayerStart)
	{
		SurvivorPlane = Cast<ASurvivorPlane>(UGameplayStatics::GetActorOfClass(GetWorld(), ASurvivorPlane::StaticClass()));
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString(TEXT("Spawn Charachter!")));
}

void ASurvivorCharacter::MovementPlane(float AxisValue)
{
	if (AxisValue != 0 && IsValid(SurvivorPlane))
	{
		SurvivorPlane->MovementToX(AxisValue);
	}
}

void ASurvivorCharacter::FireAction()
{
	SurvivorPlane->FireAction();
}

// Called every frame
void ASurvivorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASurvivorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (InputComponent)
	{
		InputComponent->BindAxis(TEXT("Movement"), this, &ASurvivorCharacter::MovementPlane);
		InputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ASurvivorCharacter::FireAction);
	}
}

