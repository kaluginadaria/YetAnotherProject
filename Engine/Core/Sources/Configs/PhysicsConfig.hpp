#ifndef PHYSICS_CONFIG_HPP
#define PHYSICS_CONFIG_HPP
#pragma once

#include "Interfaces/IPhysicsScene.hpp"
#include "Interfaces/IConstraint.hpp"
#include "Interfaces/IRigidBody.hpp"


struct IPhysicsConfig
{
	virtual IPhysicsScene* MakePhysicsScene() = 0;
	virtual IConstraint  * MakeConstraint(ActorComponent* owner) = 0;
	virtual IRigidBody   * MakeRigidBody (FShape shape, ActorComponent* owner, float  mass = 0, FVector inertia = FVector::ZeroVector) = 0;
};



#endif // !PHYSICS_CONFIG_HPP
