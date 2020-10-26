// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#define M_PI 3.1415926535897932f
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;		//射线起始点
	FRotator PlayerViewPointRotation;		//面朝方向
	// 获取角色的位置和旋转方向
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	FVector dir = PlayerViewPointRotation.Vector();
	//UE_LOG(LogTemp, Warning, TEXT("dir %s"), *dir.ToString());
	dir.Normalize();
	//UE_LOG(LogTemp, Warning, TEXT("dir %s"), *dir.ToString());
	FVector LineTraceEndLocation = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach; //射线终点,圆心坐标
	FVector Ends = LineTraceEndLocation;
	FVector u = FVector(dir[1], -dir[0], 0);
	FVector v = FVector::CrossProduct(dir, u);

	u.Normalize(), v.Normalize();
	FVector EndLocation;


	/*
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		Ends,
		FColor(0, 255, 0),
		false,
		0.0f,
		0.0f,
		1.0f
	);
	*/


	
	for (float theta = 0; theta <= 2 * M_PI; theta += M_PI / 70) {
		float x = Ends[0] + r * (u[0] * cos(theta) + v[0] * sin(theta));
		float y = Ends[1] + r * (u[1] * cos(theta) + v[1] * sin(theta));
		float z = Ends[2] + r * (u[2] * cos(theta) + v[2] * sin(theta));
		EndLocation = FVector(x, y, z);

		FHitResult HitResult;
		FCollisionQueryParams QueryParameter = FCollisionQueryParams("", false, GetOwner());
		GetWorld()->LineTraceSingleByObjectType(
			HitResult,
			PlayerViewPointLocation,
			EndLocation,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			QueryParameter
		);
		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit != nullptr) EndLocation = HitResult.Location;
		DrawDebugLine(
			GetWorld(),
			PlayerViewPointLocation,
			EndLocation,
			FColor(255, 0, 0),
			false,
			0.0f,
			0.0f,
			1.0f
		);
	}


}

