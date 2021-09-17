#include "RoadGenerator.h"


ARoadGenerator::ARoadGenerator()
{
 	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(FName("Spline"));

	if (!ensure(Spline != nullptr)) return;

	Spline->SetMobility(EComponentMobility::Static);

	RootComponent = Spline;	
}

void ARoadGenerator::BuildRoadElement(UStaticMesh* Mesh, FName Name, int Index)
{
	USplineMeshComponent* MeshComponent = NewObject<USplineMeshComponent>(this, Name);

	if (Mesh != nullptr && MeshComponent != nullptr)
	{
		int NextIndex = (Index + 1) % NumberOfSplinePoints;
		FVector StartLocation, StartTangent, EndLocation, EndTangent;

		Spline->GetLocalLocationAndTangentAtSplinePoint(Index, StartLocation, StartTangent);
		Spline->GetLocalLocationAndTangentAtSplinePoint(NextIndex, EndLocation, EndTangent);

		MeshComponent->RegisterComponent();
		MeshComponent->OnComponentCreated();
		MeshComponent->ComponentTags.Add(TEXT("RoadElement"));
		MeshComponent->SetMobility(EComponentMobility::Static);
		MeshComponent->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
		MeshComponent->SetStaticMesh(Mesh);
		MeshComponent->SetStartAndEnd(StartLocation, StartTangent, EndLocation, EndTangent, true);
		MeshComponent->SetStartRoll(RoadData[Index].TrackBank);
		MeshComponent->SetEndRoll(RoadData[NextIndex].TrackBank);
		MeshComponent->SetStartScale(FVector2D(RoadData[Index].TrackWidth, RoadData[Index].TrackThickness));
		MeshComponent->SetEndScale(FVector2D(RoadData[NextIndex].TrackWidth, RoadData[NextIndex].TrackThickness));
		MeshComponent->SetForwardAxis(ForwardAxis, true);
		MeshComponent->SetCollisionEnabled(Collisions);
	}
}

void ARoadGenerator::CreateRoad()
{
	NumberOfSplinePoints = Spline->GetNumberOfSplinePoints();

	for (auto& Component : GetComponentsByTag(USplineMeshComponent::StaticClass(), TEXT("RoadElement")))
	{
		Component->DestroyComponent();
	}

	while (RoadData.Num() < NumberOfSplinePoints)
	{
		FSplineRoad NewSplineRoad = FSplineRoad();
		RoadData.Add(NewSplineRoad);
	}

	int EndIndex = IsLooping ? NumberOfSplinePoints : NumberOfSplinePoints - 1;

	for (int i = 0; i < EndIndex; ++i)
	{		
		FString MeshName = FString::Printf(TEXT("Road %d"), i);	
		BuildRoadElement(RoadMesh, *MeshName, i);

		if (RoadData[i].LeftSide) 
		{
			FString LeftSideName = FString::Printf(TEXT("LeftSide %d"), i);
			BuildRoadElement(LeftSideMesh, *LeftSideName, i);
		}

		if (RoadData[i].RightSide)
		{
			FString RightSideName = FString::Printf(TEXT("RightSide %d"), i);
			BuildRoadElement(RightSideMesh, *RightSideName, i);
		}		
	}
}

void ARoadGenerator::PostEditMove(bool bFinished)
{
	CreateRoad();

	if (RoadData.Num() > NumberOfSplinePoints)
	{
		RoadData.Pop();
	}
}

void ARoadGenerator::OnConstruction(const FTransform& Transform)
{
	CreateRoad();
}

void ARoadGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoadGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

