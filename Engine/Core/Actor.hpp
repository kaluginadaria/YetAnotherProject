#pragma once

#include <vector>
#include <memory>

#include "ActorComponent.hpp"
#include "ActorModule.hpp"
#include "Object.hpp"


/** Base class for all Actors on scene
 *	Privides:
 *	. relative location	(root component driven)
 *	. obsolute location	(root component driven)
 */
class Actor : public Object
{
	GENERATED_BODY(Actor, Object)
public:

	Actor();

public: //~~~~~~~~~~~~~~| Physics -> to root component

	void AddForce (const Vector3f& force, ESpaceType space);
	void AddTorque(const Vector3f& torue, ESpaceType space);

public: //~~~~~~~~~~~~~~| Kinematic -> to root component

		/// transform

	void SetComponentTransform(Transform newTransform);
	void SetRelativeTransform(Transform newTransform);
	Transform GetComponentTransform() const;
	Transform GetRelativeTransform() const;

	/// location

	void SetComponentLocation(Vector3f newLocation);
	void SetRelativeLocation(Vector3f newLocation);
	Vector3f  GetComponentLocation() const;
	Vector3f  GetRelativeLocation() const;

	/// rotation

	void SetComponentRotation(Quatf newRotation);
	void SetRelativeRotation(Quatf newRotation);
	Quatf GetComponentRotation() const;
	Quatf GetRelativeRotation() const;

	/// add

	void AddTransform(Transform delta, ESpaceType space = ESpaceType::eWorld);
	void AddComponentLocation(Vector3f	delta, ESpaceType space = ESpaceType::eWorld);
	void AddComponentRotation(Quatf     delta, ESpaceType space = ESpaceType::eWorld);

public: //~~~~~~~~~~~~~~| chain and modules

	const ActorComponent* GetRootComponent() const { return rootComponent; }
	      ActorComponent* GetRootComponent()       { return rootComponent; }
	void SetRootComponent(ActorComponent* newRoot);

	      std::vector<ActorModule*>& GetModules()	    { return modules; }
	const std::vector<ActorModule*>& GetModules() const { return modules; }

	// TODO:: GetComponents<T> - over modules and components

protected:

	/// >> common
	ActorComponent* rootComponent;
	std::vector<ActorModule*> modules;
	/// <<	

public: //~~~~~~~~~~~~~~| Creation functions

	template<class _T>
	_T* CreateSubComponent(std::string name)
	{
		return ObjectCreator::CreateSubComponent<_T>(name, world, this);
	}
};
