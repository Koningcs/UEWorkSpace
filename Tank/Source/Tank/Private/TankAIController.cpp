// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
	AMyTank* PlayTank = GetPlayerTank();
	AMyTank* AITank = GetControlledTank();
	if (AITank != nullptr && PlayTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s %s"), *PlayTank->GetName(), *AITank->GetName());
	}
}


AMyTank* ATankAIController::GetPlayerTank() {
	return Cast<AMyTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
AMyTank* ATankAIController::GetControlledTank() {
	return Cast<AMyTank>(GetPawn()); //Cast 类型强制转换
}