// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"
#include "ResourcePoint.h"


// Sets default values
AResourcePoint::AResourcePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AResourcePoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResourcePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

