// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
//#include "World.h"
#include "MyTank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	AMyTank* GetControlledTank();
	void AimToTarget();
	bool SightRayHitLoaction(FVector & HitLocation);
	bool LineHitLocation(FVector WorldLocation, FVector WorldDirection, FVector& HitLocation);

private:

	FVector2D ViewportSize;

	float CrosshairXLocation = 0.5f;
	float CrisshairYLocation = 0.3f;
	
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000.0;
	
};
