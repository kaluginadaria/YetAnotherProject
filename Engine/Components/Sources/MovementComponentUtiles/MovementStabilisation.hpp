#pragma once
#ifndef MOVEMENT_STABILISATION_HPP
#define MOVEMENT_STABILISATION_HPP

#include "MovementStates.hpp"



struct FMovementStabilisationFlags
{
	int bControlOutsideStableZone : 1;
	int bChangeStatemode          : 1;
	int bIgnoreCurrentForces      : 1;

public:
	FMovementStabilisationFlags()
		: bControlOutsideStableZone (0)
		, bChangeStatemode			(1)
		, bIgnoreCurrentForces		(0)
	{}
};


struct FMovementStabilisation
{
public:	//~~~~~~~~~~~~~~~~~~~| Member Define

	using LStabilisationFunction = std::function<
		FVector(			// correction torque in free case
			const FQuat&,	// target  direction
			const FQuat&,	// current direction
			const FVector&,	// current angular speed
			float			// DeltaSeconds
			)
		>;

	enum EClampMode {
		ECM_RAW, // 
		ECM_TRIM // 
		};

public:	//~~~~~~~~~~~~~~~~~~~| Costruction

	FMovementStabilisation();

	void BeginPlay();

public:	//~~~~~~~~~~~~~~~~~~~| Interface

	void Stabilisate(float DeltaTime);
	void Stabilisate(float DeltaTime, const FQuat& Rotation);

protected:	//~~~~~~~~~~~~~~~~| Members

	FMovementStates* states; // 
	ActorComponent*  target; // 

	FMovementStabilisationFlags flags;
	FVector stabilisationFactor;
	FQuat   targetRotation;
	float   fallAngle;

public:

	void SetStates(FMovementStates* states);
	void SetTarget(ActorComponent*       target);
	
protected:	//~~~~~~~~~~| stabilisation function |

	LStabilisationFunction stabilisationFunction;

public:

	template<typename Funct>
	void SetStabilisationfunction(Funct func)						{ stabilisationFunction = func; }
	      LStabilisationFunction& GetStabilisationFunction()		{ return stabilisationFunction; }
	const LStabilisationFunction& GetStabilisationFunction() const	{ return stabilisationFunction; }
	
	void ResetStabilisationFunction();

protected:	//~~~~~~~~~~~~~~~|

	FVector DefaultStabilisationFunction(
		  const FQuat& TargetRotation
		, const FQuat& CurrentRotation
		, const FVector& CurrentAngularSpeed
		, float DeltaSeconds
		);
	
	FVector GetNormalTorque() const;
	FVector GetNormalForce () const;

	FVector ClampControl(FVector Control);
	FVector TrimControl (FVector Control);

};

#endif // !MOVEMENT_STABILISATION_HPP