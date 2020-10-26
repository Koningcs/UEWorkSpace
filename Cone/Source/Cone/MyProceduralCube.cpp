// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProceduralCube.h"
#include "lineActor.h"
// Sets default values
AMyProceduralCube::AMyProceduralCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>("mesh");
	SetRootComponent(mesh);
	mesh->bUseAsyncCooking = true;
	MeshDrawRect();
}

// Called when the game starts or when spawned
void AMyProceduralCube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyProceduralCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyProceduralCube::UpdateLOSMeshData(const TArray<FVector>& Vertices, const TArray<int32>& Triangles)
{
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
void AMyProceduralCube::MeshDrawRect() {

	TArray<FVector> vertices;
	FVector2D Position;
	Position.X = 0, Position.Y = 0;
	FVector2D Size;
	Size.X = 100, Size.Y = 100;



	vertices.Add(FVector(0, Position.X, Position.Y));//1
	vertices.Add(FVector(0, Position.X + Size.X, Position.Y + Size.Y));
	vertices.Add(FVector(0, Position.X, Position.Y + Size.Y));
	vertices.Add(FVector(0, Position.X, Position.Y));
	vertices.Add(FVector(0, Position.X + Size.X, Position.Y));
	vertices.Add(FVector(0, Position.X + Size.X, Position.Y + Size.Y));

	vertices.Add(FVector(Position.X, Position.Y, Position.X + Size.X));// 2
	vertices.Add(FVector(Position.X, Position.Y + Size.Y, Position.X + Size.X));
	vertices.Add(FVector(Position.X + Size.X, Position.Y + Size.Y, Position.X + Size.X));
	vertices.Add(FVector(Position.X, Position.Y, Position.X + Size.X));
	vertices.Add(FVector(Position.X + Size.X, Position.Y + Size.Y, Position.X + Size.X));
	vertices.Add(FVector(Position.X + Size.X, Position.Y, Position.X + Size.X));

	vertices.Add(FVector(Position.X, Position.Y + Size.Y, Position.Y));//3
	vertices.Add(FVector(Position.X + Size.X, Position.Y + Size.Y, Position.Y));
	vertices.Add(FVector(Position.X + Size.X, Position.Y + Size.Y, Position.Y + Size.Y));
	vertices.Add(FVector(Position.X, Position.Y + Size.Y, Position.Y));
	vertices.Add(FVector(Position.X + Size.X, Position.Y + Size.Y, Position.Y + Size.Y));
	vertices.Add(FVector(Position.X, Position.Y + Size.Y, Position.Y + Size.Y));


	vertices.Add(FVector(Position.X + Size.X, Position.X, Position.Y)); //对应1
	vertices.Add(FVector(Position.X + Size.X, Position.X, Position.Y + Size.Y));
	vertices.Add(FVector(Position.X + Size.X, Position.X + Size.X, Position.Y + Size.Y));
	vertices.Add(FVector(Position.X + Size.X, Position.X, Position.Y));
	vertices.Add(FVector(Position.X + Size.X, Position.X + Size.X, Position.Y + Size.Y));
	vertices.Add(FVector(Position.X + Size.X, Position.X + Size.X, Position.Y));

	vertices.Add(FVector(Position.X, Position.Y, Position.X));// 对应2
	vertices.Add(FVector(Position.X + Size.X, Position.Y + Size.Y, Position.X));
	vertices.Add(FVector(Position.X, Position.Y + Size.Y, Position.X));
	vertices.Add(FVector(Position.X, Position.Y, Position.X));
	vertices.Add(FVector(Position.X + Size.X, Position.Y, Position.X));
	vertices.Add(FVector(Position.X + Size.X, Position.Y + Size.Y, Position.X));


	vertices.Add(FVector(Position.X, Position.Y, Position.Y));//3
	vertices.Add(FVector(Position.X + Size.X, Position.Y, Position.Y + Size.Y));
	vertices.Add(FVector(Position.X + Size.X, Position.Y, Position.Y));
	vertices.Add(FVector(Position.X, Position.Y, Position.Y));
	vertices.Add(FVector(Position.X, Position.Y, Position.Y + Size.Y));
	vertices.Add(FVector(Position.X + Size.X, Position.Y, Position.Y + Size.Y));


	TArray<int32> Triangles;
	for (int i = 0; i < vertices.Num(); i++)
	{
		Triangles.Add(i);
	}
	UpdateLOSMeshData(vertices, Triangles);
}