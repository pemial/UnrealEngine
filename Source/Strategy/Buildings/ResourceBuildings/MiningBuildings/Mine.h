// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiningBuilding.h"
#include "Mine.generated.h"

UCLASS()
class STRATEGY_API AMine : public AMiningBuilding
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
