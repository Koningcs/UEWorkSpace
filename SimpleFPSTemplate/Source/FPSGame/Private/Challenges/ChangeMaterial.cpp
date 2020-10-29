// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeMaterial.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
// Sets default values
AChangeMaterial::AChangeMaterial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));
	RootComponent = MyMesh;
	MyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
	OverlapBox->SetupAttachment(MyMesh);
	OverlapBox->SetBoxExtent(FVector(100.0f));
	OverlapBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//OverlapBox->SetCollisionEnabled();
		 
	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &AChangeMaterial::ChangeMaterialOn);
	OverlapBox->OnComponentEndOverlap.AddDynamic(this, &AChangeMaterial::ChangeMaterialOff);

}

// Called when the game starts or when spawned
void AChangeMaterial::BeginPlay()
{
	Super::BeginPlay();
	//MyMesh->SetMaterial(0, OffMaterial);
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(100, 100, 100), FColor::White, true, -1, 0, 10);
	

}
// Called every frame
void AChangeMaterial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AChangeMaterial::ChangeMaterialOn(UPrimitiveComponent* OverlapSphereDesComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MyMesh->SetMaterial(0, OnMaterial);

}

void AChangeMaterial::ChangeMaterialOff(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	MyMesh->SetMaterial(0, OffMaterial);
}


