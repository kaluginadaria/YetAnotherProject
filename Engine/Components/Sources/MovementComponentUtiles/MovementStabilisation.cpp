#include "MovementStabilisation.hpp"

FMovementStabilisation::FMovementStabilisation()
	: states(nullptr)
	, target(nullptr)
	, fallAngle(0)
{
	ResetStabilisationFunction();
}

void FMovementStabilisation::BeginPlay()
{
}

void FMovementStabilisation::Stabilisate(float DeltaTime)
{
}

void FMovementStabilisation::Stabilisate(float DeltaTime, const FQuat & Rotation)
{
}

void FMovementStabilisation::SetStates(FMovementStates * states)
{
}

void FMovementStabilisation::SetTarget(ActorComponent * target)
{
}

void FMovementStabilisation::ResetStabilisationFunction()
{
}

FVector FMovementStabilisation::DefaultStabilisationFunction(
	  const FQuat& TargetRotation
	, const FQuat& CurrentRotation
	, const FVector& CurrentAngularSpeed
	, float DeltaSeconds )
{
	return FVector();
}

FVector FMovementStabilisation::GetNormalTorque() const
{
	return FVector();
}

FVector FMovementStabilisation::GetNormalForce() const
{
	return FVector();
}

FVector FMovementStabilisation::ClampControl(FVector Control)
{
	return FVector();
}

FVector FMovementStabilisation::TrimControl(FVector Control)
{
	return FVector();
}
