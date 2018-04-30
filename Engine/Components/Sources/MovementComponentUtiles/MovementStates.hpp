#pragma once
#ifndef MOVEMENT_STATES_HPP
#define MOVEMENT_STATES_HPP

#include <unordered_map>
#include "Actor.hpp"


/** Movement mode
 */
enum class EMovementMode 
{
	  NONE

	, Run	         ///
	, Walk			 ///
	, Lying			 ///
	, Sprint		 ///
	, Jumping		 ///
	, Crouching		 ///

	, Swimming_slow  ///
	, Swimming_fast	 ///
	
	, falling        ///
	, flying		 ///
	
	, MAX
};


/** 
 */
enum class EMovementStateType {
	  Current	= 1 << 0
	, Last		= 1 << 1
	, MAX
};


/** 
 */
enum class EMovementImpactType
{		  
	  Force        /// input = force / torque
	, Impulce      /// imput = (angular) impulce
	, Acceleration /// input = (angular) accelration 
	, Velocity     /// input = (angular) velocity
};


/** Common characteristics of a movement mode 
*/
struct FMovementMode
{
public:	// << Normal (target) kinematic values
	FVector Velocity     = FVector::ZeroVector;
	FVector Omega        = FVector::ZeroVector;
	FVector Acceleration = FVector::ZeroVector;
	FVector Epsilon      = FVector::ZeroVector;

public: // << extra fields
	FVector Force          = FVector::ZeroVector; /// EMovementImpactType == Force
	FVector Torque         = FVector::ZeroVector; /// EMovementImpactType == Force
	FVector Impulce        = FVector::ZeroVector; /// EMovementImpactType == Impulce
	FVector AngularImpulce = FVector::ZeroVector; /// EMovementImpactType == Impulce

public:	// << Control values
	EMovementImpactType ImpactType = EMovementImpactType::Force;
	bool bTwoStep      = false; // Whether we set "On prepearing"
	bool bShouldColide = false; // Whether we need a overlap to apply an impact

public:	// << Trimming values
	float ForceBoostFactor  = 0;
	float TorqueBoostFactor = 0;
};


/** 
*/
struct FMovementTelemetry
{
public: // << kinematic telemetry
	FVector Velocity     = FVector::ZeroVector;
	FVector Acceleration = FVector::ZeroVector;
	FVector Omega        = FVector::ZeroVector;
	FVector Epsilon      = FVector::ZeroVector;
	FTransform Transform = FVector::ZeroVector;

public: // << control
	FVector LinearInput  = FVector::ZeroVector;
	FVector AngularInput = FVector::ZeroVector;

public: // << 
	FVector RegisteredForce  = FVector::ZeroVector;
	FVector RegisteredTorque = FVector::ZeroVector;
};


/** 
*/
struct FMovementStatesFlags
{
	int bTrimExternalForce	: 1;
	int bTrimExternalTorque	: 1;
	int bUseStabilisation	: 1;

public:
	FMovementStatesFlags()
		: bTrimExternalForce (1)
		, bTrimExternalTorque(1)
		, bUseStabilisation  (1)
	{}
};


/** Mane class of the file, storeing all required for a movement information
*/
struct FMovementStates
{
public:
	struct FUpdateFlags
	{	
	public:
		FUpdateFlags() : changed(0) {}

		void Clear()	         { changed = 0;    }
		explicit operator bool() { return changed; }

		void SetUpdated	 (int flag = 1) { changed |=  flag;	     }
		void UnsetUpdated(int flag = 1) { changed &= ~flag;	     }
		bool IsUpdated	 (int flag = 1) { return changed & flag; }

	protected:
		int changed;
	};

public:
	FMovementStates();

protected:	//~~~~~~~~~~~~~~~~~~~| Conditions
	/// telemetry
	mutable std::unordered_map< 
		EMovementStateType, 
		FMovementTelemetry
		> conditions;

public:	
	/// calculate final states and flush them into last sockets
	void NextFrame(float DeltaTime);
	/// calculate final states for the state type
	void UpdateStates(float DeltaTime);
	/// move current states into a last slot
	void shiftStates();

public:
	/// << control inut
	      FVector& LinearInput     (EMovementStateType Time = EMovementStateType::Current)       { return conditions[Time].LinearInput;      }
	const FVector& LinearInput     (EMovementStateType Time = EMovementStateType::Current) const { return conditions[Time].LinearInput;      }
	      FVector& AngularInput    (EMovementStateType Time = EMovementStateType::Current)       { return conditions[Time].AngularInput;     }
	const FVector& AngularInput    (EMovementStateType Time = EMovementStateType::Current) const { return conditions[Time].AngularInput;     }
	/// << force, applyed form external sources that must not be trimmered
	      FVector& RegisteredForce (EMovementStateType Time = EMovementStateType::Current)       { return conditions[Time].RegisteredForce;  }
	const FVector& RegisteredForce (EMovementStateType Time = EMovementStateType::Current) const { return conditions[Time].RegisteredForce;  }
	      FVector& RegisteredTorque(EMovementStateType Time = EMovementStateType::Current)       { return conditions[Time].RegisteredTorque; }
	const FVector& RegisteredTorque(EMovementStateType Time = EMovementStateType::Current) const { return conditions[Time].RegisteredTorque; }

protected:	//~~~~~~~~~~~~~~~~| Modes 
	/// work modes
	mutable std::unordered_map<
		EMovementMode, 
		FMovementMode
		> modes;

public:
	/// active mode
	EMovementMode movementMode;
	/// temporal modifer
	EMovementMode extraMode;

	/// get the mode
	FMovementMode& GetMode(EMovementMode mode)       { return modes[mode]; }
	FMovementMode  GetMode(EMovementMode mode) const { return modes[mode]; }
	
	/// get a current mode
	FMovementMode& CurrentMode()       { return GetMode(extraMode == EMovementMode::NONE ? movementMode : extraMode); }
	FMovementMode  CurrentMode() const { return GetMode(extraMode == EMovementMode::NONE ? movementMode : extraMode); }

public:	//~~~~~~~~~~~~~~~~~~~| Flags 
	/// flags shows wethre a state were update
	FUpdateFlags updateFlags;
	/// main flags
	FMovementStatesFlags flags;

public:	//~~~~~~~~~~~~~~~~~~~| Easy Acces
		//***| current values |

	FVector& Velocity()						{ return conditions[EMovementStateType::Current].Velocity;		}
	FVector& Acceleration()					{ return conditions[EMovementStateType::Current].Acceleration;	}
	FVector& Omega()						{ return conditions[EMovementStateType::Current].Omega;		}
	FVector& Epsilon()						{ return conditions[EMovementStateType::Current].Epsilon;		}
	FTransform& Transform()					{ return conditions[EMovementStateType::Current].Transform;	}

	FVector Velocity()				const	{ return conditions[EMovementStateType::Current].Velocity;		}
	FVector Acceleration()			const	{ return conditions[EMovementStateType::Current].Acceleration;	}
	FVector Omega()					const	{ return conditions[EMovementStateType::Current].Omega;		}
	FVector Epsilon()				const	{ return conditions[EMovementStateType::Current].Epsilon;		}
	FTransform Transform()			const	{ return conditions[EMovementStateType::Current].Transform;	}

public: //***| last values |

	FVector LastVelocity()			const	{ return conditions[EMovementStateType::Last].Velocity;		}
	FVector LastAcceleration()		const	{ return conditions[EMovementStateType::Last].Acceleration;	}
	FVector LastOmega()				const	{ return conditions[EMovementStateType::Last].Omega;			}
	FVector LastEpsilon()			const	{ return conditions[EMovementStateType::Last].Epsilon;			}
	FTransform LastTransform()		const	{ return conditions[EMovementStateType::Last].Transform;		}

public: //***| normal values |

	FVector NormalSpeed()			const	{ return CurrentMode().Velocity;	 }
	FVector NormalOmega()			const	{ return CurrentMode().Omega;		 }
	FVector NormalAcceleration()	const	{ return CurrentMode().Acceleration; }
	FVector NormalEpsilon()			const	{ return CurrentMode().Epsilon;		 }

};

#endif // !MOVEMENT_STATES_HPP