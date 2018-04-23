#include "ModuleManager.hpp"

IFrontendConfig* ModuleManager::frontend = nullptr;
IPhysicsConfig*  ModuleManager::physics  = nullptr;


void ModuleManager::SetFrontendConfig(IFrontendConfig* conf)
{
	if (frontend)
	{
		delete frontend;
	}
	frontend = conf;
}

IFacade* ModuleManager::MakeFacade(ActorComponent* owner)
{
	if (frontend)
	{
		return frontend->MakeFacade(owner);
	}
	return nullptr;
}

IViewer* ModuleManager::MakeViewer(PlayerController* controller)
{
	if (frontend)
	{
		return frontend->MakeViewer(controller);
	}
	return nullptr;
}

void ModuleManager::SetPhysicsConfig(IPhysicsConfig* conf)
{
	if (physics)
	{
		delete physics;
	}
	physics = conf;
}

IPhysicsScene* ModuleManager::MakeScene()
{
	if (physics)
	{
		return physics->MakePhysicsScene();
	}
	return nullptr;
}

IConstraint* ModuleManager::MakeConstraint(ActorComponent* owner)
{
	if (physics)
	{
		return physics->MakeConstraint(owner);
	}
	return nullptr;
}

IRigidBody* ModuleManager::MakeBody(FShape shape, ActorComponent* owner, float mass, FVector inertia)
{
	if (physics)
	{
		return physics->MakeRigidBody(shape, owner, mass, inertia);
	}
	return nullptr;
}
