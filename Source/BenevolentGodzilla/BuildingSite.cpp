// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"
#include "BuildingSite.h"
<<<<<<< HEAD
//#include "SwatchComponent.h"
=======
>>>>>>> origin/master

#include "Planet.h"


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

void ABuildingSite::OnConstruction( const FTransform& Transform )
{
	APlanet* planet = nullptr;
	for ( TActorIterator<APlanet> ActorItr( GetWorld() ); ActorItr; ++ActorItr )
	{
		planet = *ActorItr;
		if ( planet )
		{
			FVector position, normal;
			planet->GetPositionAndNormal( GetActorLocation(), position, normal, 0.f );
			SetActorLocation( position );
			break;
		}
	}

	/*FName swatch_component_name("SwatchComponent");
	for (auto colour : m_required)
	{
		auto mesh = CreateDefaultSubobject<UStaticMeshComponent>(swatch_component_name);
		if (!mesh)
			continue;
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
		}
		mesh->SetWorldLocation(GetActorLocation());
		mesh->SetActive(true);
		mesh->SetVisibility(true);
		mesh->RegisterComponent();
		mesh->RegisterComponentWithWorld(GetWorld());
		m_swatch = mesh;
	}*/
}

void ABuildingSite::PlaceColour(ResourceColour colour)
{
	m_placed.Add(colour);
	m_required.RemoveSingle(colour);
}

void ABuildingSite::building_fired()
{
	m_complete = true;
}
