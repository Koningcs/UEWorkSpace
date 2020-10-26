// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"
// 前置声明
class USphereComponent;
class UParticleSystem;
UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	bool bIsCarryingObjective;
protected:
	// 定义一个组件 名称MeshComp,类型StaticMesh
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UParticleSystem* PackupFX;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffects();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
