// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
void ATankPlayerController::BeginPlay() {
	
	Super::BeginPlay();
	UWorld* World = GetWorld();
	AMyTank* ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ERROR: Controlled Tank is NULL"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank is %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	AimToTarget();
}

AMyTank* ATankPlayerController::GetControlledTank()
{
	return Cast<AMyTank>( GetPawn() );
}



void ATankPlayerController::AimToTarget() {

	FVector HitLoaction;
	if (SightRayHitLoaction(HitLoaction)) {
		// Ö´ÐÐ×ªÏò
		UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLoaction.ToString());
	}

}

bool ATankPlayerController::SightRayHitLoaction(FVector& HitLocation)
{
	
	if (GEngine && GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	FVector WorldLocation;
	FVector WorldDirection;
	FVector2D SightPosition = FVector2D(ViewportSize.X * CrosshairXLocation, ViewportSize.Y * CrisshairYLocation);
	DeprojectScreenPositionToWorld(SightPosition.X, SightPosition.Y, WorldLocation, WorldDirection);

	if (LineHitLocation(WorldLocation, WorldDirection, HitLocation)) {
		return true;
	}

	return false;
}

bool ATankPlayerController::LineHitLocation(FVector WorldLocation, FVector WorldDirection, FVector& HitLocation)
{

	UE_LOG(LogTemp, Warning, TEXT("%s %s"), *WorldLocation.ToString(), *WorldDirection.ToString());
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		WorldLocation,
		WorldLocation + WorldDirection * LineTraceRange,
		ECollisionChannel::ECC_Visibility
	)) {
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}
