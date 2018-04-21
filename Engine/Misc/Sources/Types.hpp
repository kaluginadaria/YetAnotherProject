#ifndef CORE_TYPES_HPP
#define CORE_TYPES_HPP
#pragma once

#include <assert.h>
#include <functional>

#include "Math.hpp"

class Object;


enum ESpaceType
{
	eLocal,
	eWorld,
	eParent
};

enum EObjectType
{
	eObject,
	eActor,
	eActorComponent,
	eActorModule,
	eGameMode
};

enum ETickType
{
	ePrePhysics,
	eInPhysics,
	ePostPhysics,
	eRender,

	eMAX
};

enum ESimulationState
{
	eUnstarted,
	eInProgress,
	ePaused,
	eStopped
};

enum EAttachmentRule
{
	eKeepRelative,
	eSnapToTarget,
	eKeepWorld
};


/*******************************************************************************
*								Interfaces
*******************************************************************************/

struct ITickFunction
{
	virtual void operator()(float DeltaTime, ETickType type) = 0;

	virtual Object*   GetTarget()	const = 0;
	virtual ETickType GetTickType() const = 0;
};


/*******************************************************************************
*								Structs
*******************************************************************************/


/**
 */
struct TickFunction : public ITickFunction
{
	ETickType tickType;
	Object*	  target;

	std::function<void(float, ETickType)> function;

public:

	virtual void operator()(float DeltaTime, ETickType type) override;

	virtual Object*		GetTarget()	  const override;
	virtual ETickType   GetTickType() const override;

public:
	
	template<class _Fx, class _T>
	void BindFunction(_Fx func, _T* newTarget)
	{
		target = newTarget;
		function = std::function<void(float, ETickType)>(std::bind(
			func, newTarget, 
			std::placeholders::_1, 
			std::placeholders::_2
			));
	}
};

/** 
 */
struct Index
{
public:
	size_t index;

public:
	Index() : index(0) {}
	size_t operator++(   ) { return ++index; }
	size_t operator++(int) { return ++index; }
	operator size_t()      { return   index; }
};


/** Object Universal ID
 */
struct OUID
{
	size_t id;

	OUID() : id(0) {}

	OUID operator++(int)
	{
		OUID curr = *this;
		return ++id, curr;
	}

	operator size_t() const
	{
		return id;
	}
};


/*******************************************************************************
*								Shape types
*******************************************************************************/

enum class EShapeType
{
	eBox
};

struct FShape
{
	FShape(EShapeType type, FVector extends) 
		: type   (type)
		, extends(extends)
	{}

	static FShape MakeBox(FVector extends)
	{
		return FShape(EShapeType::eBox, extends);
	}

public:

	EShapeType type;
	FVector extends;
};


/*******************************************************************************
*								constraint types
*******************************************************************************/

enum EAngleType
{
	ePitch,
	eRoll,
	eYaw
};

enum EAxisType
{
	eX,
	eY,
	eZ
};


struct FConstraintType
{
public: //~~~~~~~~~~~~~~| rotation

	int LockYaw   : 1;
	int LockRoll  : 1;
	int LockPitch : 1;

public: //~~~~~~~~~~~~~~| location

	int LockX : 1;
	int LockY : 1;
	int LockZ : 1;

public: //~~~~~~~~~~~~~~| constructors

	FConstraintType(bool default)
		: LockYaw   (default)
		, LockRoll  (default)
		, LockPitch (default)
		, LockX     (default)
		, LockY     (default)
		, LockZ     (default)
	{}

	// 3 - sphere
	static FConstraintType MakeSphere()
	{
		FConstraintType res(true);
		res.LockPitch = 0;
		res.LockRoll  = 0;
		res.LockYaw   = 0;
		return res;
	}

	// 3 - movement
	static FConstraintType MakeMovement()
	{
		FConstraintType res(true);
		res.LockX = 0;
		res.LockY = 0;
		res.LockZ = 0;
		return res;
	}

	// 4 - cylinder
	static FConstraintType MakeCylinder(EAxisType axis)
	{
		FConstraintType res(true);
		res.SetRotationMovement(axis, false);
		return res;
	}

	// 5 - ratation
	static FConstraintType MakeRotation(EAngleType angle)
	{
		FConstraintType res(true);
		res.SetRotation(angle, false);
		return res;
	}

	// 5 - axis
	static FConstraintType MakeAxis(EAxisType axis)
	{
		FConstraintType res(true);
		res.Setmovement(axis, false);
		return res;
	}

	// 6 - seal
	static FConstraintType MakeSeal()
	{
		return FConstraintType(true);
	}

private:

	void SetRotationMovement(EAxisType axis, bool state)
	{
		switch (axis) {
		case eX: LockRoll  = state; LockX = state; break;
		case eY: LockPitch = state; LockY = state; break;
		case eZ: LockYaw   = state; LockZ = state; break;
		}
	}

	void SetRotation(EAngleType angle, bool state)
	{
		switch (angle) {
		case ePitch: LockPitch = state; break;
		case eRoll:  LockRoll  = state; break;
		case eYaw:   LockYaw   = state; break;
		}
	}

	void Setmovement(EAxisType axis, bool state)
	{
		switch (axis)
		{
		case eX: LockX = state; break;
		case eY: LockY = state; break;
		case eZ: LockZ = state; break;
		}
	}
};


#endif // !CORE_TYPES_HPP