// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ResourcePoint.generated.h"

UENUM()
enum class ResourceColour
{
	// Place-holder colours
	Blue,
	Green,
	Yellow,
	Count
};

UCLASS()
class BENEVOLENTGODZILLA_API AResourcePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResourcePoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	ResourceColour m_Colour;
};
