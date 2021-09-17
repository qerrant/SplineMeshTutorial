#include "SplineRoad.h"

FSplineRoad::FSplineRoad()
{
	TrackBank = 0.0f;
	TrackWidth = 1.0f;
	TrackThickness = 1.0f;
	LeftSide = false;
	RightSide = false;
}

FSplineRoad::FSplineRoad(float Bank, float Width, float Thickness, bool IsLeftSide, bool IsRightSide)
{
	TrackBank = Bank;
	TrackWidth = Width;
	TrackThickness = Thickness;
	LeftSide = IsLeftSide;
	RightSide = IsRightSide;
}

FSplineRoad::~FSplineRoad()
{
}
