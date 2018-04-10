#include "Actor.hpp"

Actor::Actor() : rootComponent(nullptr)
{}


//~~~~~~~~~~~~~~~~~~~~~~| << proxi functions

void Actor::AddForce	(const Vector3f& force, ESpaceType space) { if (rootComponent) rootComponent->AddForce (force, space); }
void Actor::AddTorque	(const Vector3f& torue, ESpaceType space) { if (rootComponent) rootComponent->AddTorque(torue, space); }

// transform

void		Actor::SetComponentTransform	(Transform newTransform) { if (rootComponent) rootComponent->SetComponentTransform(newTransform); }
void		Actor::SetRelativeTransform		(Transform newTransform) { if (rootComponent) rootComponent->SetRelativeTransform (newTransform); }
Transform	Actor::GetComponentTransform	() const				 { if (rootComponent) return rootComponent->GetComponentTransform(); return Transform::getIdentity(); }
Transform	Actor::GetRelativeTransform		() const				 { if (rootComponent) return rootComponent->GetRelativeTransform();	 return Transform::getIdentity(); }

// location

void		Actor::SetComponentLocation		(Vector3f newLocation)	 { if (rootComponent) rootComponent->SetComponentLocation(newLocation); }
void		Actor::SetRelativeLocation		(Vector3f newLocation)	 { if (rootComponent) rootComponent->SetRelativeLocation (newLocation); }
Vector3f	Actor::GetComponentLocation		() const				 { if (rootComponent) return rootComponent->GetComponentLocation(); return Vector3f(0, 0, 0); }
Vector3f	Actor::GetRelativeLocation		() const				 { if (rootComponent) return rootComponent->GetRelativeLocation();  return Vector3f(0, 0, 0); }

// rotation

void		Actor::SetComponentRotation		(Quatf newRotation)		 { if (rootComponent) rootComponent->SetComponentRotation(newRotation); }
void		Actor::SetRelativeRotation		(Quatf newRotation)		 { if (rootComponent) rootComponent->SetRelativeRotation (newRotation); }
Quatf		Actor::GetComponentRotation()	const					 { if (rootComponent) return rootComponent->GetComponentRotation(); return Quatf::getIdentity(); }
Quatf		Actor::GetRelativeRotation()	const					 { if (rootComponent) return rootComponent->GetRelativeRotation();  return Quatf::getIdentity(); }

// transform

void		Actor::AddTransform				(Transform delta, ESpaceType space)		{ if (rootComponent) rootComponent->AddTransform		(delta, space); }
void		Actor::AddComponentLocation		(Vector3f delta, ESpaceType space)		{ if (rootComponent) rootComponent->AddComponentLocation(delta, space); }
void		Actor::AddComponentRotation		(Quatf delta, ESpaceType space)			{ if (rootComponent) rootComponent->AddComponentRotation(delta, space); }

//~~~~~~~~~~~~~~~~~~~~~~| >> proxi functions

void Actor::SetRootComponent(ActorComponent* newRoot)
{
	if (rootComponent)
	{
		rootComponent->AttachTo(newRoot);
	}
	rootComponent = newRoot;
}