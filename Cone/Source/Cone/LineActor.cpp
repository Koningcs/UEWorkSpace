#include "LineActor.h"

ALineActor::ALineActor()
{
	PrimaryActorTick.bCanEverTick = false;

	PathLineComponent = CreateDefaultSubobject<ULineComponent>("PathLineComponent");

	PathThickness = 5.f;
	PathColor = FLinearColor::Blue;

	SetRootComponent(PathLineComponent);
}

ALineActor::~ALineActor()
{
	Clear(); //gy add
}

/*void ALineActor::SetPath(const TArray<UGrid*>& Path)
{
	TArray<FVector> Points;

	FVector PrePoint, CurrPoint, TempPoint, Dir;
	for (int i = 0; i < Path.Num(); ++i)
	{
		const UGrid* Grid = Path[i];
		CurrPoint = Grid->GetCenter() + FVector(0.f, 0.f, ZOffset);

		if (i == 0)
		{
			Points.Add(CurrPoint);

			GridType = Grid->GridType;
			GridSize = Grid->GetGridSize();
		}
		else
		{
			if (FMath::Abs(CurrPoint.Z - PrePoint.Z) < LineBreakThreshold)
			{
				Points.Add(CurrPoint);
			}
			else
			{
				TempPoint = CurrPoint;
				TempPoint.Z = PrePoint.Z;
				Dir = TempPoint - PrePoint;
				Dir.Normalize();

				int32 Distance = FVector::Dist(PrePoint, TempPoint);

				Distance = PrePoint.Z < CurrPoint.Z ? Distance / 2 - ZOffset : Distance / 2 + ZOffset;

				TempPoint = PrePoint + Distance * Dir;
				Points.Add(TempPoint);

				TempPoint.Z = CurrPoint.Z;
				Points.Add(TempPoint);

				Points.Add(CurrPoint);
			}
		}
		PrePoint = CurrPoint;
	}

	SetCustomPoints(Points);
}*/

void ALineActor::SetCustomPoints(const TArray<FVector>& Points)
{
	PathLineComponent->LineColor = PathColor;
	PathLineComponent->LineThickness = PathThickness;
	PathLineComponent->SetPoints(Points);

	m_Points = Points;
}

void ALineActor::SetColor(FLinearColor color, bool bLoop)
{
	PathLineComponent->LineColor = color;
	PathLineComponent->SetColor(m_Points, color, bLoop);
}

void ALineActor::Clear()
{
	m_Points.Empty();
}

/*



	FActorSpawnParameters SpawnPara;
	SpawnPara.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	pSf->meshActor = playerController->GetWorld()->SpawnActor<ALineActor>(ALineActor::StaticClass(), FVector(0, 0, 0), FRotator(0, 0, 0), SpawnPara);
	TArray<FVector> array;
	array.Add(ptCur);
	((ALineActor*)pSf->meshActor)->SetCustomPoints(array);



*/