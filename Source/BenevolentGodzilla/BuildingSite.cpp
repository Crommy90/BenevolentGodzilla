// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"
#include "BuildingSite.h"


// Sets default values
ABuildingSite::ABuildingSite()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildingSite::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildingSite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingSite::PlaceColour(ResourceColour colour)
{
	m_placed.Add(colour);
	m_required.Remove(colour);
}