// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChangeMaterial.generated.h"


class UBoxComponent;
class UMaterial;
UCLASS()
class FPSGAME_API AChangeMaterial : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChangeMaterial();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	UPROPERTY(EditAnywhere, Category = "ChangeMaterial")
	UMaterial* OnMaterial;

	UPROPERTY(EditAnywhere, Category = "ChangeMaterial")
	UMaterial* OffMaterial;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapBox;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MyMesh;

	UFUNCTION()
	void ChangeMaterialOn(UPrimitiveComponent* OverlapSphereDesComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );


	UFUNCTION()
	void ChangeMaterialOff(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
