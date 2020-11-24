// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:

	AFPSGameMode();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void CompleteMission(APawn* InstigatorPawn);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionCompleted(APawn* IstigatorPawn);

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void testfunction();


protected:
	UPROPERTY(EditDefaultsOnly, Category = "NewView")
	TSubclassOf<AActor> NewViewClass;



public:


	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	float LimitTime = 3;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	float YourTime = 0.0;


};



