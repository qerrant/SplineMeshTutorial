#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "SplineRoad.h"
#include "RoadGenerator.generated.h"

UCLASS()
class WIZRUN_API ARoadGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	ARoadGenerator();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	UStaticMesh* RoadMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	UStaticMesh* LeftSideMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	UStaticMesh* RightSideMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	TArray<FSplineRoad> RoadData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	TEnumAsByte<ECollisionEnabled::Type> Collisions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	TEnumAsByte<ESplineMeshAxis::Type> ForwardAxis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	bool IsLooping = false;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void PostEditMove(bool bFinished) override;
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	USplineComponent* Spline;

protected:
	void CreateRoad();
	void BuildRoadElement(UStaticMesh* Mesh, FName Name, int Index);

private:
	int NumberOfSplinePoints = 0;	

};
