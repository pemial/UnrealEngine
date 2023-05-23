// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController() {
	bShowMouseCursor = true;

}

void AMyPlayerController::BeginPlay() {
	Super::BeginPlay();

	Player = GetPawn();
	PlayerCamera = Player->FindComponentByClass<UCameraComponent>();
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Start;
	FVector Direction;
	DeprojectMousePositionToWorld(Start, Direction);
	FVector End = Start + Direction * 8000.0f;
	GetWorld()->LineTraceSingleByChannel(PlainMousePointer, Start, End, ECC_Visibility);
	GetWorld()->LineTraceSingleByChannel(WorldMousePointer, Start, End, ECC_Camera);

	DrawHandBuilding();
}

void AMyPlayerController::SetupInputComponent() {
    Super::SetupInputComponent();

    InputComponent->BindAxis("MoveForward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPlayerController::MoveRight);
	InputComponent->BindAxis("RotateRight", this, &AMyPlayerController::RotateRight);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMyPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMyPlayerController::ZoomOut);
	InputComponent->BindAction("Set", IE_Pressed, this, &AMyPlayerController::Set);
}

void AMyPlayerController::MoveForward(float value)
{
	Player->AddActorLocalOffset(FVector(CameraMoveSpeed * value, 0, 0));
}

void AMyPlayerController::MoveRight(float value)
{
	Player->AddActorLocalOffset(FVector(0, CameraMoveSpeed * value, 0));
}

void AMyPlayerController::RotateRight(float value)
{
	Player->AddActorLocalRotation(FRotator(0, -RotationSpeed * value, 0));
}

void AMyPlayerController::ZoomIn()
{
	PlayerCamera->AddWorldOffset(PlayerCamera->GetForwardVector() * CameraZoomSpeed);
}

void AMyPlayerController::ZoomOut()
{
	PlayerCamera->AddWorldOffset(-PlayerCamera->GetForwardVector() * CameraZoomSpeed);
}

void AMyPlayerController::Set() {
	if (HandBuilding) {
		HandBuilding = nullptr;
	}
	else {
		if (ABuilding* PointedBuilding = Cast<ABuilding>(WorldMousePointer.Actor.Get())) {
			PointedBuilding->ShowMenu();
		}
	}
}

void AMyPlayerController::DrawHandBuilding() {
	if (HandBuilding) {
		HandBuilding->SetActorLocation(PlainMousePointer.Location);
	}
}