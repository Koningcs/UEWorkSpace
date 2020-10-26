#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LineComponent.h"
#include "LineActor.generated.h"

/**
	Used for rendering path
*/
UCLASS()
class  ALineActor : public AActor
{
	GENERATED_BODY()

public:
	ALineActor();
	virtual ~ALineActor();

	UFUNCTION(BlueprintCallable, Category = "PathGuide")
		virtual void SetCustomPoints(const TArray<FVector>& Points);

	UFUNCTION(BlueprintCallable, Category = "PathGuide")
		virtual void Clear();

	FLinearColor PathColor;

	float PathThickness;

	//float ZOffset;
public:
	void SetColor(FLinearColor color, bool bLoop);

protected:
	TArray<FVector> m_Points;

	UPROPERTY()
		ULineComponent* PathLineComponent;
};
