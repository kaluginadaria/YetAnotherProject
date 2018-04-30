#include "Engine.hpp"
#include "B2Config.hpp"
#include "OSGConfig.hpp"
#include "Modules/ModuleManager.hpp"

#include "PGGameMode.hpp"
#include "PGPlayerController.hpp"

using PGSimulationConfig = TSimulationModeConfig<PGPlayerController, PGGameMode>;


int main()
{
	ModuleManager::SetFrontendConfig(new OSGConfig());
	ModuleManager::SetPhysicsConfig (new B2Config() );

	auto* config = new PGSimulationConfig();
	auto mode = SimulationMode::Get(config);
	
	Engine engine;
	engine.SetSimulationMode(std::move(mode));
	return engine.MainCycle();
}