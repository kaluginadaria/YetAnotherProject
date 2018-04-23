#ifndef MODULE_MANAGER_HPP
#define MODULE_MANAGER_HPP
#pragma once

#include "Configs/FrontendConfig.hpp"
#include "Configs/PhysicsConfig.hpp"


class ModuleManager
{
public:

	static void SetFrontendConfig(IFrontendConfig* conf);
	static IFacade* MakeFacade(ActorComponent* owner);
	static IViewer* MakeViewer(PlayerController* controller);

	static void SetPhysicsConfig(IPhysicsConfig* conf);
	static IPhysicsScene* MakeScene();
	static IConstraint* MakeConstraint(ActorComponent* owner);
	static IRigidBody* MakeBody(FShape shape, ActorComponent* owner, float mass = 0, FVector inertia = FVector::ZeroVector);

private:

	static IFrontendConfig* frontend;
	static IPhysicsConfig*  physics;
};


#endif // !MODULE_MANAGER_HPP
