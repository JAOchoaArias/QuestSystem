// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Character/ACppQuestCharacter.h"


// Sets default values
AACppQuestCharacter::AACppQuestCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AACppQuestCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AACppQuestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AACppQuestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

