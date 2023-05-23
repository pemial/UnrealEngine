// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Buildings/Building.h"
#include <Runtime/Engine/Classes/Camera/CameraComponent.h>

#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGY_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	void virtual SetupInputComponent() override;
	void virtual BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	APawn* Player;
	UCameraComponent* PlayerCamera;
	float CameraMoveSpeed = 10.0f;
	float CameraZoomSpeed = 150.0f;

	float RotationSpeed = 2.0f;

	FHitResult WorldMousePointer;
	FHitResult PlainMousePointer;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ABuilding* HandBuilding;

	void MoveForward(float value);
	void MoveRight(float value);
	void RotateRight(float value);
	void ZoomIn();
	void ZoomOut();
	void Set();

	void DrawHandBuilding();
};
