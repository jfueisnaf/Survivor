// Fill out your copyright notice in the Description page of Project Settings.


#include "Survivor/Public/SurvivorGameMode.h"

#include "Survivor/Public/SurvivorCharacter.h"

ASurvivorGameMode::ASurvivorGameMode()
{
	DefaultPawnClass = ASurvivorCharacter::StaticClass();
}
