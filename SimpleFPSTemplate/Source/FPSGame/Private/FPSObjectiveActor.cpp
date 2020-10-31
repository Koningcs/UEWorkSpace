// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 实例化组件
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	
	// 设置碰撞
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	//设置为根组件
	RootComponent = MeshComp;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	
	//设置碰撞相关
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	//设置MeshComp 是 SphereComp 的上层组件
	SphereComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	//PlayEffects();
}

void AFPSObjectiveActor::PlayEffects() {
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PackupFX, GetActorLocation());
}


// Called every frame
void AFPSObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor) {
	// 继承于Actor
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffects();
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter) { 
		MyCharacter->bIsCarryingObjective = true;
		Destroy();
	}
}
