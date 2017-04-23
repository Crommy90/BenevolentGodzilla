// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ResourcePoint.h"
#include "BuildingSite.generated.h"

UCLASS()
class BENEVOLENTGODZILLA_API ABuildingSite : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingSite();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* m_swatch;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnConstruction( const FTransform& Transform ) override;

	UFUNCTION(BlueprintCallable, Category = "BuildingSite")
		void PlaceColour(ResourceColour colour);

	UFUNCTION( BlueprintImplementableEvent, Category = "Godzilla" )
		void ColourPlaced_BP();

	void building_fired();

	UPROPERTY(EditAnywhere) 
	TArray<ResourceColour> m_required;

	UPROPERTY(EditAnywhere)
	UStaticMesh* m_cube;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* m_blue;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* m_green;
	UPROPERTY(EditAnywhere)
	UMaterialInterface* m_yellow;
	
	TArray<ResourceColour> m_placed;

	UPROPERTY( BlueprintReadOnly )
	float m_percentage_welded;

	UPROPERTY( BlueprintReadOnly )
	bool m_complete = false;
};
