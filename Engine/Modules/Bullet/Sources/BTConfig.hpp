#pragma once
#ifndef BTCONFIG_HPP
#define BTCONFIG_HPP

#include "Configs/PhysicsConfig.hpp"
#include "BTPhysicsScene.hpp"
#include "BTConstraint.hpp"
#include "BTRigidBody.hpp"


class BTConfig : public IPhysicsConfig
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

#endif // !BTCONFIG_HPP