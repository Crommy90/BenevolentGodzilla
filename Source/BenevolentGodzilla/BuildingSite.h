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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) 
	TArray<ResourceColour> m_Required;
	
	TArray<ResourceColour> m_Placed;

	float m_PercentageWelded;
};
