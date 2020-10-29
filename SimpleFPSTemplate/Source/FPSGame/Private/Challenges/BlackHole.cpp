// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereDesComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereDesComp"));
	SphereDesComp->SetupAttachment(MeshComp);
	//SphereDesComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereDesComp->InitSphereRadius(100.0f);

	SphereDesComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapSphereDesComp);


	SphereAttactComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereAttactComp"));
	SphereAttactComp->SetupAttachment(MeshComp);
	SphereAttactComp->InitSphereRadius(3000.0f);




	//SphereDesComp->
	//SphereDesComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

void ABlackHole::OverlapSphereDesComp(UPrimitiveComponent* OverlapSphereDesComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
	if (OtherActor) OtherActor->Destroy();
}


// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{

	Super::BeginPlay();
	//GetOwner()->
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> SomeComponent;
	SphereAttactComp->GetOverlappingComponents(SomeComponent);
	for (int32 i = 0; i < SomeComponent.Num(); i++) {
		if (SomeComponent[i] && SomeComponent[i]->IsSimulatingPhysics()) {
			const float SphereRadius = SphereAttactComp->GetScaledSphereRadius();
			const float ForceStrength = -2000;
			SomeComponent[i]->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}
	
	
