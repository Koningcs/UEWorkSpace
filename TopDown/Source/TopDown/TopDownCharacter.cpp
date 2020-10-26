// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TopDownCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ATopDownCharacter::ATopDownCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	LOSMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("LineOfSightMesh"));
	LOSMesh->bUseAsyncCooking = true;
	LOSMesh->ContainsPhysicsTriMeshData(false);
	LOSMesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

void ATopDownCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TickLOSMesh(DeltaSeconds);
	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}


void ATopDownCharacter::InitLOSMesh()
{
	/*
	int NumVertices = FMath::RoundToInt(ArcAngle / AngleStep) + 2;
	LOSVertices.Init(FVector::ZeroVector, NumVertices);

	int NumTriangles = (ArcAngle == 360) ? ((NumVertices - 1) * 3) : ((NumVertices - 2) * 3);
	LOSTriangles.Init(0, NumTriangles);
	*/


	/*

	FVector LineStartLocation = GetActorLocation();
	FVector CurrentActorForward = GetActorForwardVector();
	float MinAngle = -ArcAngle / 2;
	float MaxAngle = ArcAngle / 2;
	int VertexIndex = 1;
	for (float CurrentAngle = MinAngle; CurrentAngle <= MaxAngle; CurrentAngle += AngleStep) {
		FVector CurrentAngleDirection = CurrentActorForward.RotateAngleAxis(CurrentAngle, FVector(0, 0, 1));
		FVector LineEndLocation = LineStartLocation + CurrentAngleDirection * Radius;

		FVector HitResultInCharacterLocalSpace = GetActorTransform().InverseTransformPosition(LineEndLocation);
		LOSVertices[VertexIndex] = HitResultInCharacterLocalSpace;
		VertexIndex++;
	}

	VertexIndex = 0;
	for (int Triangle = 0; Triangle < LOSTriangles.Num(); Triangle += 3) {
		LOSTriangles[Triangle] = 0;
		LOSTriangles[Triangle + 1] = VertexIndex + 1;

		if (Triangle == (NumVertices - 2) * 3) // the arc has 360 angle, or in other words, it's a circle
		{
			LOSTriangles[Triangle + 2] = 1;
		}
		else
		{
			LOSTriangles[Triangle + 1] = VertexIndex + 2;
		}

		VertexIndex++;
	}

	UpdateLOSMeshData(LOSVertices, LOSTriangles);

	LOSMesh->SetRelativeLocation(FVector(0, 0, -90));
	LOSMesh->SetMaterial(0, LOSMaterial);
	*/
}

void ATopDownCharacter::BeginPlay() {
	Super::BeginPlay();

	InitLOSMesh();

}

void ATopDownCharacter::TickLOSMesh(float DeltaSeconds) {
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;

	const FName TraceTag("LoSTraceTag");
	FCollisionQueryParams TraceParams = FCollisionQueryParams(TraceTag, false, this);

	FVector LineStartLocation = GetActorLocation();
	FVector CurrentActorForward = GetActorForwardVector();
	FVector LineCenterLocation = LineStartLocation + CurrentActorForward * Radius;
	FVector LineEndLocation;

	UE_LOG(LogTemp, Warning, TEXT("CurrentActorForward %s"), *CurrentActorForward.ToString());
	UE_LOG(LogTemp, Warning, TEXT("LineCenterLocation %s"), *LineCenterLocation.ToString());
	FVector Dir = FVector(0, 1, 0);
	float r = 100;
	int Angle = 60;
	int NumVertices = 360 / Angle;
	LOSVertices.Init(FVector::ZeroVector, NumVertices + 2);
	LOSVertices[0] = LineCenterLocation;
	//int NumVertices = 360 / Angle;
	for (int i = 1; i <= NumVertices; i++) {
		LineEndLocation = LineCenterLocation + Dir * 50;
		UE_LOG(LogTemp, Warning, TEXT("LineEndLocation %s"), *LineEndLocation.ToString());
		Dir = Dir.RotateAngleAxis(Angle, CurrentActorForward);
		LOSVertices[i] = LineEndLocation;
	}
	LOSVertices[NumVertices + 1] = LOSVertices[1];


	LOSTriangles.Init(0, 3 * (NumVertices + 1));
	int k = 0;
	for (int i = 1; i < LOSVertices.Num() - 1; i++) {
		LOSTriangles[k++] = 0;
		LOSTriangles[k++] = i + 1;
		LOSTriangles[k++] = i;;

	}

	UpdateLOSMeshData(LOSVertices, LOSTriangles);
}


void ATopDownCharacter::UpdateLOSMeshData(const TArray<FVector>& Vertices, const TArray<int32>& Triangles) {
	TArray<FVector> TempNormals;
	TArray<FVector2D> TempUV0;
	TArray<FProcMeshTangent> TempTangents;
	TArray<FLinearColor> TempVertexColors;
	LOSMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, TempNormals, TempUV0, TempVertexColors, TempTangents, false);
}