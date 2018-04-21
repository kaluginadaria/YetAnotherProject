#ifndef OSG_CONFIG_HPP
#define OSG_CONFIG_HPP
#pragma once

#include "Configs/FrontendConfig.hpp"
#include "OSGConfig.hpp"
#include "OSGViewer.hpp"


struct OSGConfig : public IFrontendConfig
{
	virtual IFacade* MakeFacade(ActorComponent* owner) 
	{ 
		return new Facade(owner); 
	}

	virtual IViewer* MakeViewer(PlayerController* controller) 
	{ 
		return new Viewer(controller); 
	}
};


#endif // !OSG_CONFIG_HPP
