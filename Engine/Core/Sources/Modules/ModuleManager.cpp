#include "ModuleManager.hpp"

FFrontendConfig* ModuleManager::frontend = nullptr;



void ModuleManager::SetFrontendConfig(FFrontendConfig* conf)
{
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
