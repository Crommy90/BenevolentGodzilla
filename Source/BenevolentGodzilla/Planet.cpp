// Fill out your copyright notice in the Description page of Project Settings.

#include "BenevolentGodzilla.h"
#include "Planet.h"


// Sets default values
APlanet::APlanet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>( "Mesh" );

	m_Radius = 300.f;
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlanet::OnConstruction( const FTransform& Transform )
{
	FVector min, max;
	m_Mesh->GetLocalBounds( min, max );
	float mesh_radius = max.X - min.X;
	mesh_radius /= 2;
	float scale_ratio = m_Radius / mesh_radius;
	SetActorScale3D( FVector( scale_ratio ) );
}

void APlanet::GetPositionAndNormal( const FVector& position_in, FVector& position, FVector& Normal ) const
{
	// First find the normal
	Normal = ( position_in - GetActorLocation()).GetSafeNormal();

	position = GetActorLocation() + (Normal * m_Radius);
}

