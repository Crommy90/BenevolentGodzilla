// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Planet.generated.h"

UCLASS()
class BENEVOLENTGODZILLA_API APlanet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnConstruction( const FTransform& Transform ) override;

	UFUNCTION( BlueprintCallable, Category = "Location" )
	void GetPositionAndNormal( const FVector& position_in, FVector& position, FVector& Normal, float RadiusAddition ) const;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Planet )
		float m_Radius;

	UPROPERTY( Category = Planet, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true") )
		class UStaticMeshComponent* m_Mesh;

	
	
};
