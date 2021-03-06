// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"
#include "BuildingSite.h"

#include "Planet.h"


// Sets default values
ABuildingSite::ABuildingSite()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_percentage_welded = 0.f;
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

bool ABuildingSite::PlaceColour(ResourceColour colour)
{
	int total = m_placed.Num() + m_required.Num();
	if ( total == 0 || m_complete || m_percentage_welded >= 100.f )
	{
		m_percentage_welded = 100.f;
		return true;
	}
	else if( colour == m_required[0] )
	{
		m_placed.Add( colour );
		m_required.RemoveAt( 0 );
		float total_f = (float)total;
		float not_done = m_required.Num();
		m_percentage_welded = ((total_f - not_done) / total_f) * 100.f;
		ColourPlaced_BP();
		return true;
	}
	else
	{
		for ( int i = 0; i < m_placed.Num(); ++i )
		{
			m_required.Add( m_placed[i] );
		}
		m_placed.Empty();
		float total_f = (float)total;
		float not_done = m_required.Num();
		m_percentage_welded = ((total_f - not_done) / total_f) * 100.f;
		return false;
	}
}

void ABuildingSite::building_fired()
{
	if ( m_percentage_welded >= 100.f )
	{
		m_complete = true;
		burnt_BP();
	}
}

ResourceColour ABuildingSite::NextColour() const
{
	return m_required[0];
}
