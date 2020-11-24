// Fill out your copyright notice in the Description page of Project Settings.


#include "Challenges/LaunchCharacher/LaunchActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "FPSCharacter.h"

// Sets default values
ALaunchActor::ALaunchActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	SphereOverlapComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereOverlapComp"));
	SphereOverlapComp->SetupAttachment(MeshComp);
	SphereOverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereOverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereOverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereOverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchActor::HandleOverlap);
}

// Called when the game starts or when spawned
void ALaunchActor::BeginPlay()
{
	Super::BeginPlay();
}

void ALaunchActor::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPSCharacter* MyCharacher = Cast<AFPSCharacter>(OtherActor);
	FVector LaunchArea = FVector(1000, -200, 1200);
	MyCharacher->LaunchCharacter(LaunchArea, true, true);
}

// Called every frame
void ALaunchActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

