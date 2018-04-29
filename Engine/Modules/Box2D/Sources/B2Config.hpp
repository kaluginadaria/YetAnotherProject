#pragma once
#ifndef B2CONFIG_HPP
#define B2CONFIG_HPP

#include "Configs/PhysicsConfig.hpp"
#include "B2PhysicsScene.hpp"
#include "B2Constraint.hpp"
#include "B2RigidBody.hpp"


class B2Config : public IPhysicsConfig
{
public:
	virtual IPhysicsScene* MakePhysicsScene() override
	{
		return new PhysicsScene();
	}

	virtual IConstraint* MakeConstraint(ActorComponent* owner) override
	{
		return new Constraint(owner);
	}

	virtual IRigidBody* MakeRigidBody(FShape shape, ActorComponent* owner, float mass, FVector inertia) override
	{
		return new RigidBody(shape, owner, mass, inertia);
	}
};

#endif // !B2CONFIG_HPP