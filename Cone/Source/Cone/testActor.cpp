// Fill out your copyright notice in the Description page of Project Settings.


#include "testActor.h"
#include "LineActor.h"

// Sets default values
AtestActor::AtestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	MeshCompoent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AtestActor::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnPara;
	SpawnPara.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ALineActor* pSf;
	pSf = World->GetWorld()->SpawnActor<ALineActor>(ALineActor::StaticClass(), FVector(0, 0, 0), FRotator(0, 0, 0), SpawnPara);
}

// Called every frame
void AtestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

