// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"
#include "BuildingSite.h"
#include "SwatchComponent.h"


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
	
	FName swatch_component_name("SwatchComponent");
	for (auto colour : m_required)
	{
		/*auto mesh = CreateDefaultSubobject<UStaticMeshComponent>(swatch_component_name);
		mesh->SetStaticMesh(m_cube);
		switch (colour)
		{
		case ResourceColour::Blue:
			mesh->SetMaterial(0, m_blue);
			break;

		case ResourceColour::Green:
			mesh->SetMaterial(0, m_green);
			break;

		case ResourceColour::Yellow:
			mesh->SetMaterial(0, m_yellow);
			break;
		}*/
	}
}

// Called every frame
void ABuildingSite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingSite::PlaceColour(ResourceColour colour)
{
	m_placed.Add(colour);
	m_required.RemoveSingle(colour);
}