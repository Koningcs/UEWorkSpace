// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "MyProceduralCube.generated.h"

UCLASS()
class CONE_API AMyProceduralCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyProceduralCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MeshDrawRect();

	void UpdateLOSMeshData(const TArray<FVector>& Vertices, const TArray<int32>& Triangles);

	UPROPERTY(BlueprintReadWrite)
	UProceduralMeshComponent* mesh;
};
