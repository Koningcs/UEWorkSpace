// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProceduralCone.h"
#define M_PI 3.1415926535897932f
// Sets default values
AMyProceduralCone::AMyProceduralCone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("mesh"));
}

// Called when the game starts or when spawned
void AMyProceduralCone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyProceduralCone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

