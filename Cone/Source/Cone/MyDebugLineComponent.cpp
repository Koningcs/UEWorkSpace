// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDebugLineComponent.h"
#define M_PI 3.1415926535897932f
// Sets default values for this component's properties
UMyDebugLineComponent::UMyDebugLineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyDebugLineComponent::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("dir %s"), *GetOwner()->GetActorLocation().ToString());
	// ...
	
}


// Called every frame
void UMyDebugLineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector StartLocation = GetOwner()->GetActorLocation();
	FVector end = FVector(0, 0, 0);
	FVector dir = (end - StartLocation); // 法向量
	dir.Normalize();

	FVector Ends = StartLocation + dir * len; // 圆心坐标

	DrawDebugLine(
		GetWorld(),
		StartLocation,
		Ends,
		FColor(0, 255, 0),
		false,
		0.0f,
		0.0f,
		1.0f
	);
	

	FVector u = FVector(dir[1], -dir[0], 0);
	FVector v = FVector::CrossProduct(dir, u);

	u.Normalize(), v.Normalize();
	FVector EndLocation;
	for (float theta = 0; theta <= 2 * M_PI; theta += M_PI / 50) {
		float x = Ends[0] + r * (u[0] * cos(theta) + v[0] * sin(theta));
		float y = Ends[1] + r * (u[1] * cos(theta) + v[1] * sin(theta));
		float z = Ends[2] + r * (u[2] * cos(theta) + v[2] * sin(theta));
		EndLocation = FVector(x, y, z);
		FHitResult HitResult;
		FCollisionQueryParams QueryParameter = FCollisionQueryParams("", false, GetOwner());
		GetWorld()->LineTraceSingleByObjectType(
			HitResult,
			StartLocation,
			EndLocation,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			QueryParameter
		);
		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit != nullptr) EndLocation = HitResult.Location;
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			FColor(255, 0, 0),
			false,
			0.0f,
			0.0f,
			1.0f
		);
	}


}

