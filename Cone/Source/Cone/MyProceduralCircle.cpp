// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProceduralCircle.h"

// Sets default values
AMyProceduralCircle::AMyProceduralCircle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("mesh"));
	MeshDrawRect();
}

// Called when the game starts or when spawned
void AMyProceduralCircle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyProceduralCircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyProceduralCircle::UpdateCircleMeshData(const TArray<FVector>& Vertices, const TArray<int32>& Triangles) {
	TArray<FVector> TempNormals;
	TArray<FVector2D> TempUV0;
	TArray<FProcMeshTangent> TempTangents;
	TArray<FLinearColor> TempVertexColors;

	mesh->CreateMeshSection_LinearColor(
		0,
		Vertices,
		Triangles,
		TempNormals,
		TempUV0,
		TempVertexColors,
		TempTangents,
		false
	);


}

void AMyProceduralCircle::MeshDrawRect() {

	TArray<FVector> Vertices;
	
	TArray<int32> Triangles;
	FVector LineStartLocation = FVector(0, 0, 0);
	FVector dir = FVector(0, 1, 0);
	FVector LineEndLocation;	
	//Vertices.Add(FVector(0, 0, 100));
	dir.Normalize();
	int NumVertices = 360 / Angle;
	
	Vertices.Init(FVector::ZeroVector, NumVertices+2);
	Vertices[0] = FVector(0, 0, 100);
	for (int i = 1; i <= NumVertices; i++) {
		LineEndLocation = LineStartLocation + dir * Radius;
		dir = dir.RotateAngleAxis(Angle, FVector(0, 0, 1));
		Vertices[i] = LineEndLocation;
	}
	Vertices[NumVertices+1] = Vertices[1];
	
	for (int i = 1; i < Vertices.Num()-1; i++) {
		Triangles.Add(0);
		Triangles.Add(i + 1);
		Triangles.Add(i);
	}
	
	UpdateCircleMeshData(Vertices, Triangles);
}