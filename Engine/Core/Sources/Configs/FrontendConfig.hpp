#ifndef FRONTEND_CONFIG_HPP
#define FRONTEND_CONFIG_HPP
#pragma once

#include "Interfaces/IFacade.hpp"
#include "Interfaces/IViewer.hpp"

class PlayerController;
class ActorComponent;

struct IFrontendConfig
{
	virtual IFacade* MakeFacade(ActorComponent* owner) = 0;
	virtual IViewer* MakeViewer(PlayerController* controller) = 0;
};



#endif // !FRONTEND_CONFIG_HPP
