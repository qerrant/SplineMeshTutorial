#pragma once

#include "CoreMinimal.h"
#include "SplineRoad.generated.h"

USTRUCT(BlueprintType)
struct WIZRUN_API FSplineRoad
{
	GENERATED_USTRUCT_BODY()

public:
	FSplineRoad();
	FSplineRoad(float Bank, float Width, float Thickness, bool IsLeftSide, bool IsRightSide);
	~FSplineRoad();

	UPROPERTY(EditAnywhere)
	float TrackBank;

	UPROPERTY(EditAnywhere)
	float TrackWidth;

	UPROPERTY(EditAnywhere)
	float TrackThickness;

	UPROPERTY(EditAnywhere)
	bool LeftSide;

	UPROPERTY(EditAnywhere)
	bool RightSide;
};
