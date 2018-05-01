#ifndef MODULE_MANAGER_HPP
#define MODULE_MANAGER_HPP

#include "../Configs/FrontendConfig.hpp"


/** In the project we have this submodules:
 *	. graphic
 *	. phisics
 * the first one have the interfaces:
 *		. IFacde
 *		. IVewer
 * the second one:
 *		. IRigidBody
 *		. IPxsScene
 *
 * The interface realisation must be injected into the engine components.
 * And to make it, it's required to have an singleton-fabric will crete the interface realisation.
 * To make that I'll use a class-config generateing the realisations.
 */
class ModuleManager
{
public:

	static void SetFrontendConfig(FFrontendConfig* conf);
	static IFacade* MakeFacade(ActorComponent* owner);
	static IViewer* MakeViewer(PlayerController* controller);

private:

	static FFrontendConfig* frontend;
};


#endif // !MODULE_MANAGER_HPP
